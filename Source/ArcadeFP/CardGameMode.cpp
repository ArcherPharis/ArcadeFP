// Fill out your copyright notice in the Description page of Project Settings.


#include "CardGameMode.h"
#include "BaseCard.h"
#include "CardGamePlayer.h"
#include "EnemyCardPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "CardController.h"

ACardGameMode::ACardGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACardGameMode::BeginPlay()
{
	Super::BeginPlay();
	controller = Cast<ACardController>(UGameplayStatics::GetPlayerController(this, 0));
	
	
}

void ACardGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//UE_LOG(LogTemp, Warning, TEXT("%i"), oldPlayerSum);
	
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
	oldEnemySum = totalEnemySum;
	totalEnemySum += card->GetCardValue();
	onEnemyScored.Broadcast(totalEnemySum);
	SkirmishRound(card->GetCardValue(), enemy);
	
}

void ACardGameMode::CheckSkirmishValues()
{
	if (totalPlayerSum < totalEnemySum)
	{
		if (player->GetHand().Num() == 0)
		{
			GameOver();
			return;
		}


		currentTurnPlayer = player;
		cardGameState = Blitz;
		onPhaseChange.Broadcast("Blitz");
	}
	else if (totalPlayerSum > totalEnemySum)
	{
		if (enemy->GetHand().Num() == 0)
		{
			PlayerWon();
			return;
		}

		cardGameState = Blitz;
		onPhaseChange.Broadcast("Blitz");
		BlitzRound(totalEnemySum, enemy);
	}

	if (totalPlayerSum == totalEnemySum)
	{	
		player->ClearDeck();
		enemy->ClearDeck();
	}
}

void ACardGameMode::FindLowestPossibleCard()
{

	if (enemy->GetCurrentCard() && enemy->GetCurrentCard()->isBolted)
	{
		ABaseCard* resCard = nullptr;
		for (ABaseCard* sCard : enemy->GetHand())
		{
			if (sCard->GetCardValue() == 1 && resCard == nullptr)
			{
				resCard = sCard;
			}
			if (resCard)
			{
				resCard->UseSpecialEffect();
				enemy->RemoveFromHand(resCard);
				oldEnemySum = totalEnemySum;
				totalEnemySum += resCard->GetCardValue() + enemy->GetCurrentCard()->GetCardValue();
				onEnemyScored.Broadcast(totalEnemySum);
				resCard->SetActorRotation(FRotator(180, resCard->GetActorRotation().Yaw, resCard->GetActorRotation().Roll));
				currentTurnPlayer = player;
				return;
			}
		}
	}


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
	
	if (possibleCards.Num() > 0)
	{
		ABaseCard* lowestCard = possibleCards[0];
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
		if (lowestCard)
		{

			enemy->RemoveFromHand(lowestCard);
			oldEnemySum = totalEnemySum;
			totalEnemySum += lowestCard->GetCardValue();
			onEnemyScored.Broadcast(totalEnemySum);
			lowestCard->SetActorRotation(FRotator(180, lowestCard->GetActorRotation().Yaw, lowestCard->GetActorRotation().Roll));
			currentTurnPlayer = player;
		}
	}
	else
	{
		ABaseCard* specialCard = nullptr;

		for (ABaseCard* sCard : enemy->GetHand())
		{
			if (sCard->GetCardValue() == 0 && specialCard == nullptr)
			{
				specialCard = sCard;
			}
		}

		if (specialCard)
		{
			specialCard->UseSpecialEffect();
			enemy->RemoveFromHand(specialCard);
			oldEnemySum = totalEnemySum;
			totalEnemySum += specialCard->GetCardValue();
			onEnemyScored.Broadcast(totalEnemySum);
			specialCard->SetActorRotation(FRotator(180, specialCard->GetActorRotation().Yaw, specialCard->GetActorRotation().Roll));
			currentTurnPlayer = player;
		}
		else
		{
			PlayerWon();
		}
	}

}






void ACardGameMode::SetPlayerSum(ABaseCard* card)
{
	totalPlayerSum += card->GetCardValue();
	UE_LOG(LogTemp, Warning, TEXT("%i"), totalPlayerSum)
}

int ACardGameMode::GetEitherPlayerSum()
{
	if (currentTurnPlayer == player)
	{
		return totalPlayerSum;
	}
	else if (currentTurnPlayer == enemy)
	{
		return totalEnemySum;
	}


	return 0;
}

void ACardGameMode::DoubleSum(ABaseCardPlayer* playerWhoFlared)
{
	if (playerWhoFlared == player)
	{
		oldPlayerSum = totalPlayerSum;
		totalPlayerSum *= 2;
		onPlayerScored.Broadcast(totalPlayerSum);
	}
	if (playerWhoFlared == enemy)
	{
		oldEnemySum = totalEnemySum;
		totalEnemySum *= 2;
		onEnemyScored.Broadcast(totalEnemySum);
	}
}

