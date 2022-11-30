// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCardPlayer.h"
#include "BaseCard.h"

void AEnemyCardPlayer::BeginPlay()
{
	Super::BeginPlay();
	DealCards();
	SetGamePlayer(this, false);
	ShuffleDeck();
}

void AEnemyCardPlayer::DealCards()
{
	Super::DealCards();
	
	for (ABaseCard* card : GetHand())
	{
		card->SetActorRotation(FRotator(180, 0, 0));
	}
}

void AEnemyCardPlayer::EnemyBlitz()
{

	TSubclassOf<ABaseCard> cardClass = GetDeck()[0];
	ABaseCard* card = GetWorld()->SpawnActor<ABaseCard>(cardClass);
}
