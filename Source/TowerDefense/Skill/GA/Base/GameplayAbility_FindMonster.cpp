// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/GA/Base/GameplayAbility_FindMonster.h"
#include "../../../Utility/MessageSystem/MesssageStruct/SkillOptionalData.h"
#include "Kismet/GameplayStatics.h"

UGameplayAbility_FindMonster::UGameplayAbility_FindMonster()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
}

void UGameplayAbility_FindMonster::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	const AActor* ClosestActor = TriggerEventData->Target;
	if (ClosestActor == nullptr)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Monster"), FoundActors);
	if (FoundActors.Num() > 0)
	{
		float ClosestDistance = FLT_MAX;
		FVector OwnerActorLocation = TriggerEventData->Target->GetActorLocation();
		for (const auto& Actor : FoundActors)
		{
			if (Actor == TriggerEventData->Target)
				continue;

			FVector ActorLocation = Actor->GetActorLocation();
			if ((OwnerActorLocation - ActorLocation).Length() < ClosestDistance)
			{
				ClosestDistance = (OwnerActorLocation - ActorLocation).Length();
				ClosestActor = Actor;
			}
		}
	}

	TargetActor = const_cast<AActor*>(ClosestActor);
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}
