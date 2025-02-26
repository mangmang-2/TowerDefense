// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/Goal/USMonsterGoal.h"
#include "Components/BoxComponent.h"
#include "../DataTable/USStageSubsystem.h"
#include "NativeGameplayTags.h"
#include "../MessageSystem/GameplayMessageSubsystem.h"
#include "../MessageSystem/MesssageStruct/USTowerMessage.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Message_Game_Info)

// Sets default values
AUSMonsterGoal::AUSMonsterGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	RootComponent = BoxComponent;

	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AUSMonsterGoal::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AUSMonsterGoal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUSMonsterGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUSMonsterGoal::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && OtherActor->Tags.Contains(TEXT("Monster")))
	{
		OtherActor->Destroy();
	}

	FUSGameData Message;
	Message.Verb = TAG_Message_Game_Info;
	Message.GameInfo = EGameInfo::Health;

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSystem.BroadcastMessage(Message.Verb, Message);
}

