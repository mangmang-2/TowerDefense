// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "USTowerPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AUSTowerPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	void ProjectMouseToGroundPlane(FVector2D& ScreenPosition, FVector& Intersection, bool& bMousePostion);
	FVector2D GetViewportCenter();
	FVector2D GetMouseViewportPosition(bool& bMousePostion);
	FVector ProjectScreenPositionToGamePlane(FVector2D ScreenPosition);
};
