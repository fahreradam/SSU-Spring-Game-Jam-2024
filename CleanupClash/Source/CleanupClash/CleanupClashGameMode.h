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
<<<<<<< Updated upstream

	int CurrentNumPlayer = 0;

	float PlayerStunTime = 1.5;

	UFUNCTION(BlueprintCallable)
	ETeamName GiveTeamName();
=======
	// virtual void BeginPlay() override;
>>>>>>> Stashed changes
};



