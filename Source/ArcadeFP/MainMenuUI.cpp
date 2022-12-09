// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuUI::NativeConstruct()
{
	startGame->OnReleased.AddDynamic(this, &UMainMenuUI::StartGame);
	exitGame->OnReleased.AddDynamic(this, &UMainMenuUI::QuitGame);

}

void UMainMenuUI::StartGame()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Arcade");
}

void UMainMenuUI::QuitGame()
{
	UGameplayStatics::GetPlayerController(this, 0)->ConsoleCommand("quit");
}
