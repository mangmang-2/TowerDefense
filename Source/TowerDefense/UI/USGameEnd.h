// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "USGameEnd.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UUSGameEnd : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetText(bool bVictory);
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextBlock_Title;
};
