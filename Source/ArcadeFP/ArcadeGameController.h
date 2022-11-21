// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArcadeGameController.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API AArcadeGameController : public APlayerController
{
	GENERATED_BODY()

public:
	AArcadeGameController();


	class UInGameUI* GetUI() const { return inGameUI; }

	void BeginPlay() override;


private:
	UInGameUI* inGameUI;

	class ABaseCharacter* player;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UInGameUI> inGameUIClass;
	
};
