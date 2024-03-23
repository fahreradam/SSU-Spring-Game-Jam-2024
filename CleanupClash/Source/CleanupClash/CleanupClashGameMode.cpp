// Copyright Epic Games, Inc. All Rights Reserved.

#include "CleanupClashGameMode.h"
#include "PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACleanupClashGameMode::ACleanupClashGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/BP_Player.BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
