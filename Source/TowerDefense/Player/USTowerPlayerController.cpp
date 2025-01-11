// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/USTowerPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

void AUSTowerPlayerController::ProjectMouseToGroundPlane(FVector2D& ScreenPosition, FVector& Intersection, bool& bMousePostion)
{
	ScreenPosition = GetMouseViewportPosition(bMousePostion);
	if (bMousePostion == false)
		ScreenPosition = GetViewportCenter();

	Intersection = ProjectScreenPositionToGamePlane(ScreenPosition);
}

FVector2D AUSTowerPlayerController::GetViewportCenter()
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	return FVector2D(ViewportSizeX / 2.0f, ViewportSizeY / 2.0f);
}

FVector2D AUSTowerPlayerController::GetMouseViewportPosition(bool& bMousePostion)
{
	float LocationX, LocationY;
	bMousePostion = GetMousePosition(LocationX, LocationY);

	return FVector2D(LocationX, LocationY);
}


FVector AUSTowerPlayerController::ProjectScreenPositionToGamePlane(FVector2D ScreenPosition)
{
	FVector WorldPosition, WorldDirection;
	DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldPosition, WorldDirection);

	FVector LineEnd = WorldPosition + (WorldDirection * 100000.0f);
	FPlane APlane(FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 1.0f));

	FVector Intersection;
	float T;
	UKismetMathLibrary::LinePlaneIntersection(WorldPosition, LineEnd, APlane, T, Intersection);

	return Intersection;
}
