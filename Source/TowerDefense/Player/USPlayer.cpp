// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/USPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "../UI/USTowerSelectUI.h"
#include "../Utility/DataTable/USTowerUpgradeSubSystem.h"
#include "../Tower/Interface/USTowerUpgradeInterface.h"
#include "../Utility/MessageSystem/MesssageStruct/USTowerMessage.h"
#include "NativeGameplayTags.h"
#include "../Utility/MessageSystem/GameplayMessageSubsystem.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_SelectUI_Message);

// Sets default values
AUSPlayer::AUSPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 1139.963867f;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bInheritRoll = true;
	SpringArm->SocketOffset = FVector(-300.0, 0, 80.0);
	SpringArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));
}

// Called when the game starts or when spawned
void AUSPlayer::BeginPlay()
{
	Super::BeginPlay();
	UpdateZoom();

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->bShowMouseCursor = true;

		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		InputMode.SetHideCursorDuringCapture(false); // 마우스 클릭 시 커서 숨김 방지

		PC->SetInputMode(InputMode);
	}
}

// Called every frame
void AUSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTracking();;
}

// Called to bind functionality to input
void AUSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		if (BaseInputMappingContext)
		{
			Subsystem->AddMappingContext(BaseInputMappingContext, 0);
		}
	}
}

void AUSPlayer::BlueprintZoomFunc(float ActionValue)
{
	ZoomDirection = ActionValue;
	UpdateZoom();
	Dof();
}

void AUSPlayer::BPClickFunc()
{
	FVector2D ViewportCenter = GetViewportCenter();

	FVector2D ScreenPos;
	FVector Intersection;
	bool bMousePostion;
	ProjectMouseToGroundPlane(ScreenPos, Intersection, bMousePostion);
	if (bMousePostion)
	{
		FindActorsAtIntersection(Intersection, 100.0f);
	}
}

void AUSPlayer::UpdateZoom()
{
	ZoomValue = FMath::Clamp((ZoomDirection * 0.01) + ZoomValue, 0, 1);

	float Alpha = ZoomCurve->GetFloatValue(ZoomValue);

	float TargetArmLength = UKismetMathLibrary::Lerp(5000.0f, 10000.0f, Alpha);
	SpringArm->TargetArmLength = TargetArmLength;

	float TargetRotation = UKismetMathLibrary::Lerp(-40.0f, -55.0f, Alpha);
	SpringArm->SetRelativeRotation(FRotator(TargetRotation, 0.0f, 0.0f));

	float MaxSpeed = UKismetMathLibrary::Lerp(1000.0f, 6000.0f, Alpha);
	FloatingPawnMovement->MaxSpeed = MaxSpeed;

	Dof();

	float FieldOfView = UKismetMathLibrary::Lerp(20.0f, 15.0f, Alpha);
	Camera->SetFieldOfView(FieldOfView);
}

void AUSPlayer::Dof()
{
	FPostProcessSettings PostProcessSettings;
	PostProcessSettings.bOverride_DepthOfFieldFstop = true;
	PostProcessSettings.DepthOfFieldFstop = 3.0f;

	PostProcessSettings.bOverride_DepthOfFieldSensorWidth = true;
	PostProcessSettings.DepthOfFieldSensorWidth = 150.0f;

	PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
	PostProcessSettings.DepthOfFieldFocalDistance = SpringArm->TargetArmLength;

	Camera->PostProcessSettings = PostProcessSettings;
}

void AUSPlayer::MoveTracking()
{
	FVector PlayerLocation = GetActorLocation();
	FVector NormalizedLocation = PlayerLocation.GetSafeNormal(0.0001f); // Tolerance를 0.0001로 설정
	float LocationLength = PlayerLocation.Size();
	float ScaleValue = FMath::Max(0, (LocationLength - 9000.0f) / 5000.0f);

	FVector WorldDirection = FVector(NormalizedLocation.X, NormalizedLocation.Y, 0) * -1.0f;
	// 이동 입력 추가
	AddMovementInput(WorldDirection, ScaleValue);

	EdgeMode();
}

void AUSPlayer::EdgeMode()
{
	FVector2D ViewportCenter = GetViewportCenter();

	FVector2D ScreenPos;
	FVector Intersection;
	bool bMousePostion;
	ProjectMouseToGroundPlane(ScreenPos, Intersection, bMousePostion);

	FVector Direction = CursorDistFromViewportCenter(ScreenPos - ViewportCenter);
	FTransform ActorTransform = GetActorTransform();
	FVector TransformDirection = UKismetMathLibrary::TransformDirection(ActorTransform, Direction);

	float Strength = 1.0f;
	AddMovementInput(TransformDirection, Strength);
}

FVector2D AUSPlayer::GetViewportCenter()
{
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (PlayerController == nullptr)
		return FVector2D::ZeroVector;

	int32 ViewportSizeX, ViewportSizeY;
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

	return FVector2D(ViewportSizeX / 2.0f, ViewportSizeY / 2.0f);
}

FVector2D AUSPlayer::GetMouseViewportPosition(bool& bMousePostion)
{
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (PlayerController == nullptr)
		return FVector2D::ZeroVector;

	float LocationX, LocationY;
	bMousePostion = PlayerController->GetMousePosition(LocationX, LocationY);

	return FVector2D(LocationX, LocationY);
}

