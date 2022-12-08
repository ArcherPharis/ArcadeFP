// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCard.h"
#include "BlazeCard.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API ABlazeCard : public ABaseCard
{
	GENERATED_BODY()

private:
	virtual void UseSpecialEffect() override;
	
};
