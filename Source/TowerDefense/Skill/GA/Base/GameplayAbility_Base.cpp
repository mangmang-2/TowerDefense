// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/GA/Base/GameplayAbility_Base.h"
#include "Abilities/GameplayAbilityTypes.h"

void UGameplayAbility_Base::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (TriggerEventData)
	{
		const USkillOptionalData* LoadData = Cast<const USkillOptionalData>(TriggerEventData->OptionalObject);
		if (LoadData)
		{
			CopiedDelegate = LoadData->OnSkillComplete;
		}
	}
}

void UGameplayAbility_Base::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (CopiedDelegate.IsBound())
	{
		CopiedDelegate.Broadcast(TargetActor);
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
