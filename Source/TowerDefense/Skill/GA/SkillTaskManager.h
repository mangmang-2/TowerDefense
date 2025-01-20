// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SkillTaskManager.generated.h"

UENUM(BlueprintType)
enum class ETaskState : uint8
{
    Waiting,
    Executing,
    Completed
};

USTRUCT(BlueprintType)
struct FTask
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere)
    FGameplayTag TaskTag;

    UPROPERTY(EditAnywhere)
    ETaskState State = ETaskState::Waiting;

    UPROPERTY(EditAnywhere)
    FName CompletionFunctionName;
};

/**
 * 
 */
UCLASS(Blueprintable)
class TOWERDEFENSE_API USkillTaskManager : public UObject
{
	GENERATED_BODY()
	

public:
    UPROPERTY(EditAnywhere)
    TArray<FTask> TaskList;

    class AActor* OwnerActor = nullptr;
    void SetOwnerActor(class AActor* Actor);
    void SetTaskList(TArray<FTask> Tasks);

    UFUNCTION()
    void CompleteTask(const AActor* OldTarget, const AActor* NewTarget);

    UFUNCTION()
    void ExecuteTask(const AActor* OldTarget, const AActor* NewTarget);
};
