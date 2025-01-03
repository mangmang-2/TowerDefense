// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/GA/GameplayAbility_ArrowAttack.h"
#include "../AT/AbilityTask_TrackingProjectile.h"
#include "Abilities/GameplayAbilityTypes.h"

UGameplayAbility_ArrowAttack::UGameplayAbility_ArrowAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
}

void UGameplayAbility_ArrowAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UAbilityTask_TrackingProjectile* TrackingProjectileTask = UAbilityTask_TrackingProjectile::CreateTask(this, TriggerEventData->Target.Get(), ProjectileClass);
	TrackingProjectileTask->OnCompleted.AddDynamic(this, &UGameplayAbility_ArrowAttack::OnCompleteCallback);
	TrackingProjectileTask->ReadyForActivation();
}

void UGameplayAbility_ArrowAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_ArrowAttack::OnCompleteCallback()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
