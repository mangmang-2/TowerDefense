// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/Unit/USUnitSpawner.h"
#include "../../Unit/USUnit.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
AUSUnitSpawner::AUSUnitSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AUSUnitSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AUSUnitSpawner::SpawnActors, SpawnInterval, true);
}

// Called every frame
void AUSUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUSUnitSpawner::SpawnActors()
{
    if (RepeatCount == false && CurrentSpawnCount >= MaxSpawnCount)
    {
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
        return;
    }

    for (int32 i = 0; i < BatchSpawnCount && CurrentSpawnCount < MaxSpawnCount; ++i)
    {
        FVector SpawnLocation = GetActorLocation() + FVector(FMath::RandRange(-100, 100), FMath::RandRange(-100, 100), 0);
        FRotator SpawnRotation = FRotator::ZeroRotator;

        APawn* SpawnedActor = UAIBlueprintHelperLibrary::SpawnAIFromClass(
            GetWorld(),
            SpawnUnitClass,
            nullptr,
            SpawnLocation,
            SpawnRotation,
            true
        );

        if (SpawnedActor)
        {
            CurrentSpawnCount++;
        }
    }
    
}

