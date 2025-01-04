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


protected:
	FTimerHandle SpawnTimerHandle;
	int32 CurrentSpawnCount = 0;

	bool RepeatCount = false;

	// 웨이포인트
	FVector WayPoint;

	UPROPERTY(EditAnywhere)
	int32 MaxSpawnCount = 20;

	UPROPERTY(EditAnywhere)
	int32 BatchSpawnCount = 5;

	UPROPERTY(EditAnywhere)
	float SpawnInterval = 3.0f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AUSUnit> SpawnUnitClass;
};
