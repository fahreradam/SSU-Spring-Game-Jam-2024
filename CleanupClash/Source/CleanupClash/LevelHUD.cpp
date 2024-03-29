// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelHUD.h"
#include "SPauseMenuWidget.h"
#include "Widgets/SWeakWidget.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"


void ALevelHUD::BeginPlay()
{
	Super::BeginPlay();
}

void ALevelHUD::ShowPauseMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		PauseWidget = SNew(SPauseMenuWidget).OwningHUD(this);
		GEngine->GameViewport->AddViewportWidgetContent(
			SAssignNew(MenuWidgetContainer, SWeakWidget).PossiblyNullContent(PauseWidget.ToSharedRef())
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

void ALevelHUD::ShowGameMenu()
{
	if (GEngine && GEngine->GameViewport)
	{
		PauseWidget = SNew(SPauseMenuWidget).OwningHUD(this);
	}
}

void ALevelHUD::RemoveMenu(bool GoToMainLevel)
{
	if (GEngine && GEngine->GameViewport && MenuWidgetContainer.IsValid())
	{
		if (PlayerOwner)
		{
			GEngine->GameViewport->RemoveViewportWidgetContent(MenuWidgetContainer.ToSharedRef());
			PlayerOwner->bShowMouseCursor = false;
			PlayerOwner->SetInputMode(FInputModeGameOnly());
		}
	}
}
