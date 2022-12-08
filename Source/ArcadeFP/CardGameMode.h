// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseArcadeGameMode.h"
#include "CardGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyScored, int, newScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerScored, int, newScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseChange, FString, newPhase);


UENUM()
enum CardGameState
{
	Skirmish UMETA(DisplayName = "Skirmish"),
	Blitz UMETA(DisplayName = "Blitz")
};

/**
 * 
 */
UCLASS()
class ARCADEFP_API ACardGameMode : public ABaseArcadeGameMode
{
	GENERATED_BODY()

public:
	ACardGameMode();

	void SetPlayerSum(class ABaseCard* card);

	int GetEitherPlayerSum();

	void DoubleSum(class ABaseCardPlayer* playerWhoFlared);

	void ResurrectCard(ABaseCardPlayer* playerWhoResurrected, ABaseCard* card);
	void Flip(ABaseCardPlayer* playerWhoFlipped);

	void SetOldPlayerAmount();

	void GameOver();
	void PlayerWon();

	void PreCheck();

	

	FOnEnemyScored onEnemyScored;
	FOnPlayerScored onPlayerScored;
	FOnPhaseChange onPhaseChange;

	UPROPERTY(EditAnywhere, Category = "CardGameMode")
	TEnumAsByte<CardGameState> cardGameState;

	void SetPlayer(ABaseCardPlayer* P);
	void SetEnemy(class AEnemyCardPlayer* E);

	void BoltSum(ABaseCardPlayer* playerWhoBolted);

	bool isPlayerInTurn(const ABaseCardPlayer* currentPlayerToCheck) const;

	void SkirmishRound(int scoreFromCurrentPlayer, ABaseCardPlayer* playerWhoWent);
	void BlitzRound(int scoreFromCurrentPlayer, ABaseCardPlayer* playerWhoWent);

	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "CardGameGameMode")
	void HandleTieSkirmish();

	



private:

	

	UPROPERTY(EditDefaultsOnly, Category = "Player Score")
	int totalPlayerSum = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Player Score")
	int totalEnemySum = 0;

	int oldPlayerSum;
	int oldEnemySum;


	UPROPERTY(EditAnywhere, Category = "CardGameMode")
	ABaseCardPlayer* player;

	UPROPERTY(EditAnywhere, Category = "CardGameMode")
	class AEnemyCardPlayer* enemy;

	UPROPERTY(EditAnywhere, Category = "CardGameMode")
	ABaseCardPlayer* currentTurnPlayer;
	
	FTimerHandle enemyTurnDelayHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "EnemyParameters")
	float enemyTurnDelay = 1.5f;

	void EnemySkirmish();

	void CheckSkirmishValues();

	void FindLowestPossibleCard();
	void BroadcastBothScores();

	
	
};
