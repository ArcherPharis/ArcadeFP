// Fill out your copyright notice in the Description page of Project Settings.


#include "CardGameMode.h"
#include "BaseCard.h"
#include "CardGamePlayer.h"
#include "EnemyCardPlayer.h"
#include "Kismet/GameplayStatics.h"

void ACardGameMode::SetPlayerSum(ABaseCard* card)
{
	totalPlayerSum += card->GetCardValue();
	UE_LOG(LogTemp, Warning, TEXT("%i"), totalPlayerSum)
}

void ACardGameMode::SetPlayer(ABaseCardPlayer* P)
{
	player = P;
}

void ACardGameMode::SetEnemy(ABaseCardPlayer* E)
{
	enemy = E;
}

