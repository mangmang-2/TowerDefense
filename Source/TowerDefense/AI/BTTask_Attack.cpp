// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../Skill/Tag/USGameplayTag.h"
#include "AbilitySystemBlueprintLibrary.h"

UBTTask_Attack::UBTTask_Attack()
{
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (BlackboardComp == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FGameplayEventData PayloadData;
	PayloadData.Target = Cast<AActor>(BlackboardComp->GetValueAsObject(TEXT("Target")));
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(ControllingPawn, USTAG_MESSAGE_UNIT_ATTACK, PayloadData);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, FTimerDelegate::CreateLambda([&]() {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		})
		, 3.0f, false);

	return EBTNodeResult::InProgress;
}
