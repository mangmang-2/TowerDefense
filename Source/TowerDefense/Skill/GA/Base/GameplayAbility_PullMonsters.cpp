// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/GA/Base/GameplayAbility_PullMonsters.h"
#include "../../../Utility/MessageSystem/MesssageStruct/SkillOptionalData.h"
#include "Kismet/GameplayStatics.h"

UGameplayAbility_PullMonsters::UGameplayAbility_PullMonsters()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerExecution;
}

void UGameplayAbility_PullMonsters::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	const USkillOptionalData* LoadData = Cast<const USkillOptionalData>(TriggerEventData->OptionalObject);

	CopiedDelegate = LoadData->OnSkillComplete;
	TargetActor = const_cast<AActor*>(TriggerEventData->Target.Get());

	FVector SkillCenter = TargetActor->GetActorLocation();
	if (LoadData->LastTargetLocation != FVector::ZeroVector)
	{
		SkillCenter = LoadData->LastTargetLocation;
	}

	float PullRadius = 1000.0f;
	PullMonstersToCenter(SkillCenter, PullRadius);
}

void UGameplayAbility_PullMonsters::PullMonstersToCenter(const FVector& Center, float Radius)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Monster"), FoundActors);

	MovingMonsters.Empty();
	MonsterElapsedTime.Empty();
	for (AActor* Actor : FoundActors)
	{
		FVector ActorLocation = Actor->GetActorLocation();
		if ((Center - ActorLocation).Length() < Radius)
		{
			MovingMonsters.Add(Actor, false);
			MonsterElapsedTime.Add(Actor, 0.0f);
			MoveActorToLocation(Actor, Center);
		}
	}
}

void UGameplayAbility_PullMonsters::MoveActorToLocation(AActor* Actor, const FVector& TargetLocation)
{
	FVector StartLocation = Actor->GetActorLocation();
	float Duration = 0.2f;

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		FTimerDelegate::CreateUObject(this, &ThisClass::UpdateActorLocation, Actor, StartLocation, TargetLocation, Duration, TimerHandle),
		0.01f,
		true
	);

	Actor->SetActorLocation(TargetLocation, true);
}

void UGameplayAbility_PullMonsters::UpdateActorLocation(AActor* Actor, FVector StartLocation, FVector TargetLocation, float Duration, FTimerHandle TimerHandle)
{
	if (Actor == nullptr)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		return;
	}
	if (MonsterElapsedTime.Contains(Actor) == false)
	{
		MonsterElapsedTime.Add(Actor, 0.0f);
	}

	float& ElapsedTime = MonsterElapsedTime[Actor];
	ElapsedTime += 0.01f;

	//float Alpha = FMath::Clamp(ElapsedTime / Duration, 0.0f, 1.0f);
	float Alpha = MovementCurve ? MovementCurve->GetFloatValue(ElapsedTime) : FMath::Clamp(ElapsedTime, 0.0f, 1.0f);

	FVector NewLocation = FMath::Lerp(StartLocation, TargetLocation, Alpha);
	Actor->SetActorLocation(NewLocation);
	if (Alpha >= 1.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		ElapsedTime = 0.0f;

		if (MovingMonsters.Contains(Actor))
		{
			MovingMonsters[Actor] = true;
			CheckAllMonstersFinished();
		}
	}
}

void UGameplayAbility_PullMonsters::CheckAllMonstersFinished()
{
	bool bAllFinished = true;

	for (const auto& Pair : MovingMonsters)
	{
		if (Pair.Value == false)
		{
			bAllFinished = false;
			break;
		}
	}

	if (bAllFinished)
	{
		CopiedDelegate.Broadcast(TargetActor);
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}
