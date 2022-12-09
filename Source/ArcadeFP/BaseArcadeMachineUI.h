// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseArcadeMachineUI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API UBaseArcadeMachineUI : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetScoreText(int newScore);
	void SetResultsScreen(int finalScore, int tokensWon);

	

protected:
	class UTextBlock* GetScoreText() const { return scoreText; }

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* scoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* finalScoreText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* tokensWonText;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* inGameCanvas;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* resultsCanvas;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* canvasSwitcher;
	
};
