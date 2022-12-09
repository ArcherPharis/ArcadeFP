// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcadeGameInstance.h"

void UArcadeGameInstance::SetTokenCount(int amount)
{
	Tokens = FMath::Clamp(Tokens += amount, 0, 999999);
	UE_LOG(LogTemp, Warning, TEXT("%i"), Tokens);
	
}
