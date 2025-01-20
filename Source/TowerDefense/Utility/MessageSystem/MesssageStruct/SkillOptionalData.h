// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "SkillOptionalData.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSkillComplete, const AActor*, OldTarget, const AActor*, NewTarget);

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API USkillOptionalData : public UObject
{
	GENERATED_BODY()

public:
	const class AActor* OldTarget = nullptr;
	FVector SkillLocation;
	FOnSkillComplete OnSkillComplete;
};
