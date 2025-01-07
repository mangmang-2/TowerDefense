// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/Unit/USUnitSpawner.h"
#include "../../Unit/USUnit.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"

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
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AUSUnitSpawner::SpawnActors, SpawnInterval, true, 1.0f);
    SpawnPoint = GetActorLocation();
}

// Called every frame
void AUSUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUSUnitSpawner::SpawnActors()
{
    if (RepeatCount == false && SpawnList.Num() >= MaxSpawnCount)
    {
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
        return;
    }

    for (int32 i = 0; i < BatchSpawnCount && SpawnList.Num() < MaxSpawnCount; ++i)
    {
        FVector SpawnLocation = SpawnPoint + FVector(FMath::RandRange(-100, 100), FMath::RandRange(-100, 100), 0);
        FRotator SpawnRotation = FRotator::ZeroRotator;

        AUSUnit* SpawnedActor = Cast<AUSUnit>(UAIBlueprintHelperLibrary::SpawnAIFromClass(
            GetWorld(),
            SpawnUnitClass,
            nullptr,
            SpawnLocation,
            SpawnRotation,
            true
        ));

        if (SpawnedActor)
        {
            SpawnedActor->OnUnitDeath.AddDynamic(this, &AUSUnitSpawner::DeathActors);
            FString AddressAsString = FString::Printf(TEXT("%p"), this);
            SpawnedActor->Tags.AddUnique(FName(AddressAsString));
            SpawnedActor->Tags.AddUnique(FName(TagName));
            
            SpawnList.Add(SpawnedActor);
            FVector Waypoint =  FindNearestNavMeshLocation(SpawnedActor->GetActorLocation());
            SpawnedActor->SetWaypoint(Waypoint);
        }
    }
    
}

void AUSUnitSpawner::InitData(int32 MaxCount, int32 BatchCount, float Interval, bool Repeat, TSubclassOf<class AUSUnit> UnitClass, FVector InSpawnPoint)
{
	MaxSpawnCount = MaxCount;
	BatchSpawnCount = BatchCount;
	SpawnInterval = Interval;
    RepeatCount = Repeat;
    SpawnUnitClass = UnitClass;
    SpawnPoint = InSpawnPoint;

    GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AUSUnitSpawner::SpawnActors, SpawnInterval, true);
}

void AUSUnitSpawner::SetWaypoint(FVector InWayPoint)
{
    WayPoint = InWayPoint;
}

void AUSUnitSpawner::DeathActors()
{
    TArray<AActor*> AllPawns;

    FString AddressAsString = FString::Printf(TEXT("%p"), this);
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), *AddressAsString, AllPawns);

    SpawnList.Empty();
    for (AActor* Actor : AllPawns)
    {
        if (AUSUnit* Unit = Cast<AUSUnit>(Actor))
        {
            SpawnList.Add(Unit);
        }
    }
}

FVector AUSUnitSpawner::FindNearestNavMeshLocation(const FVector& CurrentLocation)
{
    FNavLocation NearestNavLocation;
    UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());

    FVector QueryExtent(500.0f, 500.0f, 500.0f); // 검색 반경
    if (NavSystem && NavSystem->ProjectPointToNavigation(CurrentLocation, NearestNavLocation, QueryExtent))
    {
        return NearestNavLocation;
    }

    return CurrentLocation;
}

