// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "USWaveData.generated.h"

/**
 * 
 */

 USTRUCT(BlueprintType)
struct FUSStageData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
    TSoftObjectPtr<UWorld> StageAsset;

	UPROPERTY(EditAnywhere)
	int32 Stage = -1;

	UPROPERTY(EditAnywhere)
	int32 Health;

	UPROPERTY(EditAnywhere)
	int32 Gold;
};

USTRUCT(BlueprintType)
struct FUSWaveData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	int32 Stage;

	UPROPERTY(EditAnywhere)
	int32 Wave;

	UPROPERTY(EditAnywhere)
	int32 MonsterNum;

	UPROPERTY(EditAnywhere)
	int32 MonsterBatch;

	UPROPERTY(EditAnywhere)
	FVector SpawnPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AUSUnit> MonsterClass;
};
