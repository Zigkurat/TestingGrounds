// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
    auto AIController = OwnerComp.GetAIOwner();
    auto ControlledPawn = AIController->GetPawn();
    auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
    if (!ensure(PatrolRoute)) {
        return EBTNodeResult::Failed;
    }

    auto PatrolPoints = PatrolRoute->GetPatrolPoints();
    if (!ensure(PatrolPoints.Num() > 0)) {
        return EBTNodeResult::Failed;
    }

    auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
    auto Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);
    BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

    auto NextIndex = (Index + 1) % PatrolPoints.Num();
    BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

    return EBTNodeResult::Succeeded;
}