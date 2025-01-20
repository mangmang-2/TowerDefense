// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Base.h"
#include "GameplayAbility_FindMonster.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameplayAbility_FindMonster : public UGameplayAbility_Base
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_FindMonster();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
};
