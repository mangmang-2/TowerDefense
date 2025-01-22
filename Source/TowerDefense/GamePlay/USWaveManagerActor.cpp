// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlay/USWaveManagerActor.h"
#include "../Utility/DataTable/USStageSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "../Unit/USUnit.h"
#include "../Tower/Tower/USUnitTower.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "../Utility/MessageSystem/GameplayMessageSubsystem.h"
#include "NativeGameplayTags.h"
#include "../Utility/DataTable/USTowerUIData.h"
#include "../Utility/MessageSystem/MesssageStruct/USTowerMessage.h"
#include "../UI/USGameEnd.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Message_UI_HUDInfo)
UE_DEFINE_GAMEPLAY_TAG(TAG_Message_Game_Info, "Message.Game.Info")

// Sets default values
AUSWaveManagerActor::AUSWaveManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.5f;
}

// Called when the game starts or when spawned
void AUSWaveManagerActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (RTDraw)
		UKismetRenderingLibrary::ClearRenderTarget2D(this, RTDraw);

	SetHeathPoint();
	NextWave();

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::SendInfo);
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::StartRemainTimer);

	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.RegisterListener(TAG_Message_Game_Info, this, &ThisClass::ResponseMessage);

	UUSStageSubsystem* TowerUpgradeSubSystem = GetGameInstance()->GetSubsystem<UUSStageSubsystem>();
	if (TowerUpgradeSubSystem == nullptr)
		return;
	TowerUpgradeSubSystem->SetWaveManagerActor(this);
}

// Called every frame
void AUSWaveManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> TowerActors;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(),TEXT("MonsterTower"), TowerActors);

	TArray<AActor*> MonsterActor;
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), TEXT("Monster"), MonsterActor);

	if (TowerActors.Num() == 0 && MonsterActor.Num() == 0)
	{
		NextWave();
	}
}

void AUSWaveManagerActor::NextWave()
{
	UUSStageSubsystem* TowerUpgradeSubSystem = GetGameInstance()->GetSubsystem<UUSStageSubsystem>();
	if (TowerUpgradeSubSystem == nullptr)
		return;

	if (TowerUpgradeSubSystem->IsLastWave(CurrentWave))
	{
		if (TowerUpgradeSubSystem->IsLastStage())
		{
			// 종료 메세지
			ShowGameEndWidget(true);
		}
		else
		{
			TowerUpgradeSubSystem->NextStage();
		}
		return;
	}
	CurrentWave++;
	SpawnMonsterTower(CurrentWave);
	SendInfo();
	StartRemainTimer();
	IncreaseGold();
}

void AUSWaveManagerActor::SpawnMonsterTower(int32 Wave)
{
	UClass* BP_MonsterTowerClass = LoadObject<UClass>(nullptr, TEXT("/Game/TowerDefance/Monster/BP_MonsterTower.BP_MonsterTower_C"));
	if (BP_MonsterTowerClass == nullptr)
		return;

	UUSStageSubsystem* TowerUpgradeSubSystem = GetGameInstance()->GetSubsystem<UUSStageSubsystem>();
	if (TowerUpgradeSubSystem == nullptr)
		return;

	TArray<FUSWaveData> WaveDataList = TowerUpgradeSubSystem->CurrentStageWaveData(Wave);
	for (auto WaveData : WaveDataList)
	{
		if (WaveData.MonsterClass == nullptr)
			return;

		AUSUnitTower* TowerActor = Cast<AUSUnitTower>(GetWorld()->SpawnActor<AActor>(
			BP_MonsterTowerClass,
			WaveData.SpawnPoint,
			FRotator::ZeroRotator
		));

		if (TowerActor == nullptr)
			return;

		TowerActor->ReplaceUnitClass(WaveData.MonsterClass);
		TowerActor->Tags.Add(TEXT("MonsterTower"));
	}
}

