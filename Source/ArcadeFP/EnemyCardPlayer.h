// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCardPlayer.h"
#include "EnemyCardPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API AEnemyCardPlayer : public ABaseCardPlayer
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	void EnemyBlitz();

private:
	virtual void DealCards() override;


	
};
