// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayAbility_BackTeleport.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameplayAbility_BackTeleport : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGameplayAbility_BackTeleport();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	FVector CalculateBacktrackLocation(AActor* Target, float Distance);

	float TeleportDistance = 500;       // 텔레포트할 거리


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UGameplayEffect> CooldownEffect;
};
