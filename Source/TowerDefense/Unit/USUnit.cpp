// Fill out your copyright notice in the Description page of Project Settings.


#include "Unit/USUnit.h"
#include "AbilitySystemComponent.h"
#include "../Tower/Stat/USTowerStatAttributeSet.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NiagaraComponent.h"


// Sets default values
AUSUnit::AUSUnit()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	AttributeSet = CreateDefaultSubobject<UUSTowerStatAttributeSet>(TEXT("AttributeSet"));

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = CapsuleComponent;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UnitMesh"));
	SkeletalMesh->SetupAttachment(RootComponent);
	//SkeletalMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
	FloatingPawnMovement->MaxSpeed = 300.0f;

	NiagaraEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
	NiagaraEffect->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AUSUnit::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(RecordPathTimerHandle, this, &AUSUnit::RecordPath, RecordInterval, true);

	TargetWaypoint = GetActorLocation();

	if (UUSTowerStatAttributeSet* Stat = const_cast<UUSTowerStatAttributeSet*>(ASC->GetSet<UUSTowerStatAttributeSet>()))
	{
		Stat->OnHealthChange.AddDynamic(this, &ThisClass::OnHealthChange);
	}
}

void AUSUnit::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	RunBehaviorTree();
}

void AUSUnit::Destroyed()
{
	StopAction();
	Super::Destroyed();
}

// Called every frame
void AUSUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateWaypoint();
}

// Called to bind functionality to input
void AUSUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AUSUnit::RunBehaviorTree()
{
	if(BehaviorTree == nullptr)
		return;

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController == nullptr)
		return;

	if (AIController->RunBehaviorTree(BehaviorTree) == false)
		return;
}

void AUSUnit::IdleBehaviorTree()
{
	if (IdleBehavior == nullptr)
		return;

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController == nullptr)
		return;

	if (AIController->RunBehaviorTree(IdleBehavior) == false)
		return;	
}

void AUSUnit::RecordPath()
{
	if (PathHistory.Num() >= MaxPathPoints)
	{
		PathHistory.RemoveAt(0);
	}

	PathHistory.Add(GetActorLocation());

	for (int32 i = 0; i < PathHistory.Num() - 1; ++i)
	{
		//DrawDebugLine(GetWorld(), PathHistory[i], PathHistory[i + 1], FColor::Green, false, 2.0f, 0, 2.0f);
	}
}

FVector AUSUnit::GetRecordPostion(float Distance)
{
	if(PathHistory.Num() == 0)
		return GetActorLocation();

	FVector CurrentLocation = GetActorLocation();
	FVector FoundPosition = CurrentLocation; // 기본값은 현재 위치
	float AccumulatedDistance = 0.0f;

	for (int32 i = PathHistory.Num() - 1; i > 0; --i)
	{
		float SegmentDistance = FVector::Dist(PathHistory[i], PathHistory[i - 1]);
		AccumulatedDistance += SegmentDistance;

		if (AccumulatedDistance >= Distance)
		{
			FoundPosition = PathHistory[i - 1];
			break;
		}
	}
	if(FoundPosition == CurrentLocation)
		return GetActorLocation();

	int32 FoundIndex = PathHistory.Find(FoundPosition);
	if (FoundIndex != INDEX_NONE)
	{
		PathHistory.RemoveAt(FoundIndex, PathHistory.Num() - FoundIndex);
	}

	return FoundPosition;
}

void AUSUnit::SetWaypoint(FVector InWaypoint)
{
	StopAction();
	RunBehaviorTree();
	TargetWaypoint = InWaypoint;
	TargetWaypoint.Z = 0;
	IsReady = false;

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
		if (Blackboard)
		{
			Blackboard->SetValueAsVector(TEXT("WayPoint"), TargetWaypoint);
			Blackboard->SetValueAsBool(TEXT("Ready"), IsReady);
		}
	}
}

void AUSUnit::UpdateWaypoint()
{
	if (IsReady == false)
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation.Z = 0;
		FVector Direction = (TargetWaypoint - CurrentLocation).GetSafeNormal();

		FRotator CurrentRotation = GetActorRotation();
		FRotator TargetRotation = Direction.Rotation();
		SetActorRotation(FRotator(CurrentRotation.Pitch, TargetRotation.Yaw, CurrentRotation.Roll));

		FloatingPawnMovement->AddInputVector(Direction);

		if (FVector::Dist(CurrentLocation, TargetWaypoint) < 10.0f)
		{
			IsReady = true;
			AAIController* AIController = Cast<AAIController>(GetController());
			if (AIController)
			{
				UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
				if (Blackboard)
				{
					Blackboard->SetValueAsBool(TEXT("Ready"), IsReady);
				}
			}
			FloatingPawnMovement->StopActiveMovement(); // 이동 중지
		}
	}
}

void AUSUnit::SetNiagara(TObjectPtr<class UNiagaraSystem> NiagaraSystem)
{
	if (NiagaraSystem)
	{
		NiagaraEffect->SetAsset(NiagaraSystem);
		NiagaraEffect->Activate();
	}
	else
	{
		NiagaraEffect->Deactivate();
	}
}

void AUSUnit::SetMatchingActor(AUSUnit* TargetActor)
{
	IdleBehaviorTree();
	CombatState(true);
	TargetActor->CombatState(true);

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
		if (Blackboard)
		{
			Blackboard->SetValueAsObject(TEXT("Target"), TargetActor);
		}
	}

	RunBehaviorTree();
}

void AUSUnit::CombatState(bool bState)
{
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
		if (Blackboard)
		{
			Blackboard->SetValueAsBool(TEXT("Combat"), bState);
		}
	}
}

void AUSUnit::GiveAbility(TArray<TSubclassOf<class UGameplayAbility>> Abilities)
{
	for (const auto& Ability : Abilities)
	{
		FGameplayAbilitySpec Spec(Ability);
		ASC->GiveAbility(Spec);
	}
}

void AUSUnit::StopAction()
{
	IdleBehaviorTree();
	CombatState(false);
	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
		if (Blackboard)
		{
			// 순서 잘지켜야..
			AUSUnit* TargetObject = Cast<AUSUnit>(Blackboard->GetValueAsObject(TEXT("Target")));
			Blackboard->SetValueAsObject(TEXT("Target"), nullptr);	
			if (TargetObject)
			{
				TargetObject->StopAction();
				TargetObject->RunBehaviorTree();
			}
		}
	}
}

void AUSUnit::OnHealthChange()
{
	if (ASC->GetSet<UUSTowerStatAttributeSet>()->GetHealth() <= 0)
	{
		OnUnitDeath.Broadcast(this);
		Destroy();
	}
}

void AUSUnit::SetHealth(float Health)
{
	if(ASC == nullptr)
		return;
	UUSTowerStatAttributeSet* Stat = const_cast<UUSTowerStatAttributeSet*>(ASC->GetSet<UUSTowerStatAttributeSet>());

	if(Stat == nullptr)
		return;

	Stat->SetHealth(Health);
	Stat->SetMaxHealth(Health);
}


