// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/Unit/USUnitSpawner.h"

// Sets default values
AUSUnitSpawner::AUSUnitSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUSUnitSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUSUnitSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

