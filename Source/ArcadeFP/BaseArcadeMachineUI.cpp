// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseArcadeMachineUI.h"
#include "Components/TextBlock.h"

void UBaseArcadeMachineUI::SetScoreText(int newScore)
{

	scoreText->SetText(FText::FromString(FString::FromInt(newScore)));

}