FVector AUSPlayer::ProjectScreenPositionToGamePlane(FVector2D ScreenPosition)
{
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (PlayerController == nullptr)
		return FVector::ZeroVector;

	FVector WorldPosition, WorldDirection;
	PlayerController->DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldPosition, WorldDirection);

	FVector LineEnd = WorldPosition + (WorldDirection * 100000.0f);
	FPlane APlane(FVector(0.0f, 0.0f, 0.0f), FVector(0.0f, 0.0f, 1.0f));

	FVector Intersection;
	float T;
	UKismetMathLibrary::LinePlaneIntersection(WorldPosition, LineEnd, APlane, T, Intersection);

	return Intersection;
}

void AUSPlayer::ProjectMouseToGroundPlane(FVector2D& ScreenPosition, FVector& Intersection, bool& bMousePostion)
{
	ScreenPosition = GetMouseViewportPosition(bMousePostion);
	if (bMousePostion == false)
		ScreenPosition = GetViewportCenter();

	Intersection = ProjectScreenPositionToGamePlane(ScreenPosition);
}

FVector AUSPlayer::CursorDistFromViewportCenter(FVector2D ScreenPos)
{
	FVector2D Distance = CalculateEdgeMoveDistance();
	FVector2D OffsetMousePosition = OffsetMousePositionToCreateDeadZone(ScreenPos, Distance);
	FVector2D Adjusted = AdjustForNegativeDirection(ScreenPos);

	return FVector(Adjusted.Y * OffsetMousePosition.Y * -1.0f, Adjusted.X * OffsetMousePosition.X, 0.0f);
}

FVector2D AUSPlayer::CalculateEdgeMoveDistance()
{
	FVector2D ViewportCenter = GetViewportCenter();

	// 최종 Edge Move Distance 계산
	return FVector2D(ViewportCenter.X - EdgeMoveDistance, ViewportCenter.Y - EdgeMoveDistance);
}

FVector2D AUSPlayer::OffsetMousePositionToCreateDeadZone(FVector2D ScreenPos, FVector2D Distance)
{
	// 마우스 위치의 절대값 계산
	float AbsMouseX = FMath::Abs(ScreenPos.X);
	float AbsMouseY = FMath::Abs(ScreenPos.Y);

	// X축, Y축에서 Dead Zone을 감안한 위치 계산
	float OffsetX = FMath::Max(0.0f, AbsMouseX - Distance.X) / EdgeMoveDistance;
	float OffsetY = FMath::Max(0.0f, AbsMouseY - Distance.Y) / EdgeMoveDistance;

	return FVector2D(OffsetX, OffsetY);
}

FVector2D AUSPlayer::AdjustForNegativeDirection(FVector2D InputVector)
{
	float AdjustedX = FMath::Sign(InputVector.X);
	float AdjustedY = FMath::Sign(InputVector.Y);

	return FVector2D(AdjustedX, AdjustedY);
}

void AUSPlayer::FindActorsAtIntersection(FVector Intersection, float Radius)
{
	TArray<FHitResult> HitResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(Radius);

	bool bHit = GetWorld()->SweepMultiByChannel(
		HitResults,
		Intersection,
		Intersection,
		FQuat::Identity,
		ECC_GameTraceChannel1, // 충돌 채널
		Sphere
	);
	DrawDebugSphere(GetWorld(), Intersection, Radius, 12, FColor::Green, false, 1.0f, 0, 2.0f);

	if (bHit)
	{
		for (const FHitResult& Hit : HitResults)
		{
			if (AActor* HitActor = Hit.GetActor())
			{
				TowerSelectUI(HitActor);
				DrawDebugSphere(GetWorld(), HitActor->GetActorLocation(), Radius, 12, FColor::Red, false, 1.0f, 0, 2.0f);
			}
		}
	}
	else
	{
		FUSTowerSelectUIMessage Message;
		Message.Verb = TAG_SelectUI_Message;

		UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
		MessageSystem.BroadcastMessage(Message.Verb, Message);
	}
}

void AUSPlayer::TowerSelectUI(AActor* SelectedActor)
{
	IUSTowerUpgradeInterface *TowerUpgrade = Cast<IUSTowerUpgradeInterface>(SelectedActor);
	if(TowerUpgrade == nullptr)
		return;

	FVector WorldLocation = SelectedActor->GetActorLocation(); 
	FVector2D ScreenPosition;

	if (GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(WorldLocation, ScreenPosition) == false)
		return;

	UUSTowerSelectUI* TowerSelect = CreateWidget<UUSTowerSelectUI>(GetWorld(), TowerSelectClass, TEXT("TowerConfirm"));
	if (TowerSelect == nullptr)
		return;

	if (TowerSelect->IsInViewport())
		return;

	UUSTowerUpgradeSubSystem* TowerUpgradeSubSystem = GetGameInstance()->GetSubsystem<UUSTowerUpgradeSubSystem>();
	if(TowerUpgradeSubSystem == nullptr)
		return;

	TArray<FUSTowerUpgradeData> UpgradeData = TowerUpgradeSubSystem->GetUpgradeDataListByParentID(TowerUpgrade->GetTowerID());
	TowerSelect->SetActor(SelectedActor);
	TowerSelect->SetData(UpgradeData);
	
	TowerSelect->AddToViewport();
	TowerSelect->SetPositionInViewport(ScreenPosition);

}