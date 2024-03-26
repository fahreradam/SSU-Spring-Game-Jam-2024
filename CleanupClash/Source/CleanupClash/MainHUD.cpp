// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "SMainMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	ShowMenu();
}

void AMainHUD::ShowMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		MenuWidget = SNew(SMainMenuWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(
			SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(MenuWidget.ToSharedRef())
		);
		
		if (PlayerOwner)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Show Menu");
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
		GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());
		// UGameplayStatics::OpenLevel(this, )
		if (PlayerOwner)
		{
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameOnly());
			if (GoToMainLevel)
			{
				UGameplayStatics::OpenLevel(this, FName("LV_Gameplay"), true);
			}
		}
	}
}

