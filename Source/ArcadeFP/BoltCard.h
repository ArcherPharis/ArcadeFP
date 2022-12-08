// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCard.h"
#include "BoltCard.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API ABoltCard : public ABaseCard
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Bolt Card")
	void BoltEffect();

private:
	virtual void UseSpecialEffect() override;
	
};
