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

void ACardGameMode::HandleTieSkirmish()
{
	totalEnemySum = 0;
	totalPlayerSum = 0;
	cardGameState = Skirmish;
	currentTurnPlayer = player;
	BroadcastBothScores();
}

void ACardGameMode::BroadcastBothScores()
{
	onEnemyScored.Broadcast(totalEnemySum);
	onPlayerScored.Broadcast(totalPlayerSum);
}

void ACardGameMode::EnemySkirmish()
{
	TSubclassOf<ABaseCard> cardClass = enemy->GetDeck()[0];
	ABaseCard* card;
	enemy->Skirmish(cardClass, card);
	totalEnemySum += card->GetCardValue();
	onEnemyScored.Broadcast(totalEnemySum);
	SkirmishRound(card->GetCardValue(), enemy);
	
}

void ACardGameMode::CheckSkirmishValues()
{
	if (totalPlayerSum < totalEnemySum)
	{
		currentTurnPlayer = player;
		cardGameState = Blitz;
		onPhaseChange.Broadcast("Blitz");
	}
	else if (totalPlayerSum > totalEnemySum)
	{
		cardGameState = Blitz;
		onPhaseChange.Broadcast("Blitz");
		BlitzRound(totalEnemySum, enemy);
	}

	if (totalPlayerSum == totalEnemySum)
	{
		
		
		player->ClearDeck();
		enemy->ClearDeck();
		//todo, after a tie, if enemy is lower, we need to set their turn. Probably that check.

		
	}
}

void ACardGameMode::FindLowestPossibleCard()
{
	TArray<ABaseCard*> possibleCards;

	if (enemy->GetHand().Num() == 0) return;
	
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

	if (lowestCard)
	{

		enemy->RemoveFromHand(lowestCard);
		totalEnemySum += lowestCard->GetCardValue();
		onEnemyScored.Broadcast(totalEnemySum);
		lowestCard->SetActorRotation(FRotator(180, lowestCard->GetActorRotation().Yaw, lowestCard->GetActorRotation().Roll));
		currentTurnPlayer = player;
	}

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

//todo, there needs to be some RoundStartCheck function, that is placed in front of everything in both
//skirmish and blitz. It's going to check if either player's hand is zero, based on who played the card
//will end the game based on the next player's move. Which will check final scores after the final
//move. For Skirmish, if the hand is ever zero in either hand, it will just check the sums and determine
//a winner. Also if the deck is ever zero at the start of skirmish, you can use your hand instead.
//you still having deck cards means nothing in blitz, but having hand cards in skirmish can save you.

void ACardGameMode::SkirmishRound(int scoreFromCurrentPlayer, ABaseCardPlayer* playerWhoWent)
{
	if (cardGameState == Skirmish)
	{

		if (playerWhoWent == player && currentTurnPlayer == player)
		{
			totalPlayerSum += scoreFromCurrentPlayer;
			onPlayerScored.Broadcast(totalPlayerSum);
			currentTurnPlayer = enemy;
			if (totalEnemySum == 0)
			{
				GetWorldTimerManager().SetTimer(enemyTurnDelayHandle, this, &ACardGameMode::EnemySkirmish, enemyTurnDelay, false);
		
			}
			else
			{
				CheckSkirmishValues();
			}
			
		}

		if (playerWhoWent == enemy)
		{
			CheckSkirmishValues();
		}
	}
}

void ACardGameMode::BlitzRound(int scoreFromCurrentPlayer, ABaseCardPlayer* playerWhoWent)
{
	if (cardGameState == Blitz)
	{
		if (playerWhoWent == player && currentTurnPlayer == player)
		{
			totalPlayerSum += scoreFromCurrentPlayer;
			onPlayerScored.Broadcast(totalPlayerSum);
			currentTurnPlayer = enemy;

			if (totalPlayerSum > totalEnemySum)
			{
				if (enemy->GetHand().Num() == 0)
				{
					UE_LOG(LogTemp, Warning, TEXT("Enemy loses here."));
					return;
				}



				GetWorldTimerManager().SetTimer(enemyTurnDelayHandle, this, &ACardGameMode::FindLowestPossibleCard, enemyTurnDelay, false);


			}
			else if(totalEnemySum < totalEnemySum)
			{
				UE_LOG(LogTemp, Warning, TEXT("You lose screen here."));
			}

			if (totalPlayerSum == totalEnemySum)
			{
				player->ClearDeck();
				enemy->ClearDeck();
				cardGameState = Skirmish;
				onPhaseChange.Broadcast("Skirmish");
				
			}
		}

		if (playerWhoWent == enemy && currentTurnPlayer == enemy)
		{
			GetWorldTimerManager().SetTimer(enemyTurnDelayHandle, this, &ACardGameMode::FindLowestPossibleCard, enemyTurnDelay, false);
		}
	}
}