void AUSWaveManagerActor::SendInfo()
{
	{
		FUSTowerUIData Message;
		Message.Verb = TAG_Message_UI_HUDInfo;
		Message.HUDType = EHUDType::HealthPoint;
		Message.InfoText = FText::FromString(FString::FromInt(CurrentHealth));

		UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
		MessageSystem.BroadcastMessage(Message.Verb, Message);
	}
	{
		FUSTowerUIData Message;
		Message.Verb = TAG_Message_UI_HUDInfo;
		Message.HUDType = EHUDType::Gold;
		Message.InfoText = FText::FromString(FString::FromInt(CurrentGold));

		UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
		MessageSystem.BroadcastMessage(Message.Verb, Message);
	}
	{
		FUSTowerUIData Message;
		Message.Verb = TAG_Message_UI_HUDInfo;
		Message.HUDType = EHUDType::WaveInfo;
		Message.InfoText = FText::FromString(FString::FromInt(CurrentWave));

		UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
		MessageSystem.BroadcastMessage(Message.Verb, Message);
	}
}

void AUSWaveManagerActor::StartRemainTimer()
{
	RemainTime = 5;
	StopRemainTimer();
	SendRemainTime();
	GetWorld()->GetTimerManager().SetTimer(
		RemainTimerHandle,
		this,
		&ThisClass::SendRemainTime,
		1.0f,
		true
	);

	GetWorld()->GetTimerManager().SetTimer(
		RemainTimerEndHandle,
		this,
		&ThisClass::StopRemainTimer,
		RemainTime + 1,
		false 
	);
}

void AUSWaveManagerActor::StopRemainTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(RemainTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(RemainTimerEndHandle);
}

void AUSWaveManagerActor::SendRemainTime()
{
	FUSTowerUIData Message;
	Message.Verb = TAG_Message_UI_HUDInfo;
	Message.HUDType = EHUDType::RemainTime;
	Message.InfoText = FText::FromString(FString::Printf(TEXT("%02d"), RemainTime--));

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSystem.BroadcastMessage(Message.Verb, Message);
}

void AUSWaveManagerActor::IncreaseGold()
{
	UUSStageSubsystem* TowerUpgradeSubSystem = GetGameInstance()->GetSubsystem<UUSStageSubsystem>();
	if (TowerUpgradeSubSystem == nullptr)
		return;

	FUSStageData StageData = TowerUpgradeSubSystem->GetCurrentStageData();
	CurrentGold += StageData.Gold;

	SendInfo();
}

void AUSWaveManagerActor::SetHeathPoint()
{
	UUSStageSubsystem* TowerUpgradeSubSystem = GetGameInstance()->GetSubsystem<UUSStageSubsystem>();
	if (TowerUpgradeSubSystem == nullptr)
		return;

	FUSStageData StageData = TowerUpgradeSubSystem->GetCurrentStageData();
	CurrentHealth = StageData.Health;

	SendInfo();
}

void AUSWaveManagerActor::DescreaseHeathPoint()
{
	CurrentHealth--;
	SendInfo();

	if(CurrentHealth <= 0)
		ShowGameEndWidget(false);
}

void AUSWaveManagerActor::DescreaseGold(int32 Value)
{
	CurrentGold -= Value;
	SendInfo();
}

void AUSWaveManagerActor::ResponseMessage(FGameplayTag Channel, const FUSGameData& Payload)
{
	if(Payload.GameInfo == EGameInfo::Gold)
	{
		DescreaseGold(Payload.Value);
	}
	if(Payload.GameInfo == EGameInfo::Health)
	{
		DescreaseHeathPoint();
	}
}

void AUSWaveManagerActor::ShowGameEndWidget(bool bVictory)
{
	UUSGameEnd* GameEnd = CreateWidget<UUSGameEnd>(GetWorld(), GameEndClass, TEXT("GameEnd"));
	if (GameEnd == nullptr)
		return;

	GameEnd->AddToViewport();
	GameEnd->SetText(bVictory);
}
