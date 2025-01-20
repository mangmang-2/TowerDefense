// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/AT/AbilityTask_TrackingProjectile.h"
#include "../USBullet.h"


UAbilityTask_TrackingProjectile::UAbilityTask_TrackingProjectile()
{
    bTickingTask = true;
}

UAbilityTask_TrackingProjectile* UAbilityTask_TrackingProjectile::CreateTask(UGameplayAbility* OwningAbility, class AActor* OwnerActor, const class AActor* Target, TSubclassOf<AActor> InProjectileClass, float InitialSpeed, float HomingAccelerationMagnitude)
{
    UAbilityTask_TrackingProjectile* MyObj = NewAbilityTask<UAbilityTask_TrackingProjectile>(OwningAbility);
    MyObj->OwnerActor = OwnerActor;
    MyObj->TargetActor = Target;
    MyObj->InitialSpeed = InitialSpeed;
    MyObj->HomingAccelerationMagnitude = HomingAccelerationMagnitude;
    MyObj->ProjectileClass = InProjectileClass;
    
    return MyObj;
}

void UAbilityTask_TrackingProjectile::Activate()
{
    Super::Activate();


    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ActorLocation = OwnerActor->GetActorLocation() + OwnerActor->GetActorUpVector() * 50 + OwnerActor->GetActorForwardVector() * 50;
    ActorRotation = OwnerActor->GetActorRotation();

    AUSBullet* SpawnedBullet = GetWorld()->SpawnActor<AUSBullet>(
        ProjectileClass,
        ActorLocation,
        ActorRotation,
        SpawnParams
    );

    SpawnedBullet->SetHomingTarget(TargetActor);
    SpawnedBullet->SetVelocity(OwnerActor->GetActorForwardVector() * 1000);
    SpawnedBullet->SetSpeed(InitialSpeed, HomingAccelerationMagnitude);

    SpawnedBullet->OnBulletHit.AddDynamic(this, &UAbilityTask_TrackingProjectile::OnBulletHit);
    SpawnedBullet->OnBulletCancel.AddDynamic(this, &UAbilityTask_TrackingProjectile::OnBulletCancel);

}

void UAbilityTask_TrackingProjectile::OnDestroy(bool AbilityEnded)
{
    Super::OnDestroy(AbilityEnded);
}

void UAbilityTask_TrackingProjectile::TickTask(float DeltaTime)
{
    Super::TickTask(DeltaTime);
}

void UAbilityTask_TrackingProjectile::OnBulletHit(const AActor* Target)
{
    OnCompleted.Broadcast(Target);
    EndTask();
}


void UAbilityTask_TrackingProjectile::OnBulletCancel()
{
    OnInterrupted.Broadcast();
    EndTask();
}