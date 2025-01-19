// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/USGameLayerUI.h"
#include "USIconTextUI.h"
#include "../Utility/DataTable/USTowerUIData.h"

void UUSGameLayerUI::NativeConstruct()
{
	Super::NativeConstruct();
	WBP_HealthPoint->HUDType	= EHUDType::HealthPoint;
	WBP_Gold->HUDType			= EHUDType::Gold;
	WBP_WaveInfo->HUDType		= EHUDType::WaveInfo;
	WBP_RemainTime->HUDType		= EHUDType::RemainTime;
}
