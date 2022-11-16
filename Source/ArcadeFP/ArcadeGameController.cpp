// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcadeGameController.h"
#include "InGameUI.h"

AArcadeGameController::AArcadeGameController()
{


}

void AArcadeGameController::BeginPlay()
{
	Super::BeginPlay();
	if (inGameUIClass)
	{
		inGameUI = CreateWidget<UInGameUI>(this, inGameUIClass);
		inGameUI->AddToViewport();
	}


}
