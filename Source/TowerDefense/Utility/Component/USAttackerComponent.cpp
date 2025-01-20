// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/Component/USAttackerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../Unit/USUnit.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "../../Skill/Tag/USGameplayTag.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"
#include "../../Utility/MessageSystem/MesssageStruct/SkillOptionalData.h"

// Sets default values for this component's properties
UUSAttackerComponent::UUSAttackerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickInterval = 10.0f;

}


// Called when the game starts
void UUSAttackerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUSAttackerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Target = FindClosestMonster();
	if(Target == nullptr)
		return;

	ActivateAbility(Target);
}

void UUSAttackerComponent::SetAbilitySystemComponent(UAbilitySystemComponent* AbilitySystemComponent)
{
	ASC = AbilitySystemComponent;

	StartGiveAbility = ASC->GetActivatableAbilities();
}

AActor* UUSAttackerComponent::FindClosestMonster()
{
	TArray<AActor*> FoundActors;

	// 클래스에 해당하는 모든 액터 가져오기
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AUSUnit::StaticClass(),TEXT("Monster"), FoundActors);
	if(FoundActors.Num() == 0)
		return nullptr;

	FVector OwnerActorLocation = GetOwner()->GetActorLocation();
	for (const auto& Actor : FoundActors)
	{
		FVector ActorLocation = Actor->GetActorLocation();
		if ((OwnerActorLocation - ActorLocation).Length() < AttackRange)
		{
			return Actor;
		}
	}

	return nullptr;
}

void UUSAttackerComponent::ActivateAbility(AActor* Target)
{
	if (Target == nullptr)
		return;

	FGameplayEventData PayloadData;
	PayloadData.Target = Target;

	USkillOptionalData* SkillData = NewObject<USkillOptionalData>();
	SkillData->SkillLocation = Target->GetActorLocation();
	PayloadData.OptionalObject = SkillData;

	for (const auto& AbilitySpec : StartGiveAbility)
	{
		for (int32 TagsIndex = 0 ; TagsIndex < AbilitySpec.Ability->AbilityTags.Num(); TagsIndex++)
		{
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), AbilitySpec.Ability->AbilityTags.GetByIndex(TagsIndex), PayloadData);
			OwnerRotation(Target);
		}
	}
}

void UUSAttackerComponent::OwnerRotation(AActor* Target)
{
	if (Target && GetOwner())
	{
		AActor* Owner = GetOwner();

		FVector OwnerLocation = Owner->GetActorLocation();
		FVector TargetLocation = Target->GetActorLocation();

		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwnerLocation, TargetLocation);

		Owner->SetActorRotation(LookAtRotation);
	}
}

void UUSAttackerComponent::SetRange(float Range)
{
	AttackRange = Range;
}