void ACardGameMode::ResurrectCard(ABaseCardPlayer* playerWhoResurrected, ABaseCard* card)
{
	//cant test yet, enemy has to be to use other cards first, specifically bolt to know when 
	//to change its current card. let's do ressurect last.

	if (playerWhoResurrected == player)
	{
		if (player->GetCurrentCard()->isBolted)
		{
			player->GetCurrentCard()->SetActorRotation((FRotator(180, player->GetCurrentCard()->GetActorRotation().Yaw, player ->GetCurrentCard()->GetActorRotation().Roll)));
			player->GetCurrentCard()->isBolted = false;
			totalPlayerSum += oldPlayerSum;
			oldPlayerSum = totalPlayerSum - player->GetCurrentCard()->GetCardValue();
			onPlayerScored.Broadcast(totalPlayerSum);
		}
		else
		{
			player->RemoveFromHand(card);
			oldPlayerSum = totalPlayerSum;
			totalPlayerSum += card->GetCardValue() - 1;
			onPlayerScored.Broadcast(totalPlayerSum);
		}
	}


	if (playerWhoResurrected == enemy)
	{
		if (enemy->GetCurrentCard()->isBolted)
		{
			enemy->GetCurrentCard()->SetActorRotation((FRotator(-180, enemy->GetCurrentCard()->GetActorRotation().Yaw, enemy->GetCurrentCard()->GetActorRotation().Roll)));
			enemy->GetCurrentCard()->isBolted = false;
			totalEnemySum += oldEnemySum;
			oldEnemySum = totalEnemySum - enemy->GetCurrentCard()->GetCardValue();
			onEnemyScored.Broadcast(totalEnemySum);
		}
		else
		{
			enemy->RemoveFromHand(card);
			oldEnemySum = totalEnemySum;
			totalEnemySum += card->GetCardValue() - 1;
			onEnemyScored.Broadcast(totalEnemySum);
		}
	}

}

void ACardGameMode::Flip(ABaseCardPlayer* playerWhoFlipped)
{
	if (playerWhoFlipped == player)
	{
		int v = totalPlayerSum;
		int y = oldPlayerSum;
		totalPlayerSum = totalEnemySum;
		totalEnemySum = v;
		oldPlayerSum = oldEnemySum;
		oldEnemySum = y;
		onEnemyScored.Broadcast(totalEnemySum);
	}

	if (playerWhoFlipped == enemy)
	{
		int v = totalEnemySum;
		int y = oldPlayerSum;
		totalEnemySum = totalPlayerSum;
		totalPlayerSum = v;
		oldPlayerSum = oldEnemySum;
		oldEnemySum = y;
		onEnemyScored.Broadcast(totalEnemySum);
		onPlayerScored.Broadcast(totalPlayerSum);

	}
}

void ACardGameMode::GameOver()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Lost"));
	int tokens;
	ConvertScoreToTokens(0, tokens);
	controller->SetResults(0, tokens);
}

void ACardGameMode::PlayerWon()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Won"));
	int tokens;
	ConvertScoreToTokens(300, tokens);
	controller->SetResults(300, tokens);

}

void ACardGameMode::PreCheck()
{
	if (enemy->GetHand().Num() == 0 && totalEnemySum < totalPlayerSum)
	{
		PlayerWon();
		return;
	}

	if (player->GetHand().Num() == 0 && totalPlayerSum < totalEnemySum)
	{
		GameOver();
		return;
	}

	if (totalEnemySum == totalPlayerSum)
	{
		cardGameState == Skirmish;
		currentTurnPlayer = player;
	}

}

void ACardGameMode::SetOldPlayerAmount()
{
	oldPlayerSum = totalPlayerSum;
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

void ACardGameMode::BoltSum(ABaseCardPlayer* playerWhoBolted)
{
	if (playerWhoBolted == player)
	{
		enemy->GetCurrentCard()->SetActorRotation((FRotator(-180, enemy->GetCurrentCard()->GetActorRotation().Yaw, enemy->GetCurrentCard()->GetActorRotation().Roll)));
		enemy->GetCurrentCard()->isBolted = true;
		
		totalEnemySum = oldEnemySum;
		onEnemyScored.Broadcast(totalEnemySum);
		PreCheck();
	}
	if (playerWhoBolted == enemy)
	{
		player->GetCurrentCard()->SetActorRotation((FRotator(-180, player->GetCurrentCard()->GetActorRotation().Yaw, player->GetCurrentCard()->GetActorRotation().Roll)));
		player->GetCurrentCard()->isBolted = true;
		totalPlayerSum = oldPlayerSum;
		onPlayerScored.Broadcast(totalPlayerSum);
		PreCheck();
	}
}

bool ACardGameMode::isPlayerInTurn(const ABaseCardPlayer* currentPlayerToCheck) const
{
	return currentPlayerToCheck == currentTurnPlayer;
}


void ACardGameMode::SkirmishRound(int scoreFromCurrentPlayer, ABaseCardPlayer* playerWhoWent)
{
	PreCheck();
	if (cardGameState == Skirmish)
	{

		if (playerWhoWent == player && currentTurnPlayer == player)
		{
			oldPlayerSum = totalPlayerSum;
			if (scoreFromCurrentPlayer == 0)
			{
				totalPlayerSum += 1;
			}
			
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

			if (scoreFromCurrentPlayer == 0)
			{
				totalEnemySum += 1;
			}
			onEnemyScored.Broadcast(totalEnemySum);
			CheckSkirmishValues();
		}
	}
}

void ACardGameMode::BlitzRound(int scoreFromCurrentPlayer, ABaseCardPlayer* playerWhoWent)
{
	PreCheck();

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
					PlayerWon();
					return;
				}



				GetWorldTimerManager().SetTimer(enemyTurnDelayHandle, this, &ACardGameMode::FindLowestPossibleCard, enemyTurnDelay, false);


			}
			else if (totalPlayerSum < totalEnemySum)
			{
				GameOver();
				return;
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

