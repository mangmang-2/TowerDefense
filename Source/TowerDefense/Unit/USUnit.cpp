// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/USUnit.h"
#include "AbilitySystemComponent.h"
#include "../Tower/Stat/USTowerStatAttributeSet.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AUSUnit::AUSUnit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<UUSTowerStatAttributeSet>(TEXT("AttributeSet"));

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComponent;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UnitMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
	//SkeletalMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

}

// Called when the game starts or when spawned
void AUSUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUSUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUSUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

