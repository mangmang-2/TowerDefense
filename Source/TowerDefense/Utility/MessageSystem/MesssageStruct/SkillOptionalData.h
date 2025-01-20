// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "SkillOptionalData.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillComplete, const AActor*, Target);

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API USkillOptionalData : public UObject
{
	GENERATED_BODY()

public:
	FVector LastTargetLocation;
	FVector TargetSkillLocation;
	FOnSkillComplete OnSkillComplete;
};
