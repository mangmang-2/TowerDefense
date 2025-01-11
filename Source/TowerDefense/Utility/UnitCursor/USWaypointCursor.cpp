// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/UnitCursor/USWaypointCursor.h"
#include "../../Utility/Component/USTowerRangeComponent.h"
#include "../../Utility/MessageSystem/MesssageStruct/USTowerMessage.h"
#include "NativeGameplayTags.h"
#include "../../Utility/MessageSystem/GameplayMessageSubsystem.h"
#include "NavigationSystem.h"
#include "../../Player/USTowerPlayerController.h"


UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UnitWaypoint_Message);



// Sets default values
AUSWaypointCursor::AUSWaypointCursor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TowerRangeComponent = CreateDefaultSubobject<UUSTowerRangeComponent>(TEXT("TowerRangeComponent"));
}

// Called when the game starts or when spawned
void AUSWaypointCursor::BeginPlay()
{
	Super::BeginPlay();
	TowerRangeComponent->SetRange(30);

}

// Called every frame
void AUSWaypointCursor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AUSTowerPlayerController* PlayerController = Cast<AUSTowerPlayerController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController == nullptr)
		return;
	FVector2D ViewportCenter = PlayerController->GetViewportCenter();

	FVector2D ScreenPos;
	FVector Intersection;
	bool bMousePostion = false;
	PlayerController->ProjectMouseToGroundPlane(ScreenPos, Intersection, bMousePostion);
	Intersection.Z += 95;
	SetActorLocation(Intersection);
}

bool AUSWaypointCursor::IsPointOnNavMesh(const FVector& Point)
{
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (NavSys == nullptr)
		return false;

	FNavLocation NavLocation;

	bool bIsOnNavMesh = NavSys->ProjectPointToNavigation(
		Point,
		NavLocation,
		FVector(10.0f, 10.0f, 100.0f)
	);

	return bIsOnNavMesh;
}

void AUSWaypointCursor::SetAddressAsString(FString Address)
{
	AddressAsString = Address;
}

void AUSWaypointCursor::MouseToGroundPlane(FVector Intersection)
{
	if (IsPointOnNavMesh(Intersection))
	{
		SendWaypointToUnit(Intersection);
	}
}


void AUSWaypointCursor::SendWaypointToUnit(FVector Intersection)
{
	FUSTowerWaypointUIMessage Message;
	Message.Verb = TAG_UnitWaypoint_Message;
	Message.AddressAsString = AddressAsString;
	Message.Waypoint = Intersection;

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSystem.BroadcastMessage(Message.Verb, Message);

	AddressAsString = TEXT("");

	
}
