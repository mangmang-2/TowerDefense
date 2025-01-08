// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/USTowerUpgradeInterface.h"
#include "USTowerSpawnPoint.generated.h"

UCLASS()
class TOWERDEFENSE_API AUSTowerSpawnPoint : public AActor, public IUSTowerUpgradeInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUSTowerSpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UStaticMeshComponent> Mesh;
};
