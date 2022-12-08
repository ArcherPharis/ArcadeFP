// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "ArcadeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "BaseArcadeMachine.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "BaseCharacter.h"

void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();
	gameInstance = Cast<UArcadeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	playerCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	gameInstance->onTokenUpdated.AddDynamic(this, &UInGameUI::UpdateTokenText);
	startGameEasy->OnReleased.AddDynamic(this, &UInGameUI::StartWAMGame);
	startCardGameButton->OnReleased.AddDynamic(this, &UInGameUI::StartWAMGame);
	UpdateTokenText(gameInstance->GetCurrentTokenCount());
}

void UInGameUI::UpdateTokenText(int newToken)
{

	FText text = FText::FromString(FString::FromInt(newToken));
	tokenCount->SetText(text);

}

void UInGameUI::StartWAMGame()
{
	if (playerCharacter)
	{
		playerCharacter->InitCurrentInteractable();
	}
}

void UInGameUI::SwitchCanvas(ABaseArcadeMachine* arcadeMachine)
{
	currentArcadeMachine = arcadeMachine;
	UISwitcher->SetActiveWidgetIndex(currentArcadeMachine->GetUIIndex());
}
