// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CardController.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API ACardController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	void SetResults(int score, int tokens);



private:
	class UCardGameUI* inGameUI;

	

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UCardGameUI> inGameUIClass;

	int currentGameScore = 0;
	

	class ACardGameMode* gameMode;

	FTimerHandle handle;
	float time = 3;

	void GoBack();

};
