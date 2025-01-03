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

    ProjectileMovement->bRotationFollowsVelocity = true; // ����ü �̵� ���⿡ ���� ȸ��
    ProjectileMovement->ProjectileGravityScale = 0.0f; // �߷� ������ ����
    ProjectileMovement->InitialSpeed = 500.0f; // �ʱ� �ӵ�
    ProjectileMovement->MaxSpeed = 500.0f; // �ִ� �ӵ�

    ProjectileMovement->bIsHomingProjectile = true;
    ProjectileMovement->HomingAccelerationMagnitude = 30.0f; // ���� �ӵ� ����

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

