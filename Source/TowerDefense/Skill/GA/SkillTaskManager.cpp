// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/GA/SkillTaskManager.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "../../Utility/MessageSystem/MesssageStruct/SkillOptionalData.h"
#include "Abilities/GameplayAbilityTypes.h"


void USkillTaskManager::SetOwnerActor(AActor* Actor)
{
    OwnerActor = Actor;
}

void USkillTaskManager::SetTaskList(TArray<FTask> Tasks)
{
    TaskList = Tasks;
}

void USkillTaskManager::CompleteTask(const AActor* OldTarget, const AActor* NewTarget)
{
    if (TaskList.IsEmpty())
        return;

    FTask Task = TaskList[0];
    TaskList.RemoveAt(0);

    if (Task.CompletionFunctionName.IsNone() == false)
    {
        UFunction* Function = GetOuter()->FindFunction(Task.CompletionFunctionName);
        if (Function)
        {
            void* VoidPointer = const_cast<AActor*>(NewTarget);

            GetOuter()->ProcessEvent(Function, VoidPointer);
        }
    }

    ExecuteTask(OldTarget, NewTarget);
}

void USkillTaskManager::ExecuteTask(const AActor* OldTarget, const AActor* NewTarget)
{
	if (TaskList.IsEmpty())
		return;

	FTask Task = TaskList[0];
    FGameplayEventData PayloadData;
    PayloadData.Target = NewTarget;
    USkillOptionalData* SkillData = NewObject<USkillOptionalData>();
    SkillData->OldTarget = OldTarget;
    SkillData->SkillLocation = NewTarget->GetActorLocation();
    SkillData->OnSkillComplete.AddDynamic(this, &ThisClass::CompleteTask);
    PayloadData.OptionalObject = SkillData;

    if (OwnerActor)
    {
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, Task.TaskTag, PayloadData);
    }
}
