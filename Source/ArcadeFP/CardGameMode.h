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

	UPROPERTY(EditDefaultsOnly, Category = "CardGameMode")
	TEnumAsByte<CardGameState> cardGameState;

	void SetPlayer(class ABaseCardPlayer* P);
	void SetEnemy(class ABaseCardPlayer* E);



private:

	UPROPERTY(EditDefaultsOnly, Category = "Player Score")
	int totalPlayerSum = 0;

	UPROPERTY(EditDefaultsOnly, Category = "Player Score")
	int totalEnemySum = 0;

	UPROPERTY(EditAnywhere, Category = "CardGameMode")
	ABaseCardPlayer* player;

	UPROPERTY(EditAnywhere, Category = "CardGameMode")
	ABaseCardPlayer* enemy;
	
};
