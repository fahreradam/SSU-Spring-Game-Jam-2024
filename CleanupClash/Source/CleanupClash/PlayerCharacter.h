// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CleanupClash.h"
#include "TeamName.h"
#include "InputActionValue.h"
#include "Trash.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;	

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;
	
	/** Melee Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MeleeAction;

	/** Pause Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"));
	UInputAction* PauseAction;

	/** Dash Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DashAction;	

	/** Melee Attack Anim */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Anims", meta=(AllowPrivateAccess = "true"))
	UAnimMontage* MeleeAttackAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound, meta = (AllowPrivateAccess = "true"))
	USoundWave* AttackSoundWave;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Sound, meta = (AllowPrivateAccess = "true"))
	USoundWave* AttackHitSoundWave;
public:
	APlayerCharacter();

	UFUNCTION(BlueprintCallable)
	void EndMeleeAttack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	ACameraActor* CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Team)
	ETeamName TeamName = ETeamName::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Collision)
	UBoxComponent* MeleeCollision;

	UFUNCTION()
	void OnMeleeOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void StunCharacter();

	UFUNCTION(BlueprintCallable)
	void EndStun();

	UFUNCTION(BlueprintCallable)
	void DropTrash(FVector Direction);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ATrash> BPTrashActor;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<int> TrashArray;

	UPROPERTY(BlueprintReadWrite)
	EPlayerState State = EPlayerState::Default;
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for melee input */
	void Melee(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void StartInteract();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void EndInteract();

	void Pause();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void Dash();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int MaxTrash = 5;

	UFUNCTION(BlueprintCallable)
	ETeamName GetTeamName();

	UFUNCTION(BlueprintCallable)
	bool CheckTrashLimit();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UpdateTrashIcon();
			

protected:
	
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();
};

