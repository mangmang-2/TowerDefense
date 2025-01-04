// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "USMonsterGoal.generated.h"

UCLASS()
class TOWERDEFENSE_API AUSMonsterGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUSMonsterGoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
                        const FHitResult& SweepResult);

protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<class UBoxComponent> BoxComponent;

};
