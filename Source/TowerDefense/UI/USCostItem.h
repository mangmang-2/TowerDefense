// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Utility/DataTable/USTowerData.h"
#include "USCostItem.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UUSCostItem : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetData(class UTexture2D* TextureIcon, int32 CostValue);
	void SetData(FUSTowerUpgradeData UpgradeData);
	void SetActor(AActor* SelectedActor);

	UFUNCTION(BlueprintCallable)
	void BPButtonClick();

	void CreateTower();
	void DestroyUI();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UImage> Image_Icon;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock_Cost;

	FUSTowerUpgradeData TowerUpgradeData;
	AActor* OwnerActor = nullptr;
};
