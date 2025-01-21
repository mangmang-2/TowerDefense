// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/USDamageIndicatorActor.h"
#include "Components/WidgetComponent.h"

// Sets default values
AUSDamageIndicatorActor::AUSDamageIndicatorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageWidgetComponent"));
}

// Called when the game starts or when spawned
void AUSDamageIndicatorActor::BeginPlay()
{
	Super::BeginPlay();
	
	float AnimationDuration = 1.5;

	FTimerHandle RemainTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(
		RemainTimerHandle,
		this,
		&ThisClass::DestroyAfterAnimation,
		AnimationDuration,
		false
	);
}

// Called every frame
void AUSDamageIndicatorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUSDamageIndicatorActor::DestroyAfterAnimation()
{
	Destroy();
}