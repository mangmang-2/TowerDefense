// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_CombatMatch.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UBTTaskNode_CombatMatch : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTaskNode_CombatMatch();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
