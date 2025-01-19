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
    int32 Message;
};


USTRUCT(BlueprintType)
struct FUSTowerWaypointUIMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FGameplayTag Verb;

    UPROPERTY(BlueprintReadWrite)
    FString AddressAsString;

    UPROPERTY(BlueprintReadWrite)
    FVector Waypoint;
};


UENUM(BlueprintType)
enum class EGameInfo : uint8
{
	Health			UMETA(DisplayName = "Health"),
	Gold			UMETA(DisplayName = "Gold"),
	MAX				UMETA(DisplayName = "None"),
};

USTRUCT(BlueprintType)
struct FUSGameData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag Verb;

	UPROPERTY(EditAnywhere)
	EGameInfo GameInfo;

	UPROPERTY(EditAnywhere)
	int32 Value;
};
