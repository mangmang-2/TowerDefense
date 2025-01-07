// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "USUnitSpawner.generated.h"

UCLASS()
class TOWERDEFENSE_API AUSUnitSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUSUnitSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
    void SpawnActors();

	void InitData(int32 MaxCount, int32 BatchCount, float Interval, bool Repeat, TSubclassOf<class AUSUnit> UnitClass, FVector InSpawnPoint);

	void SetWaypoint(FVector InWayPoint);

	UFUNCTION()
    void DeathActors();

	FVector FindNearestNavMeshLocation(const FVector& CurrentLocation);
protected:
	FTimerHandle SpawnTimerHandle;
	bool RepeatCount = false;

	// 웨이포인트
	FVector WayPoint;

	FVector SpawnPoint;

	UPROPERTY(EditAnywhere)
	int32 MaxSpawnCount = 20;

	UPROPERTY(EditAnywhere)
	int32 BatchSpawnCount = 5;

	UPROPERTY(EditAnywhere)
	float SpawnInterval = 3.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AUSUnit> SpawnUnitClass;

	UPROPERTY(EditAnywhere)
	FName TagName;

	TArray<TObjectPtr<class AUSUnit>> SpawnList;
};
