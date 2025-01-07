// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/DataTable/USTowerUpgradeSubSystem.h"
#include "USTowerData.h"

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
