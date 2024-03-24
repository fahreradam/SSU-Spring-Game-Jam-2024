// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trash.h"
#include "Components/BoxComponent.h"
#include "TrashSpawner.generated.h"

UCLASS()
class CLEANUPCLASH_API ATrashSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrashSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SpawnDelay)
	float SpawnDelay = 1.0f;

	UFUNCTION(BlueprintCallable)
	void SpawnTrash();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ATrash> BPTrashActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* SpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* SpawnHeight;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	int GetNumTrash();

	UPROPERTY(BlueprintReadWrite)
	TArray<ATrash*> Trashes;
};
