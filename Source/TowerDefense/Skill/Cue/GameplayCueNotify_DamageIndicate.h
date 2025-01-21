// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Static.h"
#include "GameplayCueNotify_DamageIndicate.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API UGameplayCueNotify_DamageIndicate : public UGameplayCueNotify_Static
{
	GENERATED_BODY()
	
public:
	virtual bool OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) const override;


protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AUSDamageIndicatorActor> DamageActor;
};
