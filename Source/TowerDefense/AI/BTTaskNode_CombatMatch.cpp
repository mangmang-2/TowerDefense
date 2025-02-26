// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_CombatMatch.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Unit/USUnit.h"

UBTTaskNode_CombatMatch::UBTTaskNode_CombatMatch()
{
    NodeName = "Combat Match";
}

EBTNodeResult::Type UBTTaskNode_CombatMatch::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
    if (BlackboardComp == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AUSUnit* TargetActor = Cast<AUSUnit>(BlackboardComp->GetValueAsObject(TEXT("Target")));
    AUSUnit* ControllingPawn = Cast<AUSUnit>(OwnerComp.GetAIOwner()->GetPawn());
    if (TargetActor == nullptr || ControllingPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }

    AAIController* AIController = Cast<AAIController>(TargetActor->GetController());
    if (AIController)
    {
        UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
        if (Blackboard)
        {
            AUSUnit* GoalActor = Cast<AUSUnit>(Blackboard->GetValueAsObject(TEXT("Target")));
            if (GoalActor != nullptr)
            {
                return EBTNodeResult::Failed;
            }
        }
    }

    TargetActor->SetMatchingActor(ControllingPawn);
    UE_LOG(LogTemp, Warning, TEXT("%s") , *TargetActor->GetName());
    return EBTNodeResult::Succeeded;
}