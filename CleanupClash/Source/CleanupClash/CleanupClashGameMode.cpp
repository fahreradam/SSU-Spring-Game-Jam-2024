// Copyright Epic Games, Inc. All Rights Reserved.

#include "CleanupClashGameMode.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "MainHUD.h"
#include "SMainMenuWidget.h"

ACleanupClashGameMode::ACleanupClashGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	// PlayerControllerClass = AMenuPlayerController::StaticClass();
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

