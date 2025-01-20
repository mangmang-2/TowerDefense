// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/GA/Combination/GameplayAbility_ExplosionArrow.h"
#include "../SkillTaskManager.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "../../../Utility/MessageSystem/MesssageStruct/SkillOptionalData.h"

UGameplayAbility_ExplosionArrow::UGameplayAbility_ExplosionArrow()
{
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
}

void UGameplayAbility_ExplosionArrow::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(const_cast<AActor*>(ActorInfo->OwnerActor.Get()));

    if (SkillTaskManager == nullptr)
    {
        SkillTaskManager = NewObject<USkillTaskManager>(this);
    }
	SkillTaskManager->SetOwnerActor(ActorInfo->AvatarActor.Get());
    SkillTaskManager->SetTaskList(TaskList);
    SkillTaskManager->ExecuteTask(ActorInfo->AvatarActor.Get(), TriggerEventData->Target);

    EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_ExplosionArrow::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_ExplosionArrow::OnExplosionComplete(const AActor* Target)
{
}

