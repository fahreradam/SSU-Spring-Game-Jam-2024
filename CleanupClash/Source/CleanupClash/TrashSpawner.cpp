// Fill out your copyright notice in the Description page of Project Settings.


#include "TrashSpawner.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
ATrashSpawner::ATrashSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATrashSpawner::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATrashSpawner::SpawnTrash, SpawnDelay, true);	
}

// Called every frame
void ATrashSpawner::Tick(float DeltaTime)
{	
	Super::Tick(DeltaTime);
}

void ATrashSpawner::SpawnTrash()
{
	int const SpawnNum = FMath::RandRange(1, 10);
	for(int i = 0; i < SpawnNum; i++)
	{
		GetWorld()->SpawnActor<ATrash>(BPTrashActor, GetTransform());	
	}
	
}

