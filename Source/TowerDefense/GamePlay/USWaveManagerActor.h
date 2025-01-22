// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "USWaveManagerActor.generated.h"

UCLASS()
class TOWERDEFENSE_API AUSWaveManagerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUSWaveManagerActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTextureRenderTarget2D> RTDraw;

protected:
	int32 CurrentWave = 0;
	int32 CurrentHealth = 10;
	int32 CurrentGold = 0;

public:
	int32 GetCurrentGold() { return CurrentGold; }

protected:
	void NextWave();
	void SpawnMonsterTower(int32 Wave);

	void SendInfo();

protected:
	int32 RemainTime = 5;
	FTimerHandle RemainTimerHandle;
	FTimerHandle RemainTimerEndHandle;

	void StartRemainTimer();
	UFUNCTION()
	void StopRemainTimer();
	UFUNCTION()
	void SendRemainTime();

public:
	void IncreaseGold();
	void SetHeathPoint();
	void DescreaseHeathPoint(); // 몬스터마다 생명력이 다르면 모르겠지만..일단 1개씩제거
	void DescreaseGold(int32 Value);

	virtual void ResponseMessage(struct FGameplayTag Channel, const struct FUSGameData& Payload);

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUSGameEnd> GameEndClass;

	void ShowGameEndWidget(bool bVictory);
};
