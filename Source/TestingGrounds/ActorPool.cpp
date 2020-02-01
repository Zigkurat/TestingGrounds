// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorPool.h"

UActorPool::UActorPool()
{
	PrimaryComponentTick.bCanEverTick = true;
}

AActor *UActorPool::Checkout() {
	if (PooledActors.Num() == 0) {
		return nullptr;
	} else {
		return PooledActors.Pop();
	}
}

void UActorPool::Return(AActor *ActorToReturn) {
	PooledActors.Push(ActorToReturn);
}

void UActorPool::Add(AActor *ActorToAdd) {
	PooledActors.Push(ActorToAdd);
}