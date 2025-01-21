// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/Cue/GameplayCueNotify_DamageIndicate.h"
#include "../../UI/USDamageIndicatorActor.h"


bool UGameplayCueNotify_DamageIndicate::OnExecute_Implementation(AActor* Target, const FGameplayCueParameters& Parameters) const
{
	float DamageValue = Parameters.RawMagnitude;
	FVector SpawnLocation = Target->GetActorLocation() + FVector(0.f, 0.f, 100.f);

    UWorld* World = Target->GetWorld();
    if (World)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = Target;

        AUSDamageIndicatorActor* DamageIndicatorActor = World->SpawnActor<AUSDamageIndicatorActor>(DamageActor, SpawnLocation, FRotator::ZeroRotator, SpawnParams);
        if (DamageIndicatorActor)
        {
            DamageIndicatorActor->SetDamageValue(DamageValue);
        }
    }

	return true;
}
