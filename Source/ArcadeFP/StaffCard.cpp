// Fill out your copyright notice in the Description page of Project Settings.


#include "StaffCard.h"
#include "Kismet/GameplayStatics.h"
#include "CardGameMode.h"
#include "BaseCardPlayer.h"

void AStaffCard::UseSpecialEffect()
{
	Super::UseSpecialEffect();
	ACardGameMode* gm = Cast<ACardGameMode>(UGameplayStatics::GetGameMode(this));
	ABaseCardPlayer* user = Cast<ABaseCardPlayer>(GetOwner());
	gm->ResurrectCard(user, this);
}
