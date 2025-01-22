// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/DataTable/USStageSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "USStageSubsystem.h"
#include "../../GamePlay/USWaveManagerActor.h"

void UUSStageSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
	NextStage();
}

void UUSStageSubsystem::LoadStage(const FName& StageName)
{
	UGameplayStatics::OpenLevel(this, StageName);
}

void UUSStageSubsystem::LoadStageFromData(const FUSStageData& StageData)
{
	StageData.StageAsset.LoadSynchronous();
    if (StageData.StageAsset.IsValid())
    {
        FName StageName = StageData.StageAsset->GetFName();
        UGameplayStatics::OpenLevel(this, StageName);
    }
}

FUSStageData UUSStageSubsystem::GetStageData(int32 InStage)
{
	TArray<FUSStageData> DataList;
	UDataTable* DataTablePointer = LoadObject<UDataTable>(nullptr, TEXT("/Game/TowerDefance/DataTable/StageDataTable.StageDataTable"));
	if (DataTablePointer != nullptr)
	{
		TArray<FUSStageData*> AllRows;
		DataTablePointer->GetAllRows(nullptr, AllRows);

		for (const auto& Data : AllRows)
		{
			if (Data->Stage == InStage)
			{
				return *Data;
			}
		}
	}

	return FUSStageData();
}

FUSStageData UUSStageSubsystem::GetCurrentStageData()
{
	return GetStageData(CurrentStage);
}

void UUSStageSubsystem::NextStage()
{
	CurrentStage++;
	FUSStageData StageData = GetStageData(CurrentStage);
	LoadStageFromData(StageData);
}

TArray<FUSWaveData> UUSStageSubsystem::GetWaveData(int32 InStage, int32 Wave)
{
	TArray<FUSWaveData> ReturnList;
	TArray<FUSWaveData> DataList;
	UDataTable* DataTablePointer = LoadObject<UDataTable>(nullptr, TEXT("/Game/TowerDefance/DataTable/WaveDataTable.WaveDataTable"));
	if (DataTablePointer != nullptr)
	{
		TArray<FUSWaveData*> AllRows;
		DataTablePointer->GetAllRows(nullptr, AllRows);

		for (const auto& Data : AllRows)
		{
			if (Data->Stage == InStage && Data->Wave == Wave)
			{
				ReturnList.Add(*Data);
			}
		}
	}

	return ReturnList;
}

TArray<FUSWaveData> UUSStageSubsystem::CurrentStageWaveData(int32 Wave)
{
	return GetWaveData(CurrentStage, Wave);
}

bool UUSStageSubsystem::IsLastStage()
{
	return GetStageData(CurrentStage + 1).Stage == -1;
}

bool UUSStageSubsystem::IsLastWave(int32 Wave)
{
	return GetWaveData(CurrentStage, Wave + 1).IsEmpty();
}

void UUSStageSubsystem::SetWaveManagerActor(AUSWaveManagerActor* WaveActor)
{
	WaveManagerActor = WaveActor;
}

int32 UUSStageSubsystem::GetRemainGold()
{
	if(WaveManagerActor == nullptr)
		return 0;
	return WaveManagerActor->GetCurrentGold();
}

void UUSStageSubsystem::ConsumeGold(int32 GoldValue)
{
	if (WaveManagerActor)
	{
		WaveManagerActor->DescreaseGold(GoldValue);
	}
}

void UUSStageSubsystem::ConsumeHealthPoint()
{
	if (WaveManagerActor)
	{
		WaveManagerActor->DescreaseHeathPoint();
	}
}
