// Fill out your copyright notice in the Description page of Project Settings.


#include "WhackAMoleArcadeMachine.h"

void AWhackAMoleArcadeMachine::BeginGame(AActor* interactor)
{
	Super::BeginGame(interactor);
	UE_LOG(LogTemp, Warning, TEXT("The things that interacted with the whack a mole was: %s"), *interactor->GetName());
	
}
