// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_Explosion.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameplayAbility_Explosion : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_Explosion();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	void ExplosionEffect(FVector ExplosionLocation);
	TArray<AActor*> FindActors(FVector ExplosionLocation);
	void ApplyDamage(TArray<AActor*> TargetActors);


protected:

	UPROPERTY(EditAnywhere)
	float ExplosionRange = 300;

	UPROPERTY(EditAnywhere)
	float AttackDamage = 30;

    UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraSystem> NiagaraEffect;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameplayEffect> AttackDamageEffect;
};
