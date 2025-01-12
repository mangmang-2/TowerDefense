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

public:
	UFUNCTION()
	void SpawnUnit(class AUSUnit* Unit);

	FVector FindNearestNavMeshLocation(const FVector& CurrentLocation);
	TArray<FVector> GetFormationPosition(const FVector& InWayPoint, float Width, float Height);

	void ResponseMessage(struct FGameplayTag Channel, const struct FUSTowerWaypointUIMessage& Payload);
	UFUNCTION()
	void DeathActors(class AActor* Actor);
public:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UUSSpawner> UnitSpawner;

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AUSUnit> SpawnUnitClass;

	UPROPERTY(EditAnywhere)
	bool bMonsterTower = false;

	FVector Waypoint;
	TArray<FVector> UnitFormation;
	float UnitFormationLength = 70;

	TArray<TObjectPtr<class AUSUnit>> Units;
};
