// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower/Tower/USTowerBase.h"
#include "USUnitTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AUSUnitTower : public AUSTowerBase
{
	GENERATED_BODY()
	
public:
	AUSUnitTower();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class AUSUnitSpawner> UnitSpawner;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AUSUnit> SpawnUnitClass;

	FVector Waypoint;
};
