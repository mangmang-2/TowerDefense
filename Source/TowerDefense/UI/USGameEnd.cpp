// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/USGameEnd.h"
#include "Components/TextBlock.h"

void UUSGameEnd::SetText(bool bVictory)
{
	if(TextBlock_Title == nullptr)
		return;
	if(bVictory)
		TextBlock_Title->SetText(FText::FromString(TEXT("Victory")));
	else
		TextBlock_Title->SetText(FText::FromString(TEXT("Defeat")));
}
