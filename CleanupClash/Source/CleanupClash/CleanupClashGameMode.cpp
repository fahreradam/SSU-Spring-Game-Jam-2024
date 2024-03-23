// Copyright Epic Games, Inc. All Rights Reserved.

#include "CleanupClashGameMode.h"
#include "CleanupClashCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACleanupClashGameMode::ACleanupClashGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
