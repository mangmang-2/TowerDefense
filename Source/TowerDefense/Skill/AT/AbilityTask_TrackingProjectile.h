// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_TrackingProjectile.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTrackingProjectileComplete, const AActor*, Target);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTrackingProjectileInterrupted);
/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UAbilityTask_TrackingProjectile : public UAbilityTask
{
	GENERATED_BODY()
	

public:
	UAbilityTask_TrackingProjectile();
	static UAbilityTask_TrackingProjectile* CreateTask(UGameplayAbility* OwningAbility, const class AActor* Target, TSubclassOf<AActor> InProjectileClass, float InitialSpeed, float HomingAccelerationMagnitude);


	virtual void Activate() override;
	virtual void OnDestroy(bool AbilityEnded) override;

	virtual void TickTask(float DeltaTime) override;
	UFUNCTION()
	void OnBulletHit(const AActor* Target);

	UFUNCTION()
	void OnBulletCancel();
	
	UPROPERTY(BlueprintAssignable)
	FTrackingProjectileComplete	OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FTrackingProjectileInterrupted	OnInterrupted;
	

protected:
	TSubclassOf<AActor> ProjectileClass;

	const class AActor* TargetActor;
	TWeakObjectPtr<AActor> OwnerActor;
	FVector ActorLocation;
	FRotator ActorRotation;

	float InitialSpeed;
	float HomingAccelerationMagnitude;
	
};
