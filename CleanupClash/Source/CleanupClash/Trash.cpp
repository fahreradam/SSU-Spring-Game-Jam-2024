// Fill out your copyright notice in the Description page of Project Settings.


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
	SpecialMovement();
	Super::Tick(DeltaTime);

}

void ATrash::SpecialMovement()
{
	AddActorWorldRotation(FRotator(0,0.5,0));
	if (Interp)
	{
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), Location, GetWorld()->DeltaTimeSeconds, 3));
		
		if(FVector::Distance(GetActorLocation(), Location) < 2)
		{
			Interp = false;
		}
	}
	else
	{
		if(LerpUp)
		{
			SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), FVector(Location.X, Location.Y, Location.Z+OffSet), GetWorld()->DeltaTimeSeconds, 20));
			if(FVector::Distance(GetActorLocation(), FVector(Location.X, Location.Y, Location.Z+OffSet)) < 0.5)
			{
				LerpUp = false;
			}
		}
		else
		{
			SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), FVector(Location.X, Location.Y, Location.Z-OffSet), GetWorld()->DeltaTimeSeconds, 20));
			if(FVector::Distance(GetActorLocation(), FVector(Location.X, Location.Y, Location.Z-OffSet)) < 0.5)
			{
				LerpUp = true;
			}
		}
	}
}


