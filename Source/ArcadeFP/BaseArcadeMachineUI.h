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

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* scoreText;
	
};
