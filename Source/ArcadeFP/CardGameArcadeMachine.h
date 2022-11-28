// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseArcadeMachine.h"
#include "CardGameArcadeMachine.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API ACardGameArcadeMachine : public ABaseArcadeMachine
{
	GENERATED_BODY()

private:
	virtual void BeginGame(AActor* interactor) override;
	
};
