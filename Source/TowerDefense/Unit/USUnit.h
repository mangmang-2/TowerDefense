// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "USUnit.generated.h"

UCLASS()
class TOWERDEFENSE_API AUSUnit : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUSUnit();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<class UUSTowerStatAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UAnimMontage> AttckAnim;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UFloatingPawnMovement> FloatingPawnMovement;
};
