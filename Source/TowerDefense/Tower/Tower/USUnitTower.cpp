// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/Tower/USUnitTower.h"
#include "../../Utility/DataTable/USTowerData.h"
#include "../Unit/USUnitSpawner.h"
#include "NavigationSystem.h"
#include "../../Unit/USUnit.h"
#include "../../Utility/MessageSystem/MesssageStruct/USTowerMessage.h"
#include "NativeGameplayTags.h"
#include "../../Utility/MessageSystem/GameplayMessageSubsystem.h"
#include "../../Utility/Component/USTowerRangeComponent.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_UnitWaypoint_Message, "Message.Unit.Waypoint");


AUSUnitTower::AUSUnitTower() : Super(ETowerType::Unit)
{
	UnitSpawner = CreateDefaultSubobject<AUSUnitSpawner>(TEXT("UnitSpawner"));
}

void AUSUnitTower::BeginPlay()
{
	Super::BeginPlay();

	FVector ActorLocation = GetActorLocation();
	ActorLocation.Z = 0;
	if (UnitSpawner)
	{
		UnitSpawner->InitData(1, 1, 1.0f, true, SpawnUnitClass, ActorLocation);
		UnitSpawner->OnUnitSpawn.AddDynamic(this, &ThisClass::SpawnUnit);
	}
	
	Waypoint = FindNearestNavMeshLocation(GetActorLocation());
	UnitFormation = GetFormationPosition(Waypoint, UnitFormationLength, UnitFormationLength);

	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSubsystem.RegisterListener(TAG_UnitWaypoint_Message, this, &ThisClass::ResponseMessage);
}

void AUSUnitTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUSUnitTower::SpawnUnit(AUSUnit* Unit)
{
	if(Unit == nullptr)
		return;

	Unit->SetWaypoint(UnitFormation[Units.Num()]);
	Unit->GiveAbility(Abilities);

	Units.Add(Unit);
}

FVector AUSUnitTower::FindNearestNavMeshLocation(const FVector& CurrentLocation)
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

TArray<FVector> AUSUnitTower::GetFormationPosition(const FVector& InWayPoint, float Width, float Height)
{
	TArray<FVector> FormationPositions;

	FVector Top = InWayPoint + FVector(0.0f, Height, 0.0f);

	FVector BottomLeft = InWayPoint + FVector(-Width, -Height, 0.0f);

	FVector BottomRight = InWayPoint + FVector(Width, -Height, 0.0f);

	FormationPositions.Add(Top);
	FormationPositions.Add(BottomLeft);
	FormationPositions.Add(BottomRight);

	return FormationPositions;
}


void AUSUnitTower::ResponseMessage(FGameplayTag Channel, const FUSTowerWaypointUIMessage& Payload)
{
	FString AddressAsString = FString::Printf(TEXT("%p"), this);
	if(Payload.AddressAsString != AddressAsString)
		return;

	float Range = (GetActorLocation() - Payload.Waypoint).Length();
	if( TowerRangeComponent->GetAttackRange() < Range)
		return;


	UnitFormation = GetFormationPosition(Payload.Waypoint, UnitFormationLength, UnitFormationLength);

	for (int32 i = 0; i < Units.Num(); i++)
	{
		Units[i]->SetWaypoint(UnitFormation[i]);
	}
	
}