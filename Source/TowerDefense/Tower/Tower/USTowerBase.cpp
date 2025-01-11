// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower/Tower/USTowerBase.h"
#include "AbilitySystemComponent.h"
#include "../Stat/USTowerStatAttributeSet.h"
#include "../../Utility/Component/USAttackerComponent.h"
#include "Components/CapsuleComponent.h"
#include "../../Utility/Component/USTowerRangeComponent.h"

// Sets default values
AUSTowerBase::AUSTowerBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<UUSTowerStatAttributeSet>(TEXT("AttributeSet"));

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetupAttachment(RootComponent);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CapsuleComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TowerMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	AttackerComponent = CreateDefaultSubobject<UUSAttackerComponent>(TEXT("AttackerComponent"));

	TowerRangeComponent = CreateDefaultSubobject<UUSTowerRangeComponent>(TEXT("TowerRangeComponent"));
}

AUSTowerBase::AUSTowerBase(ETowerType InTowerType) : AUSTowerBase()
{
	TowerType = InTowerType;
}

// Called when the game starts or when spawned
void AUSTowerBase::BeginPlay()
{
	Super::BeginPlay();
	
	for (const auto& Ability : Abilities)
	{
		FGameplayAbilitySpec Spec(Ability);
		ASC->GiveAbility(Spec);
	}

	AttackerComponent->SetAbilitySystemComponent(ASC);


	UDataTable* TowerTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/TowerDefance/DataTable/TowerData.TowerData"));
	if (TowerTable == nullptr)
	{
		return;
	}

	FName  DisplayName(*StaticEnum<ETowerType>()->GetDisplayNameTextByIndex(static_cast<int8>(TowerType)).ToString());

	FUSTowerData* TowerData = TowerTable->FindRow<FUSTowerData>(DisplayName, TEXT(""));
	if (TowerData == nullptr)
	{
		return;
	}
	if (TowerData->Mesh == nullptr)
		return;

	SkeletalMesh->SetSkeletalMesh(TowerData->Mesh);

	AttckAnim = TowerData->AttckAnim;
}

void AUSTowerBase::InitTower(FUSTowerUpgradeData UpgradeData)
{
	TowerRangeComponent->SetRange(UpgradeData.AttackRange);
	AttackerComponent->SetRange(UpgradeData.AttackRange);
}



