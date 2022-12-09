// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WhackAMoleController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFinalScore, int, finalScore, int, tokens);
/**
 * 
 */
UCLASS()
class ARCADEFP_API AWhackAMoleController : public APlayerController
{
	GENERATED_BODY()

public:

	FOnFinalScore onFinalScore;

	void BeginPlay() override;
	UFUNCTION()
	void TargetHit(int pointsToGiveScore);
	void FinalScore();


private:
	class UBaseArcadeMachineUI* inGameUI;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UBaseArcadeMachineUI> inGameUIClass;

	int currentGameScore = 0;

	FTimerHandle handle;
	float time = 3;

	void GoBack();

	
};
