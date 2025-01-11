// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "USWaypointCursor.generated.h"

UCLASS()
class TOWERDEFENSE_API AUSWaypointCursor : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUSWaypointCursor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UUSTowerRangeComponent> TowerRangeComponent;

	FString AddressAsString;

public:
	void SendWaypointToUnit(FVector Intersection);
	bool IsPointOnNavMesh(const FVector& Point);
	void SetAddressAsString(FString Address);
	void MouseToGroundPlane(FVector Intersection);
};
