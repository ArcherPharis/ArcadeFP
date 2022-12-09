// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MMController.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API AMMController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

private:
	class UMainMenuUI* inGameUI;

	class ACharacter* player;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UMainMenuUI> inGameUIClass;
	
};
