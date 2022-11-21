// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseArcadeMachineUI.h"
#include "WhackAMoleUI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API UWhackAMoleUI : public UBaseArcadeMachineUI
{
	GENERATED_BODY()

public:

	


private:

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* comboCount;
	
};
