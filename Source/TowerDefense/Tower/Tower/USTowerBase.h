// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../../Utility/DataTable/USTowerData.h"
#include "../Interface/USTowerUpgradeInterface.h"
#include "USTowerBase.generated.h"

UCLASS()
class TOWERDEFENSE_API AUSTowerBase : public APawn, public IUSTowerUpgradeInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUSTowerBase();
	AUSTowerBase(ETowerType InTowerType);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void InitTower(FUSTowerUpgradeData UpgradeData);
	float GetHealth();
protected:
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UGameplayAbility>> Abilities;

	UPROPERTY()
	TObjectPtr<class UUSTowerStatAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> AttckAnim;

	ETowerType TowerType;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UUSAttackerComponent> AttackerComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UUSTowerRangeComponent> TowerRangeComponent;

	float Health = 100;
	
	UPROPERTY(EditAnywhere)
	bool AttackAble = true;
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class UGameplayAbility>> TowerAbilities;
};
