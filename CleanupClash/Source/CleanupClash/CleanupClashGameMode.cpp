// Copyright Epic Games, Inc. All Rights Reserved.

#include "CleanupClashGameMode.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "LevelHUD.h"
#include "MenuPlayerController.h"

ACleanupClashGameMode::ACleanupClashGameMode()
{
	PlayerControllerClass = AMenuPlayerController::StaticClass();
	HUDClass = ALevelHUD::StaticClass();
	// AMainHUD::RemoveMenu(false);
	// GEngine->GameViewport->RemoveViewportWidgetContent(.ToSharedRef());
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// PlayerControllerClass = AMenuPlayerController::StaticClass();

	TArray<AActor*> TempActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), TempActor);

	for (auto const Actor : TempActor)
	{
		StartPoints.Add(Cast<APlayerStart>(Actor));
	}
}

ETeamName ACleanupClashGameMode::GiveTeamName()
{
	ETeamName TeamName;
	switch (CurrentNumPlayer%2)
	{
	case 1:
		TeamName =  ETeamName::Team1;
		break;
	case 0:
		TeamName =  ETeamName::Team2;
		break;
	default:
		TeamName =  ETeamName::None;
		break;
	}

	CurrentNumPlayer++;
	return TeamName;
}

void ACleanupClashGameMode::ReturnToMainMenu()
{
	UGameplayStatics::OpenLevel(this, FName("LV_MainMenu"), true);
}

AActor* ACleanupClashGameMode::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	if (Player->StartSpot == nullptr)
		return StartPoints.Pop();
	return Player->StartSpot.Get();
}

