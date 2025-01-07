// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "USTowerData.h"
#include "USTowerUpgradeSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UUSTowerUpgradeSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	TArray<FUSTowerUpgradeData> GetUpgradeDataListByParentID(int32 ParentID);
	FUSTowerUpgradeData GetUpgradeData(int32 TowerID);
};
