// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseArcadeGameMode.h"
#include "CardGameMode.generated.h"

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
	void SetPlayerSum(class ABaseCard* card);

	

	UPROPERTY(EditAnywhere, Category = "CardGameMode")
	TEnumAsByte<CardGameState> cardGameState;

	void SetPlayer(class ABaseCardPlayer* P);
	void SetEnemy(class AEnemyCardPlayer* E);

	bool isPlayerInTurn(const ABaseCardPlayer* currentPlayerToCheck) const;

	void SkirmishRound(int scoreFromCurrentPlayer, ABaseCardPlayer* playerWhoWent);
	void BlitzRound(int scoreFromCurrentPlayer, ABaseCardPlayer* playerWhoWent);

	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;



private:



	UPROPERTY(EditDefaultsOnly, Category = "Player Score")
	int totalPlayerSum = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Player Score")
	int totalEnemySum = 0;

	UPROPERTY(EditAnywhere, Category = "CardGameMode")
	ABaseCardPlayer* player;

	UPROPERTY(EditAnywhere, Category = "CardGameMode")
	class AEnemyCardPlayer* enemy;

	ABaseCardPlayer* currentTurnPlayer;
	
	FTimerHandle enemyTurnDelayHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "EnemyParameters")
	float enemyTurnDelay = 1.5f;

	void EnemySkirmish();

	void CheckSkirmishValues();

	void FindLowestPossibleCard();
	
};
