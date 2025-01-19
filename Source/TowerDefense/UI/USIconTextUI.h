// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Utility/DataTable/USTowerUIData.h"
#include "USIconTextUI.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UUSIconTextUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void ResponseMessage(struct FGameplayTag Channel, const struct FUSTowerUIData& Payload);

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock_Resource;

public:
	EHUDType HUDType;
};
