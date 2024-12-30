// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/Tower/USTowerBase.h"
#include "AbilitySystemComponent.h"
#include "../Stat/USTowerStatAttributeSet.h"

// Sets default values
AUSTowerBase::AUSTowerBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<UUSTowerStatAttributeSet>(TEXT("AttributeSet"));
}

// Called when the game starts or when spawned
void AUSTowerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUSTowerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUSTowerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

