// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerCharacter.h"

#include "CleanupClashGameMode.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "LevelHUD.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MenuPlayerController.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

// APlayerCharacter

APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetMesh()->SetRelativeLocation(FVector(0,0,-90));
	GetMesh()->SetRelativeRotation(FRotator(0,-90,0));

	// Set melee collision box
	MeleeCollision = CreateDefaultSubobject<UBoxComponent>("Melee Collision");
	MeleeCollision->SetRelativeLocation(FVector(50, 0, 0));
	MeleeCollision->SetBoxExtent(FVector(16, 40, 95));
	MeleeCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnMeleeOverlap);
	MeleeCollision->SetupAttachment(RootComponent);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	
	// there absolutely has to be a better way to do this
	static ConstructorHelpers::FObjectFinder<USoundWave> attackSoundWave(TEXT("/Script/Engine.SoundWave'/Game/Sounds/effect__lesaucisson__swoosh-1.effect__lesaucisson__swoosh-1'"));
	AttackSoundWave = attackSoundWave.Object;
	
	static ConstructorHelpers::FObjectFinder<USoundWave> attackHitSoundWave(TEXT("/Script/Engine.SoundWave'/Game/Sounds/effect__adrian_gomar__book-impact-06.effect__adrian_gomar__book-impact-06'"));
	AttackHitSoundWave = attackHitSoundWave.Object;
	
}

void APlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	TeamName = static_cast<ACleanupClashGameMode*>(UGameplayStatics::GetGameMode(GetWorld()))->GiveTeamName();
}

//////////////////////////////////////////////////////////////////////////
// Input

ETeamName APlayerCharacter::GetTeamName()
{
	return TeamName;
}

bool APlayerCharacter::CheckTrashLimit()
{
	if (TrashArray.Num() < MaxTrash)
		return true;
	return false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		/*EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);*/

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		
		// Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::StartInteract);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &APlayerCharacter::EndInteract);
		
		// Attacking
		EnhancedInputComponent->BindAction(MeleeAction, ETriggerEvent::Started, this, &APlayerCharacter::Melee);

		// Pausing
		// ...NEED PAUSE ADDED -- DESMOND CRAFT
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &APlayerCharacter::Pause);

		// Dashing
		EnhancedInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &APlayerCharacter::Dash);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APlayerCharacter::OnMeleeOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerCharacter* OtherPlayer = Cast<APlayerCharacter>(OtherActor);
	if (OtherPlayer != nullptr && OtherPlayer != this)
	{
		if (OtherPlayer->State != EPlayerState::Stunned && OtherPlayer->TeamName != TeamName)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Blue, FString::Printf(TEXT("Hit another char %s"), *OtherPlayer->GetName()));

			//play hit noise
			UGameplayStatics::PlaySound2D(this, AttackHitSoundWave, 0.5f);

			// Stop animation root motion and disable attack collision
			MeleeCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			GetCharacterMovement()->DisableMovement();

			// Cause other character to drop trash and stun them
			OtherPlayer->StunCharacter();
			FRotator RotationToSelf = UKismetMathLibrary::FindLookAtRotation(OtherPlayer->GetActorLocation(), GetActorLocation());
			FVector DropDir = UKismetMathLibrary::GetForwardVector(RotationToSelf);
			OtherPlayer->DropTrash(DropDir);
		}
	}
}

void APlayerCharacter::DropTrash(FVector Direction)
{
	// Drop whichever amount is greater: 1/4 of trash total or 3 (or the rest of held trash if < 3)
	int TrashToDrop = UKismetMathLibrary::Max(ceil(TrashArray.Num() * 0.25), UKismetMathLibrary::Min(3, TrashArray.Num()));
	//GEngine->AddOnScreenDebugMessage(-1, 2.0, FColor::Blue, FString::Printf(TEXT("Dropping %d"), TrashToDrop));
	for (int i = 0; i < TrashToDrop; i++)
	{
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Z = 120;
		ATrash* Trash = GetWorld()->SpawnActor<ATrash>(BPTrashActor, SpawnLocation, GetActorRotation());
		FVector UniqueShotDirection = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(Direction, 45.0);
		FVector UniqueShotLocation = GetActorLocation() + UniqueShotDirection * UKismetMathLibrary::RandomFloatInRange(200, 400);
		UniqueShotLocation.Z = 30;
		Trash->Location = UniqueShotLocation;
		TrashArray.RemoveAt(TrashArray.Num() - 1);
	}
	UpdateTrashIcon();
}

void APlayerCharacter::StunCharacter()
{
	State = EPlayerState::Stunned;
	GetCharacterMovement()->MovementMode = EMovementMode::MOVE_None;
	UWorld* OurWorld = GetWorld();
	float StunTime = Cast<ACleanupClashGameMode>(OurWorld->GetAuthGameMode())->PlayerStunTime;
	FTimerHandle StunTimer = FTimerHandle();
	GetWorld()->GetTimerManager().SetTimer(StunTimer, this, &APlayerCharacter::EndStun, StunTime, false);
}

void APlayerCharacter::EndStun()
{
	GetCharacterMovement()->MovementMode = MOVE_Walking;
	State = EPlayerState::Default;
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = CameraComponent->GetActorRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Melee(const FInputActionValue& Value)
{
	if (State == EPlayerState::Default)
	{
		UGameplayStatics::PlaySound2D(this, AttackSoundWave, 0.5f);
		State = EPlayerState::Attacking;
		MeleeCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		PlayAnimMontage(MeleeAttackAnim);	
	}
}

void APlayerCharacter::EndMeleeAttack()
{
	MeleeCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->MovementMode = MOVE_Walking;
	if (State != EPlayerState::Stunned)
		State = EPlayerState::Default;
}

// ...NEED PAUSE ADDED -- DESMOND CRAFT
void APlayerCharacter::Pause()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Fun"));
	if (ALevelHUD* HUD = Cast<ALevelHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
	{
		HUD->ShowPauseMenu();
	}
}