// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/GA/GameplayAbility_SimpleAttack.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "../Tag/USGameplayTag.h"

UGameplayAbility_SimpleAttack::UGameplayAbility_SimpleAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbility_SimpleAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	TargetActor = TriggerEventData->Target.Get();
	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), ActionMontage, 1.0);
	PlayAttackTask->OnCompleted.AddDynamic(this, &ThisClass::OnCompleteCallback);
	PlayAttackTask->ReadyForActivation();
}

void UGameplayAbility_SimpleAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_SimpleAttack::OnCompleteCallback()
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(const_cast<AActor*>(TargetActor.Get()));

	if (ASC && AttackDamageEffect)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle EffectSpec = ASC->MakeOutgoingSpec(AttackDamageEffect, 1.0f, EffectContext);
		EffectSpec.Data->SetSetByCallerMagnitude(USTAG_TOWER_SKILL_DAMAGE, 10.0f);

		ASC->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(), ASC);
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
