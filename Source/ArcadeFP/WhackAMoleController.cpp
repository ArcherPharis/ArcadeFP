// Fill out your copyright notice in the Description page of Project Settings.


#include "WhackAMoleController.h"
#include "BaseArcadeMachineUI.h"
#include "Kismet/GameplayStatics.h"
#include "BaseArcadeGameMode.h"

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

void AWhackAMoleController::FinalScore()
{
	ABaseArcadeGameMode* gameMode = Cast<ABaseArcadeGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gameMode)
	{
		
		gameMode->ConvertScoreToTokens(currentGameScore);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("can't find gamemode"));
	}

}

