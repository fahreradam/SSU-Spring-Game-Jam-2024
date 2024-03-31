// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "SMainMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/InputDeviceLibrary.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"


void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	ShowMainMenu();
}

void AMainHUD::ShowMainMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		MenuWidget = SNew(SMainMenuWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(
			SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef())
		);
		if (PlayerOwner)
		{
			// ...player owner is from HUD.h
			// ...SetInputMode is from PlayerController.h
			PlayerOwner->bShowMouseCursor = true;
			PlayerOwner->SetInputMode(FInputModeUIOnly());
		}
	}
}

void AMainHUD::RemoveMenu(bool GoToMainLevel)
{
	if (GEngine && GEngine->GameViewport && MenuWidgetContainer.IsValid())
	{
		if (PlayerOwner)
		{
			TArray<FInputDeviceId> InputDeviceIDs;
			UInputDeviceLibrary::GetAllInputDevices(InputDeviceIDs);

			int ControllersConnected = InputDeviceIDs.Num();
			if (ControllersConnected % 2 == 0 && ControllersConnected)
			{
				int PlayerControllers = UGameplayStatics::GetNumPlayerControllers(GetWorld());
				// Remove additional player controllers
				for (int i = 1; i < PlayerControllers; i++)
					UGameplayStatics::RemovePlayer(UGameplayStatics::GetPlayerController(GetWorld(), i), true);
				// Add additional player controllers up to the amount of devices currently connected
				for (int i = 1; i < InputDeviceIDs.Num(); i++)
                {
                    UGameplayStatics::CreatePlayer(GetWorld(), -1, false);				
                }
					
				// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d")));
				// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, ToString(MenuWidgetContainer));
				GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());
				PlayerOwner->bShowMouseCursor = false;
				PlayerOwner->SetInputMode(FInputModeGameOnly());
				if (GoToMainLevel)
				{
					UGameplayStatics::OpenLevel(this, FName("LV_Gameplay"), true);
				}
			}
		}
	}
}

