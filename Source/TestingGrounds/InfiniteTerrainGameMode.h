// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundsGameMode.h"
#include "InfiniteTerrainGameMode.generated.h"

UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrainGameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()
	
public:
	AInfiniteTerrainGameMode();

public:
	UFUNCTION(BlueprintCallable, Category = Pooling)
	void PopulateBoundsVolumePool();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pooling)
	class UActorPool *NavMeshPool;

private:
	void AddToPool(class ANavMeshBoundsVolume *NavMeshToAdd);
};