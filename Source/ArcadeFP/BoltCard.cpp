// Fill out your copyright notice in the Description page of Project Settings.


#include "BoltCard.h"
#include "Kismet/GameplayStatics.h"
#include "CardGameMode.h"
#include "BaseCardPlayer.h"

void ABoltCard::UseSpecialEffect()
{
	Super::UseSpecialEffect();
	ACardGameMode* gm = Cast<ACardGameMode>(UGameplayStatics::GetGameMode(this));
	ABaseCardPlayer* user = Cast<ABaseCardPlayer>(GetOwner());
	gm->BoltSum(user);
	BoltEffect();
}
