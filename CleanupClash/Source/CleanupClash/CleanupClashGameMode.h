// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TeamName.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "CleanupClashGameMode.generated.h"

UCLASS(minimalapi)
class ACleanupClashGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACleanupClashGameMode();

	int CurrentNumPlayer = 0;

	float PlayerStunTime = 1.5;

	UFUNCTION(BlueprintCallable)
	ETeamName GiveTeamName();

	UFUNCTION(BlueprintCallable)
	void ReturnToMainMenu();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<APlayerStart*> StartPoints;

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
};



