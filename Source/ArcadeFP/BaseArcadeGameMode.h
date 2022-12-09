// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BaseArcadeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API ABaseArcadeGameMode : public AGameModeBase
{
	GENERATED_BODY()



public:

	void BeginPlay() override;

	void ConvertScoreToTokens(int finalScore, int& tokensObtained);

private:

	class UArcadeGameInstance* instance;
	
};
