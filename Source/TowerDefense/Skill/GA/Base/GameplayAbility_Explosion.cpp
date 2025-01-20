// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/GA/Base/GameplayAbility_Explosion.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "../../Tag/USGameplayTag.h"
#include "../../../Utility/MessageSystem/MesssageStruct/SkillOptionalData.h"

UGameplayAbility_Explosion::UGameplayAbility_Explosion()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
}

void UGameplayAbility_Explosion::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	FVector ExplosionLocation = FVector::ZeroVector;
	const USkillOptionalData* LoadData = Cast<const USkillOptionalData>(TriggerEventData->OptionalObject);
	if (LoadData)
	{
		ExplosionLocation = LoadData->SkillLocation;
	}

    ExplosionEffect(ExplosionLocation);

    TArray<AActor*> TargetActors = FindActors(ExplosionLocation);
	ApplyDamage(TargetActors);

	LoadData->OnSkillComplete.Broadcast(GetActorInfo().AvatarActor.Get(), TriggerEventData->Target);
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UGameplayAbility_Explosion::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_Explosion::ExplosionEffect(FVector ExplosionLocation)
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        NiagaraEffect,
        ExplosionLocation,
        FRotator::ZeroRotator
    );
}

TArray<AActor*> UGameplayAbility_Explosion::FindActors(FVector ExplosionLocation)
{
	TArray<AActor*> FoundActors;
    TArray<AActor*> ReturnActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), APawn::StaticClass(), TEXT("Monster"), FoundActors);
	for (const auto& Actor : FoundActors)
	{
		FVector ActorLocation = Actor->GetActorLocation();
		if ((ExplosionLocation - ActorLocation).Length() < ExplosionRange)
		{
            ReturnActors.Add(Actor);
		}
	}
    return ReturnActors;
}

void UGameplayAbility_Explosion::ApplyDamage(TArray<AActor*> TargetActors)
{
	for (auto Target : TargetActors)
	{
		UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(const_cast<AActor*>(Target));

		if (ASC && AttackDamageEffect)
		{
			FGameplayEffectContextHandle EffectContext = ASC->MakeEffectContext();
			FGameplayEffectSpecHandle EffectSpec = ASC->MakeOutgoingSpec(AttackDamageEffect, 1.0f, EffectContext);
			EffectSpec.Data->SetSetByCallerMagnitude(USTAG_TOWER_SKILL_DAMAGE, AttackDamage);

			ASC->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(), ASC);
		}
	}
	
}
