// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "USWaveData.h"
#include "USStageSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UUSStageSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	void Initialize(FSubsystemCollectionBase& Collection);

protected:
	int32 CurrentStage = 0;
	void LoadStage(const FName& StageName);
	void LoadStageFromData(const FUSStageData& StageData);

public:
	FUSStageData GetStageData(int32 InStage);
	FUSStageData GetCurrentStageData();

	void NextStage();

	TArray<FUSWaveData> GetWaveData(int32 InStage, int32 Wave);
	TArray<FUSWaveData> CurrentStageWaveData(int32 Wave);

	bool IsLastStage();
	bool IsLastWave(int32 Wave);


protected:
	class AUSWaveManagerActor* WaveManagerActor = nullptr;

public:
	void SetWaveManagerActor(class AUSWaveManagerActor* WaveActor);
	int32 GetRemainGold();
	void ConsumeGold(int32 GoldValue);

	void ConsumeHealthPoint();
};
