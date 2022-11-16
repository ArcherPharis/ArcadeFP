// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGameUI.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API UInGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* tokenCount;

	UPROPERTY(meta = (BindWidget))
	class UImage* coinImage;

	class UArcadeGameInstance* gameInstance;

	UFUNCTION()
	void UpdateTokenText(int newToken);


	
};
