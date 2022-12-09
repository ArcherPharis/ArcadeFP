// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseArcadeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ArcadeGameInstance.h"

void ABaseArcadeGameMode::BeginPlay()
{
	Super::BeginPlay();
	instance = Cast<UArcadeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	APlayerController* playerController = UGameplayStatics::GetPlayerController(this, 0);
	playerController->SetInputMode(FInputModeGameAndUI());
	playerController->SetShowMouseCursor(false);
}

void ABaseArcadeGameMode::ConvertScoreToTokens(int finalScore, int& tokensObtained)
{
	if (instance)
	{
		int tokens = finalScore / 10;

		instance->SetTokenCount(tokens);
		tokensObtained = tokens;
		UE_LOG(LogTemp, Warning, TEXT("Tokens earned was: %i and total token amount is: %i"),tokens, instance->GetCurrentTokenCount());
	}
}
