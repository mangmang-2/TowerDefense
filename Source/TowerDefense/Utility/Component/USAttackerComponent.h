// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayAbilitySpec.h"
#include "USAttackerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UUSAttackerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUSAttackerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void SetAbilitySystemComponent(class UAbilitySystemComponent* AbilitySystemComponent);
	AActor* FindClosestMonster();
	void ActivateAbility(AActor* Target);
	void OwnerRotation(AActor* Target);
	void SetRange(float Range);

protected:
	UPROPERTY()
	TObjectPtr<class UAbilitySystemComponent> ASC;

	float AttackRange = 10000;

	TArray<struct FGameplayAbilitySpec> StartGiveAbility;
};
