// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuPlayerController.h"
#include "MainHUD.h"

AMenuPlayerController::AMenuPlayerController()
{
	
}

/*void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);

*/

// ...NEED PAUSE ADDED -- DESMOND CRAFT
void AMenuPlayerController::SetupInputComponent()
{
	/*Super::SetupInputComponent();
	if (InputComponent)
	{
		// GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, TEXT("GOT HERE"));
		InputComponent->BindAction("IA_Pause", IE_Pressed, this, &AMenuPlayerController::OpenMenu);
	}*/
}
