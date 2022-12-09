// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseArcadeMachineUI.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"

void UBaseArcadeMachineUI::SetScoreText(int newScore)
{

	scoreText->SetText(FText::FromString(FString::FromInt(newScore)));

}

void UBaseArcadeMachineUI::SetResultsScreen(int finalScore, int tokensWon)
{
	canvasSwitcher->SetActiveWidgetIndex(1);
	finalScoreText->SetText(FText::FromString(FString::FromInt(finalScore)));
	tokensWonText->SetText(FText::FromString(FString::FromInt(tokensWon)));
}
