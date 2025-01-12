// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/GA/GameplayAbility_TripleAttack.h"
#include "../AT/AbilityTask_TrackingProjectile.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "../Tag/USGameplayTag.h"


UGameplayAbility_TripleAttack::UGameplayAbility_TripleAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
}

void UGameplayAbility_TripleAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	TargetActor = TriggerEventData->Target.Get();
	LaunchFirstProjectileTask();

	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), ActionMontage, 1.0);
	PlayAttackTask->ReadyForActivation();

	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(const_cast<AActor*>(ActorInfo->OwnerActor.Get()));

	if (ASC && CooldownEffect)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		ASC->BP_ApplyGameplayEffectToSelf(CooldownEffect, 1, EffectContext);
	}
}

void UGameplayAbility_TripleAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_TripleAttack::OnCompleteCallback(const class AActor* Target)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(const_cast<AActor*>(Target));

	if (ASC && AttackDamageEffect)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle EffectSpec = ASC->MakeOutgoingSpec(AttackDamageEffect, 1.0f, EffectContext);
		EffectSpec.Data->SetSetByCallerMagnitude(USTAG_TOWER_SKILL_DAMAGE, 20.0f);

		ASC->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(), ASC);
	}
}

void UGameplayAbility_TripleAttack::OnLastCompleteCallback(const AActor* Target)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(const_cast<AActor*>(Target));

	if (ASC && AttackDamageEffect)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle EffectSpec = ASC->MakeOutgoingSpec(AttackDamageEffect, 1.0f, EffectContext);
		EffectSpec.Data->SetSetByCallerMagnitude(USTAG_TOWER_SKILL_DAMAGE, 20.0f);
	}

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_TripleAttack::OnInterruptedCallback()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_TripleAttack::LaunchProjectile(bool bLastAttack)
{
	if (TargetActor.IsValid())
	{
		UAbilityTask_TrackingProjectile* TrackingProjectileTask = UAbilityTask_TrackingProjectile::CreateTask(this, TargetActor.Get(), ProjectileClass, InitialSpeed, HomingAccelerationMagnitude);
		if (bLastAttack)
		{
			TrackingProjectileTask->OnCompleted.AddDynamic(this, &UGameplayAbility_TripleAttack::OnLastCompleteCallback);
		}
		else
		{
			TrackingProjectileTask->OnCompleted.AddDynamic(this, &UGameplayAbility_TripleAttack::OnCompleteCallback);
		}

		TrackingProjectileTask->OnInterrupted.AddDynamic(this, &UGameplayAbility_TripleAttack::OnInterruptedCallback);
		TrackingProjectileTask->ReadyForActivation();
	}
}

void UGameplayAbility_TripleAttack::LaunchFirstProjectileTask()
{
	LaunchProjectile(false);
	UAbilityTask_WaitDelay* DelayTask = UAbilityTask_WaitDelay::WaitDelay(this, FireInterval);
	DelayTask->OnFinish.AddDynamic(this, &UGameplayAbility_TripleAttack::LaunchSecondProjectileTask);
	DelayTask->ReadyForActivation();
}

void UGameplayAbility_TripleAttack::LaunchSecondProjectileTask()
{
	LaunchProjectile(false);
	UAbilityTask_WaitDelay* DelayTask = UAbilityTask_WaitDelay::WaitDelay(this, FireInterval);
	DelayTask->OnFinish.AddDynamic(this, &UGameplayAbility_TripleAttack::LaunchThirdProjectileTask);
	DelayTask->ReadyForActivation();
}

void UGameplayAbility_TripleAttack::LaunchThirdProjectileTask()
{
	LaunchProjectile(true);
}
