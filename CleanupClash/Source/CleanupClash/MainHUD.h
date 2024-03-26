// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

/**
 * 
 */
UCLASS()
class CLEANUPCLASH_API AMainHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	TSharedPtr<class SMainMenuWidget> MenuWidget;
	// ...the container is used to remove/add the menu to the screen
	TSharedPtr<class SWidget> MenuWidgetContainer;

public:
	virtual void BeginPlay() override;
	void ShowMenu();
	void RemoveMenu(bool GoToMainLevel);
};