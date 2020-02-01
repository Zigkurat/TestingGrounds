// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile.h"
#include "Engine/World.h"
#include "NavigationSystem.h"
#include "../ActorPool.h"

ATile::ATile()
{
	PrimaryActorTick.bCanEverTick = true;

	MinSpawningExtent = FVector(0.f, -2000.f, 0.f);
	MaxSpawningExtent = FVector(4000.f, 2000.f, 0.f);
	NavMeshBoundsOffset = FVector(2000.f, 0.f, 0.f);
}

void ATile::BeginPlay()
{
	Super::BeginPlay();
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
	Super::EndPlay(EndPlayReason);

	NavMeshPool->Return(NavMesh);
}

void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn, int32 MaxSpawn, float MinScale, float MaxScale, float Radius) 
{
	int32 SpawnCount = FMath::RandRange(MinSpawn, MaxSpawn);

	for (int i = 0; i < SpawnCount; i++) {
		FVector SpawnPoint;
		float Scale = FMath::RandRange(MinScale, MaxScale);
		if (FindEmptyLocation(Radius * Scale, SpawnPoint)) {
			float YawRotation = FMath::RandRange(-180.f, 180.f);
			PlaceActor(ToSpawn, SpawnPoint, YawRotation, Scale);
		}
	}
}

bool ATile::CanSpawnAtLocation(FVector Location, float Radius) {
	FHitResult HitResult;
	FVector GlobalLocation = ActorToWorld().TransformPosition(Location);
	return !GetWorld()->SweepSingleByChannel(HitResult, GlobalLocation, GlobalLocation, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(Radius));
}

bool ATile::FindEmptyLocation(float Radius, FVector &OutLocation) {
	FBox Bounds(MinSpawningExtent, MaxSpawningExtent);

	for (int i = 0; i < 50; i++) {
		FVector CandidateLocation = FMath::RandPointInBox(Bounds);
		if (CanSpawnAtLocation(CandidateLocation, Radius)) {
			OutLocation = CandidateLocation;
			return true;
		}
	}

	return false;
}

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float YawRotation, float Scale) {
	AActor *Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPoint);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0.f, YawRotation, 0.f));
	Spawned->SetActorScale3D(FVector(Scale));
}

void ATile::SetNavMeshPool(UActorPool *NavMeshPoolToSet) {
	NavMeshPool = NavMeshPoolToSet;

	if (NavMeshPool != nullptr) {
		NavMesh = NavMeshPool->Checkout();
		if (NavMesh != nullptr) {
			NavMesh->SetActorLocation(GetActorLocation() + NavMeshBoundsOffset);
			FNavigationSystem::Build(*GetWorld());
		}
	}
}