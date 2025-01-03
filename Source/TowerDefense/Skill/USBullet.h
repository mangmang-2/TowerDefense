// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "USBullet.generated.h"

UCLASS()
class TOWERDEFENSE_API AUSBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUSBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetHomingTarget(const AActor* Target);
	void SetVelocity(FVector Velocity);

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraComponent> NiagaraEffect;

    UPROPERTY(EditAnywhere)
	TObjectPtr<class UNiagaraSystem> NiagaraSystem;
};
