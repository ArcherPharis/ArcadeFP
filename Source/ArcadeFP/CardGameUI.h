// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseArcadeMachineUI.h"
#include "CardGameUI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API UCardGameUI : public UBaseArcadeMachineUI
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void SetEnemyScore(int newScore);

	UFUNCTION()
	void SetPlayerScore(int newScore);

	UFUNCTION()
	void SetCurrentPhase(FString newPhase);



private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* currentPhase;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* enemyScore;
	
};
