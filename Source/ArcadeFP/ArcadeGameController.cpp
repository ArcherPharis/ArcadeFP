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
	if (inGameUIClass)
	{
		//TODO, the UI needs to know what game is currently being played. If it's the arcade, it loads
		//the arcade ui, if whack a mole, the whack a mole ui, etc.
		inGameUI = CreateWidget<UInGameUI>(this, inGameUIClass);
		inGameUI->AddToViewport();
	}
	player = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player)
	{
		player->onInteract.AddDynamic(inGameUI, &UInGameUI::SwitchCanvas);
	}


}

