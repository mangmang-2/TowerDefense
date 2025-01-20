// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/GA/Base/GameplayAbility_ArrowAttack.h"
#include "../../AT/AbilityTask_TrackingProjectile.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "../../Tag/USGameplayTag.h"
#include "Abilities/GameplayAbility.h"


UGameplayAbility_ArrowAttack::UGameplayAbility_ArrowAttack()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
}

void UGameplayAbility_ArrowAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	AActor* OnwerActor = const_cast<AActor*>(TriggerEventData->Target.Get());
	const USkillOptionalData* LoadData = Cast<const USkillOptionalData>(TriggerEventData->OptionalObject);
	if (LoadData && LoadData->OldTarget)
	{
		OnwerActor = const_cast<AActor*>(LoadData->OldTarget);
	}

	CopiedDelegate = LoadData->OnSkillComplete;

	UAbilityTask_TrackingProjectile* TrackingProjectileTask = UAbilityTask_TrackingProjectile::CreateTask(this, OnwerActor, TriggerEventData->Target.Get(), ProjectileClass, InitialSpeed, HomingAccelerationMagnitude);
	TrackingProjectileTask->OnCompleted.AddDynamic(this, &UGameplayAbility_ArrowAttack::OnCompleteCallback);
	TrackingProjectileTask->OnInterrupted.AddDynamic(this, &UGameplayAbility_ArrowAttack::OnInterruptedCallback);
	
	TrackingProjectileTask->ReadyForActivation();

	UAbilityTask_PlayMontageAndWait* PlayAttackTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, TEXT("PlayAttack"), ActionMontage, 1.0);
	PlayAttackTask->ReadyForActivation();
}

void UGameplayAbility_ArrowAttack::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_ArrowAttack::OnCompleteCallback(const class AActor* Target)
{
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(const_cast<AActor*>(Target));

	if (ASC && AttackDamageEffect)
	{
		FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle EffectSpec = ASC->MakeOutgoingSpec(AttackDamageEffect, 1.0f, EffectContext);
		EffectSpec.Data->SetSetByCallerMagnitude(USTAG_TOWER_SKILL_DAMAGE, AttackDamage);

		ASC->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(), ASC);
	}

	CopiedDelegate.Broadcast(GetActorInfo().AvatarActor.Get(), Target);
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_ArrowAttack::OnInterruptedCallback()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
