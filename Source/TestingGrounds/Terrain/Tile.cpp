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

TArray<FSpawnPosition> ATile::RandomSpawnPositions(FSpawnData SpawnData) 
{
	TArray<FSpawnPosition> SpawnPositions;

	int32 SpawnCount = FMath::RandRange(SpawnData.MinCount, SpawnData.MaxCount);
	for (int i = 0; i < SpawnCount; i++) {
		FSpawnPosition SpawnPosition;
		SpawnPosition.Scale = FMath::RandRange(SpawnData.MinScale, SpawnData.MaxScale);
		if (FindEmptyLocation(SpawnData.Radius * SpawnPosition.Scale, SpawnPosition.Location)) {
			SpawnPosition.YawRotation = FMath::RandRange(-180.f, 180.f);
			SpawnPositions.Add(SpawnPosition);
		}
	}

	return SpawnPositions;
}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, FSpawnData SpawnData) 
{
	TArray<FSpawnPosition> SpawnPositions = RandomSpawnPositions(SpawnData);
	for (FSpawnPosition SpawnPosition : SpawnPositions) {
		PlaceActor(ToSpawn, SpawnPosition);
	}
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ToSpawn, FSpawnData SpawnData) {
	TArray<FSpawnPosition> SpawnPositions = RandomSpawnPositions(SpawnData);
	for (FSpawnPosition SpawnPosition : SpawnPositions) {
		PlaceAIPawn(ToSpawn, SpawnPosition);
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

void ATile::PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition) {
	AActor *Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0.f, SpawnPosition.YawRotation, 0.f));
	Spawned->SetActorScale3D(FVector(SpawnPosition.Scale));
}

void ATile::PlaceAIPawn(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition) {
	APawn *Spawned = GetWorld()->SpawnActor<APawn>(ToSpawn);
	Spawned->SetActorRelativeLocation(SpawnPosition.Location);
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Spawned->SetActorRotation(FRotator(0.f, SpawnPosition.YawRotation, 0.f));
	Spawned->SpawnDefaultController();
	Spawned->Tags.Add(FName("NPC"));
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