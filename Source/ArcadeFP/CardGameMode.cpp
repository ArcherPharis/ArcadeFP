// Fill out your copyright notice in the Description page of Project Settings.


#include "CardGameMode.h"
#include "BaseCard.h"
#include "CardGamePlayer.h"
#include "EnemyCardPlayer.h"
#include "Kismet/GameplayStatics.h"

void ACardGameMode::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACardGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACardGameMode::EnemySkirmish()
{
	TSubclassOf<ABaseCard> cardClass = enemy->GetDeck()[0];
	ABaseCard* card;
	enemy->Skirmish(cardClass, card);
	totalEnemySum += card->GetCardValue();
	SkirmishRound(card->GetCardValue(), enemy);
	
}

void ACardGameMode::CheckSkirmishValues()
{
	if (totalPlayerSum < totalEnemySum)
	{
		currentTurnPlayer = player;
		cardGameState = Blitz;
	}
	else
	{
		currentTurnPlayer = enemy;
		cardGameState = Blitz;
	}

	if (totalPlayerSum == totalEnemySum)
	{
		currentTurnPlayer = player;
	}
}

void ACardGameMode::FindLowestPossibleCard()
{
	TArray<ABaseCard*> possibleCards;
	
	for (int i = 0; i < enemy->GetHand().Num(); i++)
	{
		int sumFromPossibleCard = enemy->GetHand()[i]->GetCardValue() + totalEnemySum;
		if (sumFromPossibleCard > totalPlayerSum)
		{
			possibleCards.Add(enemy->GetHand()[i]);
		}
	}
	ABaseCard* lowestCard = possibleCards[0];
	if (possibleCards.Num() > 0)
	{
		int highestPossibleScore = 7;

		for (int i = 0; i < possibleCards.Num(); i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (possibleCards[i]->GetCardValue() < highestPossibleScore)
				{
					if (lowestCard != nullptr && lowestCard->GetCardValue() <= possibleCards[i]->GetCardValue())
						break;
					UE_LOG(LogTemp, Warning, TEXT("Checking for lowest card"));
					lowestCard = possibleCards[i];

				}
				highestPossibleScore--;
			}

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No possible cards to play. I'll try to play my highest."));
	}

	enemy->RemoveFromHand(lowestCard);
	lowestCard->SetActorRotation(FRotator(180, lowestCard->GetActorRotation().Yaw, lowestCard->GetActorRotation().Roll));

	// It would store these in an array. By the way, special cards will always get stored.
//called possible choices, then it will go through this array, and sort them from lowest to
//greatest, it will then pick the first index to play. If its array size is 0 after it tries
//to find a card that would put it above your value, it will forfeit the game. Later on,
//before ALL of this, we will check if the there is a special card in the deck, and if there is
//roll a dice to decide whether or not to play it. In the case where it cannot find a greater card
//but it does have a special card, it will play the special card.

//also, if it does not have a card that will beat our sum, still have it find the largest possible
//card it can have and play that one, to at least try to tie.
}




void ACardGameMode::SetPlayerSum(ABaseCard* card)
{
	totalPlayerSum += card->GetCardValue();
	UE_LOG(LogTemp, Warning, TEXT("%i"), totalPlayerSum)
}

void ACardGameMode::SetPlayer(ABaseCardPlayer* P)
{
	player = P;
	currentTurnPlayer = player;
}

void ACardGameMode::SetEnemy(AEnemyCardPlayer* E)
{
	enemy = E;
}

bool ACardGameMode::isPlayerInTurn(const ABaseCardPlayer* currentPlayerToCheck) const
{
	return currentPlayerToCheck == currentTurnPlayer;
}

void ACardGameMode::SkirmishRound(int scoreFromCurrentPlayer, ABaseCardPlayer* playerWhoWent)
{
	if (cardGameState == Skirmish)
	{

		if (playerWhoWent == player && currentTurnPlayer == player)
		{
			UE_LOG(LogTemp, Warning, TEXT("Player Went"));
			totalPlayerSum += scoreFromCurrentPlayer;
			currentTurnPlayer = enemy;
			//so now we check if the enemy even has a score. If they do, we have to
			//determine if its higher than the player, lower, or tied.
			if (totalEnemySum == 0)
			{
				//enemy goes always in this case. but then we run the same check, to
				//see if lower, higher, or tied.
				GetWorldTimerManager().SetTimer(enemyTurnDelayHandle, this, &ACardGameMode::EnemySkirmish, enemyTurnDelay, false);
		
			}
			
		}

		if (playerWhoWent == enemy)
		{
			UE_LOG(LogTemp, Warning, TEXT("We got here"));
			CheckSkirmishValues();
		}
		//TSubclassOf<ABaseCard> cardClass = enemy->GetDeck()[0];
		//enemy->Blitz(cardClass);
	}
}

void ACardGameMode::BlitzRound(int scoreFromCurrentPlayer, ABaseCardPlayer* playerWhoWent)
{
	if (cardGameState == Blitz)
	{
		if (playerWhoWent == player && currentTurnPlayer == player)
		{
			totalPlayerSum += scoreFromCurrentPlayer;
			currentTurnPlayer = enemy;

			if (totalPlayerSum > totalEnemySum)
			{
				GetWorldTimerManager().SetTimer(enemyTurnDelayHandle, this, &ACardGameMode::FindLowestPossibleCard, enemyTurnDelay, false);

			}
		}
	}
}

