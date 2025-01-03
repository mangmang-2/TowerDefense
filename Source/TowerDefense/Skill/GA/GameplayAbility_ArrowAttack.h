// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_ArrowAttack.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameplayAbility_ArrowAttack : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGameplayAbility_ArrowAttack();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION()
	void OnCompleteCallback();

	static UGameplayAbility_ArrowAttack* CreateTask(UGameplayAbility* OwningAbility);

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;
};
