// Fill out your copyright notice in the Description page of Project Settings.


#include "CardGameUI.h"
#include "Components/TextBlock.h"

void UCardGameUI::SetEnemyScore(int newScore)
{
	
	FText score = FText::FromString(FString::FromInt(newScore));
	enemyScore->SetText(score);
	
}

void UCardGameUI::SetPlayerScore(int newScore)
{
	FText score = FText::FromString(FString::FromInt(newScore));
	GetScoreText()->SetText(score);
}

void UCardGameUI::SetCurrentPhase(FString newPhase)
{
	currentPhase->SetText(FText::FromString(newPhase));
}
