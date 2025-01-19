// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "USTowerUIData.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EHUDType : uint8
{
	HealthPoint		UMETA(DisplayName = "HealthPoint"),
	Gold			UMETA(DisplayName = "Gold"),
	WaveInfo		UMETA(DisplayName = "WaveInfo"),
	RemainTime		UMETA(DisplayName = "RemainTime"),
	MAX				UMETA(DisplayName = "None"),
};


USTRUCT(BlueprintType)
struct FUSTowerUIData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag Verb;

	EHUDType HUDType;
	FText InfoText;
};
