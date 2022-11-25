// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WhackAMoleController.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API AWhackAMoleController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	UFUNCTION()
	void TargetHit(int pointsToGiveScore);
	void FinalScore();


private:
	class UBaseArcadeMachineUI* inGameUI;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UBaseArcadeMachineUI> inGameUIClass;

	int currentGameScore = 0;

	
};
