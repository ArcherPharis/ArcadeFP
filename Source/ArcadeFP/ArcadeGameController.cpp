// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcadeGameController.h"
#include "Kismet/GameplayStatics.h"
#include "BaseCharacter.h"
#include "InGameUI.h"

AArcadeGameController::AArcadeGameController()
{


}

void AArcadeGameController::BeginPlay()
{
	Super::BeginPlay();
	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);
	if (inGameUIClass)
	{
		inGameUI = CreateWidget<UInGameUI>(this, inGameUIClass);
		inGameUI->AddToViewport();
	}
	player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player)
	{
		player->onInteract.AddDynamic(inGameUI, &UInGameUI::SwitchCanvas);
	}


}

