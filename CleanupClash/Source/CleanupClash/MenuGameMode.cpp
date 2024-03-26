// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGameMode.h"
#include "MainHUD.h"
#include "Engine/Engine.h"
#include "MenuPlayerController.h"
#include "SMainMenuWidget.h"

AMenuGameMode::AMenuGameMode()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "Menu Game Mode");
	PlayerControllerClass = AMenuPlayerController::StaticClass();
	HUDClass = AMainHUD::StaticClass();
}

