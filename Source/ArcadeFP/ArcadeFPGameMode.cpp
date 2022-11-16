// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArcadeFPGameMode.h"
#include "ArcadeFPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArcadeFPGameMode::AArcadeFPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprint/Characters/Player/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
