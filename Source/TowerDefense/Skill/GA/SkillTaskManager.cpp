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

void USkillTaskManager::CompleteTask(const AActor* Target)
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
            void* VoidPointer = const_cast<AActor*>(Target);

            GetOuter()->ProcessEvent(Function, VoidPointer);
        }
    }

    ExecuteTask(Target);
}

void USkillTaskManager::ExecuteTask(const AActor* Target)
{
	if (TaskList.IsEmpty())
		return;

	FTask& Task = TaskList[0];
    FGameplayEventData PayloadData;
    PayloadData.Target = Target;
    USkillOptionalData* SkillData = NewObject<USkillOptionalData>();
    SkillData->TargetSkillLocation = Target->GetActorLocation();
    SkillData->LastTargetLocation = Task.LastTargetLocation; // 마지막 타겟의 위치 활용
    SkillData->OnSkillComplete.AddDynamic(this, &ThisClass::CompleteTask);
    PayloadData.OptionalObject = SkillData;

    if (TaskList.Num() > 1)
    {
        if(TaskList[1].bLastTargetLocation == true)
        {
            TaskList[1].LastTargetLocation = Target->GetActorLocation();
        }
        else
        {
            TaskList[1].LastTargetLocation = OwnerActor->GetActorLocation();
        }
    }

    if (OwnerActor)
    {
        UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OwnerActor, Task.TaskTag, PayloadData);
    }
}
