// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/Component/USAttackerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../Unit/USUnit.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "../../Skill/Tag/USGameplayTag.h"

// Sets default values for this component's properties
UUSAttackerComponent::UUSAttackerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickInterval = 5.0f;
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
	ActivateAbility(Target);
}

void UUSAttackerComponent::SetAbilitySystemComponent(UAbilitySystemComponent* AbilitySystemComponent)
{
	ASC = AbilitySystemComponent;
}

AActor* UUSAttackerComponent::FindClosestMonster()
{
	TArray<AActor*> FoundActors;
	TArray<AActor*> FilteredActors;

	// Ŭ������ �ش��ϴ� ��� ���� ��������
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUSUnit::StaticClass(), FoundActors);
	if(FoundActors.Num() == 0)
		return nullptr;

	// �ϴ� ó����.. ���߿� �ֿ켱������ �������� �켱���� �������
	return FoundActors[0];
}

void UUSAttackerComponent::ActivateAbility(AActor* Target)
{
	if (Target == nullptr)
		return;

	FGameplayEventData PayloadData;
	PayloadData.Target = Target;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), USTAG_TOWER_SKILL_ARROW, PayloadData);
}

