// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/USTowerSpawnPoint.h"

// Sets default values
AUSTowerSpawnPoint::AUSTowerSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUSTowerSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUSTowerSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
