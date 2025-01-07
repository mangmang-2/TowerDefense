// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Utility/DataTable/USTowerData.h"
#include "USTowerSelectUI.generated.h"


/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UUSTowerSelectUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void SetData(TArray<FUSTowerUpgradeData> DataList);
	void Insert(FUSTowerUpgradeData UpgradeData, FVector2D Pos);
	void SetActor(AActor* SelectedActor);

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


	void ResponseMessage(struct FGameplayTag Channel, const struct FUSTowerSelectUIMessage& Payload);
protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUSCostItem> CostItemClass;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UCanvasPanel> CanvasPanel_Item;

	AActor* OwnerActor = nullptr;
};
