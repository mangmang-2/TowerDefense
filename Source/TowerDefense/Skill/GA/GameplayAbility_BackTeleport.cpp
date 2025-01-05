// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/GA/GameplayAbility_BackTeleport.h"
#include "../../Unit/USUnit.h"
#include "AIController.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

UGameplayAbility_BackTeleport::UGameplayAbility_BackTeleport()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGameplayAbility_BackTeleport::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    AActor* Target = const_cast<AActor*>(TriggerEventData->Target.Get());
    FVector TeleportLocation = CalculateBacktrackLocation(Target, TeleportDistance);

    DrawDebugLine(GetWorld(), TeleportLocation, TeleportLocation + FVector(0,0,10), FColor::Red, false, 2.0f, 0, 2.0f);

    Target->SetActorLocation(TeleportLocation);
    AAIController* AIController = Cast<AAIController>(Target->GetInstigatorController());
    if (AIController)
    {
        AIController->MoveToLocation(TeleportLocation);
    }
    
    UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(const_cast<AActor*>(ActorInfo->OwnerActor.Get()));

    if (ASC && CooldownEffect)
    {
        FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
        ASC->BP_ApplyGameplayEffectToSelf(CooldownEffect, 1, EffectContext);
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

void UGameplayAbility_BackTeleport::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}


FVector UGameplayAbility_BackTeleport::CalculateBacktrackLocation(AActor* Target, float Distance)
{
    if (Target == nullptr) 
        return FVector::ZeroVector;

    AUSUnit* Unit = Cast<AUSUnit>(Target);
    if(Unit == nullptr)
        return FVector::ZeroVector;

    return Unit->GetRecordPostion(Distance);
}