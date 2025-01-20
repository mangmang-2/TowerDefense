// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../../../Utility/MessageSystem/MesssageStruct/SkillOptionalData.h"
#include "GameplayAbility_PullMonsters.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameplayAbility_PullMonsters : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGameplayAbility_PullMonsters();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	void PullMonstersToCenter(const FVector& Center, float Radius);
	void MoveActorToLocation(AActor* Actor, const FVector& TargetLocation);
	void UpdateActorLocation(AActor* Actor, FVector StartLocation, FVector TargetLocation, float Duration, FTimerHandle TimerHandle);
	void CheckAllMonstersFinished();

protected:
	TMap<class AActor*, bool> MovingMonsters;
	TMap<class AActor*, float> MonsterElapsedTime;
	FOnSkillComplete CopiedDelegate;
	class AActor* TargetActor= nullptr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCurveFloat> MovementCurve;
};
