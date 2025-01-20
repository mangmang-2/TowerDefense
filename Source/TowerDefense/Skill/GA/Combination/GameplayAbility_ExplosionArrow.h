// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_ExplosionArrow.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameplayAbility_ExplosionArrow : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	UGameplayAbility_ExplosionArrow();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	UFUNCTION()
	void OnExplosionComplete(const AActor* Target);
protected:
	UPROPERTY()
    TObjectPtr<class USkillTaskManager> SkillTaskManager;

	UPROPERTY(EditAnywhere)
    TArray<struct FTask> TaskList;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameplayAbility> Tasks;
	 
};
