// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/Goal/USTowerLoadActor.h"
#include "../Component/GroundMaterialComponent.h"

// Sets default values
AUSTowerLoadActor::AUSTowerLoadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GroundMaterial = CreateDefaultSubobject<UGroundMaterialComponent>(TEXT("GroundMaterial"));
}

// Called when the game starts or when spawned
void AUSTowerLoadActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUSTowerLoadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

