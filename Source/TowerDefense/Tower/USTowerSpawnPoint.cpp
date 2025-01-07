// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/USTowerSpawnPoint.h"
#include "NativeGameplayTags.h"
#include "../Utility/MessageSystem/GameplayMessageSubsystem.h"
#include "../Utility/MessageSystem/MesssageStruct/USTowerMessage.h"
#include "../Utility/DataTable/USTowerUpgradeSubSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Tower/USTowerBase.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_TowerBuild_Message, "Message.Tower.Build");

// Sets default values
AUSTowerSpawnPoint::AUSTowerSpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void AUSTowerSpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSubsystem.RegisterListener(TAG_TowerBuild_Message, this, &ThisClass::ResponseMessage);
}

// Called every frame
void AUSTowerSpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AUSTowerSpawnPoint::ResponseMessage(FGameplayTag Channel, const FUSTowerBuildMessage& Payload)
{
	if(Payload.OwnerActor != this)
		return;

	UUSTowerUpgradeSubSystem* TowerUpgradeSubSystem = GetGameInstance()->GetSubsystem<UUSTowerUpgradeSubSystem>();
	if (TowerUpgradeSubSystem == nullptr)
		return;

	FUSTowerUpgradeData UpgradeData = TowerUpgradeSubSystem->GetUpgradeData(Payload.TowerID);
	if(UpgradeData.TowerID == -1)
		return;

	FVector ActorLocation = GetActorLocation();
	ActorLocation.Z = 94;
	AUSTowerBase* TowerActor = Cast<AUSTowerBase>(UAIBlueprintHelperLibrary::SpawnAIFromClass(
		GetWorld(),
		UpgradeData.TowerBaseClass,
		nullptr,
		ActorLocation,
		FRotator::ZeroRotator,
		true
	));
	TowerActor->SetTowerID(Payload.TowerID);

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

