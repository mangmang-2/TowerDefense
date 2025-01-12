// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "USTowerData.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ETowerType : uint8
{
	Unit			UMETA(DisplayName = "Unit"),
	Arrow			UMETA(DisplayName = "Arrow"),
	Magic			UMETA(DisplayName = "Magic"),
	Splash			UMETA(DisplayName = "Splash"),
	MAX				UMETA(DisplayName = "None"),
};


USTRUCT(BlueprintType)
struct FUSTowerData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	ETowerType TowerType;
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> AttckAnim;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USkeletalMesh> Mesh;
};


USTRUCT(BlueprintType)
struct FUSTowerUpgradeData : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	int32 TowerID = -1;

	UPROPERTY(EditAnywhere)
	ETowerType TowerType;

	UPROPERTY(EditAnywhere)
	int32 ParentID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UTexture2D> UIIcon;

	UPROPERTY(EditAnywhere)
	int32 UpgradeCost;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AUSTowerBase> TowerBaseClass;

	UPROPERTY(EditAnywhere)
	int32 AttackRange;

	UPROPERTY(EditAnywhere)
	int32 AttackDamage;

	UPROPERTY(EditAnywhere)
	int32 Health;
};
