// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill/USBullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"

// Sets default values
AUSBullet::AUSBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

    ProjectileMovement->bRotationFollowsVelocity = true; // 투사체 이동 방향에 따라 회전
    ProjectileMovement->ProjectileGravityScale = 0.0f; // 중력 영향을 끄기
    ProjectileMovement->InitialSpeed = 500.0f; // 초기 속도
    ProjectileMovement->MaxSpeed = 500.0f; // 최대 속도

    ProjectileMovement->bIsHomingProjectile = true;
    ProjectileMovement->HomingAccelerationMagnitude = 30.0f; // 유도 속도 설정

    NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
    NiagaraEffect->SetupAttachment(RootComponent);
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

}

void AUSBullet::SetHomingTarget(const AActor* Target)
{
    if (ProjectileMovement == nullptr)
        return;

    ProjectileMovement->HomingTargetComponent = Target->GetRootComponent();
}

void AUSBullet::SetVelocity(FVector Velocity)
{
    if(ProjectileMovement == nullptr)
        return; 

    ProjectileMovement->Velocity = Velocity;
}

