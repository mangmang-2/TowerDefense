// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/DataTable/USTowerUpgradeSubSystem.h"
#include "USTowerData.h"
#include "NativeGameplayTags.h"
#include "../MessageSystem/GameplayMessageSubsystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "../../Tower/Tower/USTowerBase.h"
#include "../MessageSystem/MesssageStruct/USTowerMessage.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_TowerBuild_Message, "Message.Tower.Build");

void UUSTowerUpgradeSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	// 서브 시스템간 순서 
	Collection.InitializeDependency<UGameplayMessageSubsystem>();

	Super::Initialize(Collection);

	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSubsystem.RegisterListener(TAG_TowerBuild_Message, this, &ThisClass::ResponseMessage);
}

TArray<FUSTowerUpgradeData> UUSTowerUpgradeSubSystem::GetUpgradeDataListByParentID(int32 ParentID)
{
	TArray<FUSTowerUpgradeData> UpgradeDataList;
	UDataTable* DataTablePointer = LoadObject<UDataTable>(nullptr, TEXT("/Game/TowerDefance/Tower/Data/TowerUpgradeData.TowerUpgradeData"));
	if (DataTablePointer != nullptr)
	{
		TArray<FUSTowerUpgradeData*> AllRows;
		DataTablePointer->GetAllRows(nullptr, AllRows);

		for (const auto& UpgradeData : AllRows)
		{
			if (UpgradeData->ParentID == ParentID)
			{
				UpgradeDataList.Add(*UpgradeData);
			}
		}
	}

	return UpgradeDataList;
}

FUSTowerUpgradeData UUSTowerUpgradeSubSystem::GetUpgradeData(int32 TowerID)
{
	TArray<FUSTowerUpgradeData> UpgradeDataList;
	UDataTable* DataTablePointer = LoadObject<UDataTable>(nullptr, TEXT("/Game/TowerDefance/Tower/Data/TowerUpgradeData.TowerUpgradeData"));
	if (DataTablePointer != nullptr)
	{
		TArray<FUSTowerUpgradeData*> AllRows;
		DataTablePointer->GetAllRows(nullptr, AllRows);

		for (const auto& UpgradeData : AllRows)
		{
			if (UpgradeData->TowerID == TowerID)
			{
				return *UpgradeData;
			}
		}
	}

	return FUSTowerUpgradeData();
}

void UUSTowerUpgradeSubSystem::SpawnTower(const FUSTowerBuildMessage& Payload)
{
	FUSTowerUpgradeData UpgradeData = GetUpgradeData(Payload.TowerID);
	if (UpgradeData.TowerID == -1)
		return;

	FVector ActorLocation = Payload.OwnerActor->GetActorLocation();
	Payload.OwnerActor->Destroy();

	ActorLocation.Z = 94;
	AUSTowerBase* TowerActor = Cast<AUSTowerBase>(UAIBlueprintHelperLibrary::SpawnAIFromClass(
		GetWorld(),
		UpgradeData.TowerBaseClass,
		nullptr,
		ActorLocation,
		FRotator::ZeroRotator,
		true
	));
	if (TowerActor)
	{
		TowerActor->SetTowerID(Payload.TowerID);
		TowerActor->InitTower(UpgradeData);
	}
}

void UUSTowerUpgradeSubSystem::ResponseMessage(FGameplayTag Channel, const FUSTowerBuildMessage& Payload)
{
	SpawnTower(Payload);
}