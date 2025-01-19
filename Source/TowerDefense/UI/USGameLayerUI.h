// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "USGameLayerUI.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UUSGameLayerUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUSIconTextUI> WBP_HealthPoint;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUSIconTextUI> WBP_Gold;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUSIconTextUI> WBP_WaveInfo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UUSIconTextUI> WBP_RemainTime;
};
