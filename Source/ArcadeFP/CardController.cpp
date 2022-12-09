// Fill out your copyright notice in the Description page of Project Settings.


#include "CardController.h"
#include "BaseArcadeMachineUI.h"
#include "Kismet/GameplayStatics.h"
#include "CardGameMode.h"
#include "CardGameUI.h"

void ACardController::BeginPlay()
{
	Super::BeginPlay();

	gameMode = Cast<ACardGameMode>(UGameplayStatics::GetGameMode(this));

	

	if (inGameUIClass)
	{
		inGameUI = CreateWidget<UCardGameUI>(this, inGameUIClass);
		inGameUI->AddToViewport();
		gameMode->onEnemyScored.AddDynamic(inGameUI, &UCardGameUI::SetEnemyScore);
		gameMode->onPlayerScored.AddDynamic(inGameUI, &UCardGameUI::SetPlayerScore);
		gameMode->onPhaseChange.AddDynamic(inGameUI, &UCardGameUI::SetCurrentPhase);

		
	}
	
}

void ACardController::SetResults(int score, int tokens)
{
	inGameUI->SetResultsScreen(score,tokens);
	GetWorldTimerManager().SetTimer(handle, this, &ACardController::GoBack, time, false);
}

void ACardController::GoBack()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Arcade");
}


