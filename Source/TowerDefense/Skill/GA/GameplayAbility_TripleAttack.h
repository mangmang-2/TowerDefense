// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_TripleAttack.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameplayAbility_TripleAttack : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UGameplayAbility_TripleAttack();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
	UFUNCTION()
	void OnCompleteCallback(const class AActor* Target);

	UFUNCTION()
	void OnLastCompleteCallback(const class AActor* Target);
	
	UFUNCTION()
	void OnInterruptedCallback();

	void LaunchProjectile(bool bLastAttack);
	UFUNCTION()
	void LaunchFirstProjectileTask();
	UFUNCTION()
	void LaunchSecondProjectileTask();
	UFUNCTION()
	void LaunchThirdProjectileTask();

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
	float FireInterval = 1.0f;

	UPROPERTY()
	TWeakObjectPtr<const class AActor> TargetActor;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameplayEffect> CooldownEffect;
	
	UPROPERTY(EditAnywhere)
	float AttackDamage = 20;
};
