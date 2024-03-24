// Fill out your copyright notice in the Description page of Project Settings.


#include "TrashSpawner.h"


// Sets default values
ATrashSpawner::ATrashSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>("SpawnerMesh");

	RootComponent = SpawnerMesh;

	SpawnerMesh->SetCollisionProfileName("BlockAll");
	SpawnerMesh->SetHiddenInGame(true);

	SpawnArea = CreateDefaultSubobject<UBoxComponent>("SpawnArea");
	SpawnArea->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>("SpawnPointMesh");
	SpawnPoint->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpawnPoint->SetHiddenInGame(true);

	SpawnHeight = CreateDefaultSubobject<UStaticMeshComponent>("TrashSpawnHeight");
	SpawnHeight->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SpawnHeight->SetHiddenInGame(true);


	


}

// Called when the game starts or when spawned
void ATrashSpawner::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATrashSpawner::Tick(float DeltaTime)
{
	if (GetNumTrash() == 0)
		SpawnTrash();
	Super::Tick(DeltaTime);
}

void ATrashSpawner::SpawnTrash()
{
	int SpawnNum = 0;

	while (SpawnNum%2 == 0)
	{
		SpawnNum = FMath::RandRange(3, 9);
	}
	for(int i = 0; i < SpawnNum; i++)
	{
		FVector SpawnLocation = FMath::RandPointInBox(SpawnArea->Bounds.GetBox());

		SpawnLocation.Z = SpawnHeight->GetComponentLocation().Z;
		ATrash* Trash = GetWorld()->SpawnActor<ATrash>(BPTrashActor, SpawnPoint->GetComponentLocation(), GetActorRotation());

		Trash->Location = SpawnLocation;
	}	
}

