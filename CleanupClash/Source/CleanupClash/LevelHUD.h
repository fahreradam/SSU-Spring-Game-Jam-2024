// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LevelHUD.generated.h"

/**
 * 
 */
UCLASS()
class CLEANUPCLASH_API ALevelHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	TSharedPtr<class SPauseMenuWidget> PauseWidget;
	// TSharedPtr<class 
	// ...the container is used to remove/add the menu to the screen
	TSharedPtr<class SWidget> MenuWidgetContainer;
	
public:
	virtual void BeginPlay() override;
	void ShowPauseMenu();
	void ShowGameMenu();
	void RemovePauseMenu();
	void ReturnToTitle();
};
