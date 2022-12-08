// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCard.h"
#include "FlipCard.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API AFlipCard : public ABaseCard
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Flip")
	void FlipEffect();

private:
	virtual void UseSpecialEffect() override;
	
};
