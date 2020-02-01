// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	ATile();

protected:
	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	FVector MinSpawningExtent;

	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	FVector MaxSpawningExtent;

	UPROPERTY(EditDefaultsOnly, Category = Spawning)
	FVector NavMeshBoundsOffset;

private:
	class UActorPool *NavMeshPool;

	AActor *NavMesh;

public:	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Generation)
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float MinScale = 1.f, float MaxScale = 1.f, float Radius = 500);

	UFUNCTION(BlueprintCallable, Category = Pooling)
	void SetNavMeshPool(UActorPool *NavMeshPoolToSet);

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	bool CanSpawnAtLocation(FVector Location, float Radius);

	bool FindEmptyLocation(float Radius, FVector &OutLocation);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint, float YawRotation, float Scale);
};
