// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TeamName.h"
#include "GameFramework/GameModeBase.h"
#include "CleanupClashGameMode.generated.h"

UCLASS(minimalapi)
class ACleanupClashGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACleanupClashGameMode();

	int CurrentNumPlayer = 0;

	UFUNCTION(BlueprintCallable)
	ETeamName GiveTeamName();
};



