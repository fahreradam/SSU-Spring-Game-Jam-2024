﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Trash.h"



// Sets default values
ATrash::ATrash()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("TrashMesh");
	Mesh->SetCollisionProfileName("OverlapAll");

	RootComponent = Mesh;

	TrashValue = FMath::RandRange(1, 30);

	
}

// Called when the game starts or when spawned
void ATrash::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrash::Tick(float DeltaTime)
{
	SetActorLocation(FMath::VInterpTo(GetActorLocation(), Location, GetWorld()->DeltaTimeSeconds, 3));
	Super::Tick(DeltaTime);

}

