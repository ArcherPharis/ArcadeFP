// Fill out your copyright notice in the Description page of Project Settings.


#include "FlipCard.h"
#include "Kismet/GameplayStatics.h"
#include "CardGameMode.h"
#include "BaseCardPlayer.h"

void AFlipCard::UseSpecialEffect()
{
	Super::UseSpecialEffect();
	ACardGameMode* gm = Cast<ACardGameMode>(UGameplayStatics::GetGameMode(this));
	ABaseCardPlayer* user = Cast<ABaseCardPlayer>(GetOwner());
	gm->Flip(user);
	FlipEffect();
}
