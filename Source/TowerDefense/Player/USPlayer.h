// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "USPlayer.generated.h"

UCLASS()
class TOWERDEFENSE_API AUSPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void BlueprintZoomFunc(float ActionValue);

	UFUNCTION(BlueprintCallable)
	void BPClickFunc();

public:
	void UpdateZoom();
	void Dof();
	void MoveTracking();
	
	void EdgeMode();
	FVector CursorDistFromViewportCenter(FVector2D ScreenPos);
	FVector2D CalculateEdgeMoveDistance();
	FVector2D OffsetMousePositionToCreateDeadZone(FVector2D ScreenPos, FVector2D Distance);
	FVector2D AdjustForNegativeDirection(FVector2D InputVector);
	void FindActorsAtIntersection(FVector Intersection, float Radius);
	void TowerSelectUI(AActor* SelectedActor);
	void ResponseMessage(struct FGameplayTag Channel, const struct FUSTowerWaypointUIMessage& Payload);

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<class USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UFloatingPawnMovement> FloatingPawnMovement;
		
	float ZoomDirection = 0.0f;
	float ZoomValue = 0.5;
	float EdgeMoveDistance = 50.0f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCurveFloat> ZoomCurve;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UInputMappingContext> BaseInputMappingContext;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUSTowerSelectUI> TowerSelectClass;

	class AUSWaypointCursor* WaypointCursor = nullptr;

};
