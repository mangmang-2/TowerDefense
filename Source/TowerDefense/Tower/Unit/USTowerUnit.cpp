// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/Unit/USTowerUnit.h"

// Sets default values
AUSTowerUnit::AUSTowerUnit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUSTowerUnit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUSTowerUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUSTowerUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

