// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/USCostItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../Utility/MessageSystem/MesssageStruct/USTowerMessage.h"
#include "NativeGameplayTags.h"
#include "../Utility/MessageSystem/GameplayMessageSubsystem.h"

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
}

void UUSCostItem::DestroyUI()
{
	FUSTowerSelectUIMessage Message;
	Message.Verb = TAG_SelectUI_Message;

	UGameplayMessageSubsystem& MessageSystem = UGameplayMessageSubsystem::Get(GetWorld());
	MessageSystem.BroadcastMessage(Message.Verb, Message);
}