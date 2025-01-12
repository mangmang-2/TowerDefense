// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/Unit/USSpawner.h"
#include "../../Unit/USUnit.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../Tower/USUnitTower.h"

// Sets default values for this component's properties
UUSSpawner::UUSSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUSSpawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
    GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &UUSSpawner::SpawnActors, SpawnInterval, true, 1.0f);

}


// Called every frame
void UUSSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UUSSpawner::SpawnActors()
{
    if (RepeatCount == false && SpawnCount >= MaxSpawnCount)
    {
        GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
        return;
    }

    for (int32 i = 0; i < BatchSpawnCount && SpawnList.Num() < MaxSpawnCount; ++i)
    {
        FVector SpawnLocation = GetOwner()->GetActorLocation() + FVector(FMath::RandRange(-100, 100), FMath::RandRange(-100, 100), 0);
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
            AUSUnitTower* UnitTower = Cast<AUSUnitTower>(GetOwner());
            if (UnitTower)
            {
                SpawnedActor->OnUnitDeath.AddDynamic(this, &UUSSpawner::DeathActors);
                FString AddressAsString = FString::Printf(TEXT("%p"), this);
                SpawnedActor->Tags.AddUnique(FName(AddressAsString));
                SpawnedActor->Tags.AddUnique(FName(TagName));
                SpawnedActor->GiveAbility(Abilities);
                SpawnedActor->SetHealth(UnitTower->GetHealth());
                OnUnitSpawn.Broadcast(SpawnedActor);

                SpawnList.Add(SpawnedActor);
                SpawnCount++;
            }
        }
    }
}

void UUSSpawner::SetWaypoint(FVector InWayPoint)
{
    WayPoint = InWayPoint;
}

void UUSSpawner::DeathActors(class AActor* Actor)
{
    SpawnList.RemoveAll([Actor](const TObjectPtr<class AUSUnit>& Item)
        {
            return Item == Actor;
        });
}


