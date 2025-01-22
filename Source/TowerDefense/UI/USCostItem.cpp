// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/USCostItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../Utility/MessageSystem/MesssageStruct/USTowerMessage.h"
#include "NativeGameplayTags.h"
#include "../Utility/MessageSystem/GameplayMessageSubsystem.h"
#include "Components/Button.h"
#include "../Utility/DataTable/USStageSubsystem.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_TowerBuild_Message);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_SelectUI_Message);

void UUSCostItem::SetData(class UTexture2D* TextureIcon, int32 CostValue)
{
	if (Image_Icon)
		Image_Icon->SetBrushFromTexture(TextureIcon);

	if (TextBlock_Cost)
		TextBlock_Cost->SetText(FText::AsNumber(CostValue));
}

void UUSCostItem::SetData(FUSTowerUpgradeData UpgradeData)
{
	TowerUpgradeData = UpgradeData;
	SetData(UpgradeData.UIIcon, UpgradeData.UpgradeCost);

	UUSStageSubsystem* TowerUpgradeSubSystem = GetGameInstance()->GetSubsystem<UUSStageSubsystem>();
	if (Button_Slot && TowerUpgradeSubSystem)
	{
		if(TowerUpgradeSubSystem->GetRemainGold() < UpgradeData.UpgradeCost)
		{
			Button_Slot->SetIsEnabled(false);

			FLinearColor DisabledColor = FLinearColor::Gray;
			Button_Slot->WidgetStyle.Normal.TintColor = FSlateColor(DisabledColor);
			Button_Slot->WidgetStyle.Hovered.TintColor = FSlateColor(DisabledColor);
			Button_Slot->WidgetStyle.Pressed.TintColor = FSlateColor(DisabledColor);
		}
	}
}

void UUSCostItem::SetActor(AActor* SelectedActor)
{
	OwnerActor = SelectedActor;
}

void UUSCostItem::BPButtonClick()
{
	CreateTower();
	DestroyUI();
}

void UUSCostItem::CreateTower()
{
	FUSTowerBuildMessage Message;
	Message.Verb = TAG_TowerBuild_Message;
	Message.TowerID = TowerUpgradeData.TowerID;
	Message.OwnerActor = OwnerActor;

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSystem.BroadcastMessage(Message.Verb, Message);

	UUSStageSubsystem* TowerUpgradeSubSystem = GetGameInstance()->GetSubsystem<UUSStageSubsystem>();
	if (TowerUpgradeSubSystem)
	{
		TowerUpgradeSubSystem->ConsumeGold(TowerUpgradeData.UpgradeCost);
	}
}

void UUSCostItem::DestroyUI()
{
	FUSTowerSelectUIMessage Message;
	Message.Verb = TAG_SelectUI_Message;

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSystem.BroadcastMessage(Message.Verb, Message);
}
