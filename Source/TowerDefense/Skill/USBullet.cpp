// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/USBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Components/SphereComponent.h"

// Sets default values
AUSBullet::AUSBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

    ProjectileMovement->bRotationFollowsVelocity = true; // 투사체 이동 방향에 따라 회전
    ProjectileMovement->ProjectileGravityScale = 0.0f; // 중력 영향을 끄기

    ProjectileMovement->bIsHomingProjectile = true;

    NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
    NiagaraEffect->SetupAttachment(RootComponent);

    SetSpeed(500.0f, 2000.0f);

}

// Called when the game starts or when spawned
void AUSBullet::BeginPlay()
{
	Super::BeginPlay();
	
    if (NiagaraSystem)
    {
        NiagaraEffect->SetAsset(NiagaraSystem);
        NiagaraEffect->Activate();
    }
}

// Called every frame
void AUSBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (TargetActor.IsValid())
    {
        FVector CurrentLocation = GetActorLocation();
        FVector TargetLocation = TargetActor->GetActorLocation();

        float Distance = FVector::Dist(CurrentLocation, TargetLocation);

        if (Distance <= 50.0f)
        {
            OnTargetHit(TargetActor.Get());
        }
    }
    else
    {
        OnTargetHit(nullptr);
    }
}

void AUSBullet::SetHomingTarget(const AActor* Target)
{
    if (ProjectileMovement == nullptr)
        return;

    ProjectileMovement->HomingTargetComponent = Target->GetRootComponent();
    TargetActor = Target;
}

void AUSBullet::SetVelocity(FVector Velocity)
{
    if(ProjectileMovement == nullptr)
        return; 

    ProjectileMovement->Velocity = Velocity;
}

void AUSBullet::OnTargetHit(const AActor* Target)
{
    OnBulletHit.Broadcast(Target);

    Destroy();
}

void AUSBullet::OnTargetCancel()
{
    OnBulletCancel.Broadcast();

    Destroy();
}

void AUSBullet::SetSpeed(float InitialSpeed, float HomingAccelerationMagnitude)
{
    ProjectileMovement->InitialSpeed = InitialSpeed;
    ProjectileMovement->MaxSpeed = InitialSpeed;
    ProjectileMovement->HomingAccelerationMagnitude = HomingAccelerationMagnitude;
}
