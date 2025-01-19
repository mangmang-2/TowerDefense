// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/USIconTextUI.h"
#include "NativeGameplayTags.h"
#include "../Utility/MessageSystem/GameplayMessageSubsystem.h"
#include "Components/TextBlock.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Message_UI_HUDInfo, "Message.UI.HUDInfo");

void UUSIconTextUI::NativeConstruct()
{
	Super::NativeConstruct();

	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.RegisterListener(TAG_Message_UI_HUDInfo, this, &ThisClass::ResponseMessage);
}

void UUSIconTextUI::ResponseMessage(FGameplayTag Channel, const FUSTowerUIData& Payload)
{
	if(HUDType == Payload.HUDType)
		TextBlock_Resource->SetText(Payload.InfoText);
}
