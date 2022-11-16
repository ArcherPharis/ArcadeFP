// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameUI.h"
#include "ArcadeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UInGameUI::NativeConstruct()
{
	Super::NativeConstruct();
	gameInstance = Cast<UArcadeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	gameInstance->onTokenUpdated.AddDynamic(this, &UInGameUI::UpdateTokenText);
	UpdateTokenText(gameInstance->GetCurrentTokenCount());
}

void UInGameUI::UpdateTokenText(int newToken)
{

	FText text = FText::FromString(FString::FromInt(newToken));
	tokenCount->SetText(text);

}
