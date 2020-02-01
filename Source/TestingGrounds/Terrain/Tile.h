// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition {
	GENERATED_USTRUCT_BODY();

	FVector Location;
	float YawRotation;
	float Scale;
};

USTRUCT(BlueprintType)
struct FSpawnData {
	GENERATED_USTRUCT_BODY();

	UPROPERTY(BlueprintReadWrite)
	int32 MinCount = 1; 
	UPROPERTY(BlueprintReadWrite)
	int32 MaxCount = 1; 
	UPROPERTY(BlueprintReadWrite)
	float MinScale = 1.f;
	UPROPERTY(BlueprintReadWrite)
	float MaxScale = 1.f;
	UPROPERTY(BlueprintReadWrite)
	float Radius = 500;
};

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
	UFUNCTION(BlueprintCallable, Category = Generation)
	void PlaceActors(TSubclassOf<AActor> ToSpawn, FSpawnData SpawnData);

	UFUNCTION(BlueprintCallable, Category = Generation)
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, FSpawnData SpawnData);

	UFUNCTION(BlueprintCallable, Category = Pooling)
	void SetNavMeshPool(UActorPool *NavMeshPoolToSet);

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	bool CanSpawnAtLocation(FVector Location, float Radius);

	template<class T>
	void PlaceActorsRandomly(TSubclassOf<T> ToSpawn, FSpawnData SpawnData);

	bool FindEmptyLocation(float Radius, FVector &OutLocation);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);
};
