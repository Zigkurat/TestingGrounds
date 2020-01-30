// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn) 
{
	FVector Min(0.f, -2000.f, 0.f);
	FVector Max(4000.f, 2000.f, 0.f);
	FBox Bounds(Min, Max);

	int32 SpawnCount = FMath::RandRange(MinSpawn, MaxSpawn);

	for (int i = 0; i < SpawnCount; i++) {
		FVector SpawnPoint = FMath::RandPointInBox(Bounds);

		AActor *Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
		Spawned->SetActorRelativeLocation(SpawnPoint);
		Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

bool ATile::CastSphere(FVector Location, float Radius) {
	FHitResult HitResult;
	return GetWorld()->SweepSingleByChannel(HitResult, Location, Location, FQuat::Identity, ECollisionChannel::ECC_Camera, FCollisionShape::MakeSphere(Radius));
}