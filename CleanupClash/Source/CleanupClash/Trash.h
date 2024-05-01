﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trash.generated.h"

UCLASS()
class CLEANUPCLASH_API ATrash : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATrash();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BeginCollision();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TrashMesh)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Score)
	int TrashValue = 10;

	UPROPERTY(BlueprintReadWrite)
	FVector Location;

	bool Interp = true;

	bool LerpUp = true;
	
	UFUNCTION()
	void SpecialMovement();

	UPROPERTY(EditAnywhere)
	float OffSet = 1000; 
};
