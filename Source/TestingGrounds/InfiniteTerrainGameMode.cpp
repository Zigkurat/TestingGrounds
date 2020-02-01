// Fill out your copyright notice in the Description page of Project Settings.


#include "InfiniteTerrainGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerrainGameMode::AInfiniteTerrainGameMode() {
    NavMeshPool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Pool"));
}

void AInfiniteTerrainGameMode::PopulateBoundsVolumePool() {
    auto NavMeshIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());

    while (NavMeshIterator) {
        AddToPool(*NavMeshIterator);
        ++NavMeshIterator;
    }
}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume *NavMeshToAdd) {
    NavMeshPool->Add(NavMeshToAdd);
}