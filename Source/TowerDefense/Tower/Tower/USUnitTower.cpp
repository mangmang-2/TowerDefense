// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/Tower/USUnitTower.h"
#include "../../Utility/DataTable/USTowerData.h"
#include "../Unit/USUnitSpawner.h"

AUSUnitTower::AUSUnitTower() : Super(ETowerType::Unit)
{
	UnitSpawner = CreateDefaultSubobject<AUSUnitSpawner>(TEXT("UnitSpawner"));
}

void AUSUnitTower::BeginPlay()
{
	Super::BeginPlay();

	UnitSpawner->InitData(3, 3, 1.0f, true, SpawnUnitClass, GetActorLocation());
}

void AUSUnitTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UnitSpawner->SetActorLocation(GetActorLocation());
}
