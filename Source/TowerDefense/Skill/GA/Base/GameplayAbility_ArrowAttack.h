// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "../../../Utility/MessageSystem/MesssageStruct/SkillOptionalData.h"
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
	void OnCompleteCallback(const class AActor* Target);
	
	UFUNCTION()
	void OnInterruptedCallback();

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameplayEffect> AttackDamageEffect;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> ActionMontage;

	UPROPERTY(EditAnywhere)
	float InitialSpeed = 500.0f;

	UPROPERTY(EditAnywhere)
	float HomingAccelerationMagnitude = 2000.0f;

	UPROPERTY(EditAnywhere)
	float AttackDamage = 20.0f;

	FOnSkillComplete CopiedDelegate;
};
