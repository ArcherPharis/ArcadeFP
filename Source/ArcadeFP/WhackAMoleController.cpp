// Fill out your copyright notice in the Description page of Project Settings.


#include "WhackAMoleController.h"
#include "BaseArcadeMachineUI.h"

void AWhackAMoleController::BeginPlay()
{
	Super::BeginPlay();

	if (inGameUIClass)
	{
		inGameUI = CreateWidget<UBaseArcadeMachineUI>(this, inGameUIClass);
		inGameUI->AddToViewport();
	}
}

void AWhackAMoleController::TargetHit(int pointsToGiveScore)
{
	currentGameScore += pointsToGiveScore;
	inGameUI->SetScoreText(currentGameScore);
}
