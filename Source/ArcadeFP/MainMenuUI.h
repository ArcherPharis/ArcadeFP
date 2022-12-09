// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API UMainMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* startGame;

	UPROPERTY(meta = (BindWidget))
	class UButton* exitGame;

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();
	
};
