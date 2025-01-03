// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/AT/AbilityTask_TrackingProjectile.h"
#include "../USBullet.h"


UAbilityTask_TrackingProjectile::UAbilityTask_TrackingProjectile()
{
    bTickingTask = true;
}

UAbilityTask_TrackingProjectile* UAbilityTask_TrackingProjectile::CreateTask(UGameplayAbility* OwningAbility, const class AActor* Target, TSubclassOf<AActor> InProjectileClass)
{
    UAbilityTask_TrackingProjectile* MyObj = NewAbilityTask<UAbilityTask_TrackingProjectile>(OwningAbility);
    MyObj->OwnerActor = OwningAbility->GetActorInfo().AvatarActor;
    MyObj->TargetActor = Target;
    return MyObj;
}

void UAbilityTask_TrackingProjectile::Activate()
{
    Super::Activate();


    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ActorLocation = OwnerActor->GetActorLocation() + OwnerActor->GetActorUpVector() * 50 + OwnerActor->GetActorForwardVector() * 50;
    ActorRotation = OwnerActor->GetActorRotation();

    UClass* BulletClass = StaticLoadClass(
        AActor::StaticClass(),
        nullptr,
        TEXT("/Game/TowerDefance/Skill/BP_Bullet.BP_Bullet_C")
    );
    // ÃÑ¾Ë ½ºÆù
    AUSBullet* SpawnedBullet = GetWorld()->SpawnActor<AUSBullet>(
        BulletClass,
        ActorLocation,
        ActorRotation,
        SpawnParams
    );

    SpawnedBullet->SetHomingTarget(TargetActor);
    SpawnedBullet->SetVelocity(OwnerActor->GetActorForwardVector() * 1000);
}

void UAbilityTask_TrackingProjectile::OnDestroy(bool AbilityEnded)
{
    Super::OnDestroy(AbilityEnded);
}

void UAbilityTask_TrackingProjectile::TickTask(float DeltaTime)
{
    Super::TickTask(DeltaTime);

}
