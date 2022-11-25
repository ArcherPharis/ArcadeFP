// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseArcadeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ArcadeGameInstance.h"

void ABaseArcadeGameMode::BeginPlay()
{
	Super::BeginPlay();
	instance = Cast<UArcadeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void ABaseArcadeGameMode::ConvertScoreToTokens(int finalScore)
{
	if (instance)
	{
		int tokens = finalScore / 10;

		instance->SetTokenCount(tokens);
		UE_LOG(LogTemp, Warning, TEXT("Tokens earned was: %i and total token amount is: %i"),tokens, instance->GetCurrentTokenCount());
	}
}
