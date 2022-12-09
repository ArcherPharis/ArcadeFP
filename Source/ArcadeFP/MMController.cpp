// Fill out your copyright notice in the Description page of Project Settings.


#include "MMController.h"
#include "MainMenuUI.h"
#include "Kismet/GameplayStatics.h"

void AMMController::BeginPlay()
{

	Super::BeginPlay();
	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);

	if (inGameUIClass)
	{
		//TODO, the UI needs to know what game is currently being played. If it's the arcade, it loads
		//the arcade ui, if whack a mole, the whack a mole ui, etc.
		inGameUI = CreateWidget<UMainMenuUI>(this, inGameUIClass);
		inGameUI->AddToViewport();
	}

}
