// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "USTowerMessage.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FUSTowerBuildMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FGameplayTag Verb;

    UPROPERTY(BlueprintReadWrite)
    int32 TowerID;

    UPROPERTY(BlueprintReadWrite)
    class AActor* OwnerActor;
};


USTRUCT(BlueprintType)
struct FUSTowerSelectUIMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FGameplayTag Verb;

    UPROPERTY(BlueprintReadWrite)
    int32 Message
 ;
};