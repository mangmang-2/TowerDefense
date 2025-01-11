// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/USTowerSelectUI.h"
#include "USCostItem.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "NativeGameplayTags.h"
#include "../Utility/MessageSystem/GameplayMessageSubsystem.h"
#include "../Utility/MessageSystem/MesssageStruct/USTowerMessage.h"
#include "../Tower/Tower/USUnitTower.h"
#include "Components/Button.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_SelectUI_Message, "Message.UI.SelectUI");
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_UnitWaypointMode_Message);

void UUSTowerSelectUI::NativeConstruct()
{
	Super::NativeConstruct();

	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSubsystem.RegisterListener(TAG_SelectUI_Message, this, &ThisClass::ResponseMessage);
}

void UUSTowerSelectUI::SetData(TArray<FUSTowerUpgradeData> DataList)
{
	switch (DataList.Num())
	{
	case 1:
		Insert(DataList[0], FVector2D(80,20));
		break;
	case 2:
		Insert(DataList[0], FVector2D(20, 20));
		Insert(DataList[1], FVector2D(140, 20));
		break;
	case 4:
		Insert(DataList[0], FVector2D(20, 20));
		Insert(DataList[1], FVector2D(140, 20));
		Insert(DataList[2], FVector2D(20, 140));
		Insert(DataList[3], FVector2D(140, 140));
		break;
	default:
		break;
	}	
}

void UUSTowerSelectUI::Insert(FUSTowerUpgradeData UpgradeData, FVector2D Pos)
{
	UUSCostItem* CostItem = CreateWidget<UUSCostItem>(GetWorld(), CostItemClass);
	if (CostItem == nullptr)
		return;
	if (CanvasPanel_Item == nullptr)
		return;

	UCanvasPanelSlot* CanvasSlot = CanvasPanel_Item->AddChildToCanvas(CostItem);
	if (CanvasSlot == nullptr)
		return;

	CostItem->SetData(UpgradeData);
	CostItem->SetActor(OwnerActor);
	CanvasSlot->SetPosition(Pos);
}

void UUSTowerSelectUI::SetActor(AActor* SelectedActor)
{
	OwnerActor = SelectedActor;

	Button_WayPoint->SetVisibility(ESlateVisibility::Hidden);
	if (SelectedActor && SelectedActor->IsA<AUSUnitTower>())
	{
		Button_WayPoint->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUSTowerSelectUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if(OwnerActor == nullptr)
		return;

	FVector WorldLocation = OwnerActor->GetActorLocation();
	FVector2D ScreenPosition;

	if (GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(WorldLocation, ScreenPosition) == false)
		return;

	SetPositionInViewport(ScreenPosition);
}

void UUSTowerSelectUI::ResponseMessage(FGameplayTag Channel, const FUSTowerSelectUIMessage& Payload)
{
	RemoveFromParent();
}

void UUSTowerSelectUI::BPClickWaypoint()
{
	FUSTowerWaypointUIMessage Message;
	Message.Verb = TAG_UnitWaypointMode_Message;
	Message.AddressAsString = FString::Printf(TEXT("%p"), OwnerActor);
	
	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSystem.BroadcastMessage(Message.Verb, Message);

	RemoveFromParent();
}
