// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "USTowerUpgradeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UUSTowerUpgradeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOWERDEFENSE_API IUSTowerUpgradeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual int32 GetTowerID() { return 0; }
	virtual void SetTowerID(int32 InTowerID) { TowerID = InTowerID; }

	int32 TowerID = 0;
};