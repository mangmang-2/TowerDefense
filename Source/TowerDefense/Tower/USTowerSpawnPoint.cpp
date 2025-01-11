// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/USTowerSpawnPoint.h"
#include "../Utility/Component/GroundMaterialComponent.h"




// Sets default values
AUSTowerSpawnPoint::AUSTowerSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	GroundMaterial = CreateDefaultSubobject<UGroundMaterialComponent>(TEXT("GroundMaterial"));
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

