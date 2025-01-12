// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "USUnit.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnitDeath, class AActor*, Actor);

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
	virtual void PossessedBy(AController* NewController) override;
	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void RunBehaviorTree();
	void IdleBehaviorTree();

	UFUNCTION()
	void RecordPath();
	FVector GetRecordPostion(float Distance);

	void SetWaypoint(FVector InWaypoint);
	void UpdateWaypoint();

	void SetNiagara(TObjectPtr<class UNiagaraSystem> NiagaraSystem);

	void SetMatchingActor(AUSUnit* TargetActor);
	void CombatState(bool bState);

	void GiveAbility(TArray<TSubclassOf<class UGameplayAbility>> Abilities);

	void StopAction();

	UFUNCTION()
	void OnHealthChange();

	void SetHealth(float Health);
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

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBehaviorTree> BehaviorTree;

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBehaviorTree> IdleBehavior;

	
	UPROPERTY()
	TObjectPtr<class UNiagaraComponent> NiagaraEffect;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UFloatingPawnMovement> FloatingPawnMovement;

protected:
	FTimerHandle RecordPathTimerHandle;
	TArray<FVector> PathHistory;
	float RecordInterval = 0.2;
	int32 MaxPathPoints = 100;

	FVector TargetWaypoint;
	bool IsReady = true;
public:
	FOnUnitDeath OnUnitDeath;
};
