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

	UFUNCTION()
	void SwitchCanvas(class ABaseArcadeMachine* arcadeMachine);

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* tokenCount;

	UPROPERTY(meta = (BindWidget))
	class UImage* coinImage;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* inGameCanvas;

	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* whackAMoleMenuCanvas;

	UPROPERTY(meta = (BindWidget))
	class UButton* startGameEasy;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* UISwitcher;

	class UArcadeGameInstance* gameInstance;

	class ABaseCharacter* playerCharacter;

	class ABaseArcadeMachine* currentArcadeMachine;

	UFUNCTION()
	void UpdateTokenText(int newToken);

	UFUNCTION()
	void StartWAMGame();



	
};
