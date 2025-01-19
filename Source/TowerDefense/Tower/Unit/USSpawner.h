// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnitSpawn, class AUSUnit*, Unit);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnComplete);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UUSSpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUSSpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UFUNCTION()
    void SpawnActors();

	void SetWaypoint(FVector InWayPoint);

	UFUNCTION()
    void DeathActors(class AActor* Actor);

protected:
	FTimerHandle SpawnTimerHandle;
	UPROPERTY(EditAnywhere)
	bool RepeatCount = false;
	int32 SpawnCount = 0;

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

	UPROPERTY(EditAnywhere)
	FName TagName;

	TArray<TObjectPtr<class AUSUnit>> SpawnList;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UGameplayAbility>> Abilities;

public:
	FOnUnitSpawn OnUnitSpawn;
	void ReplaceUnitClass(TSubclassOf<class AUSUnit> UnitClass);

	FOnSpawnComplete OnSpawnComplete;
};
