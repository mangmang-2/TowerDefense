// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/Component/USTowerRangeComponent.h"

// Sets default values for this component's properties
UUSTowerRangeComponent::UUSTowerRangeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	RangeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RangeMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Engine/BasicShapes/Plane.Plane"));
	if (MeshAsset.Succeeded())
	{
		RangeMesh->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MaterialAsset(TEXT("/Game/TowerDefance/Player/Data/MI_Cursor.MI_Cursor"));
	if (MaterialAsset.Succeeded())
	{
		RangeMesh->SetMaterial(0, MaterialAsset.Object);
	}
}


// Called when the game starts
void UUSTowerRangeComponent::BeginPlay()
{
	Super::BeginPlay();
	//RangeMesh->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
	RangeMesh->SetRelativeLocation(FVector(0.0, 0.0, -80.0));
}

void UUSTowerRangeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector TowerLocation = GetOwner()->GetActorLocation();
	TowerLocation.Z -= 90;
	RangeMesh->SetWorldLocation(TowerLocation);
}

void UUSTowerRangeComponent::SetRange(float Range)
{
	AttackRange = Range;

	float ScaleSize = AttackRange / 50.0f;
	RangeMesh->SetRelativeScale3D(FVector(ScaleSize, ScaleSize, ScaleSize));

	UMaterialInstance* MaterialAsset = LoadObject<UMaterialInstance>(nullptr, TEXT("/Game/TowerDefance/Player/Data/MI_Cursor.MI_Cursor"));
	UMaterialInstanceDynamic* DynamicMaterial = RangeMesh->CreateDynamicMaterialInstance(0, MaterialAsset);
	if (DynamicMaterial)
	{
		FLinearColor OutValue;
		DynamicMaterial->GetVectorParameterValue(FName("Shape"), OutValue);
		float UVScale = 0.05f / ScaleSize;
		OutValue.G = UVScale;
		DynamicMaterial->SetVectorParameterValue(FName("Shape"), OutValue);
	}
}

float UUSTowerRangeComponent::GetAttackRange()
{
	return AttackRange;
}

