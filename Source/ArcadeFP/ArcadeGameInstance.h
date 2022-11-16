

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArcadeGameInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTokenUpdated, int, newToken);

/**
 * 
 */
UCLASS()
class ARCADEFP_API UArcadeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	FORCEINLINE int GetCurrentTokenCount() const { return Tokens; }

	FOnTokenUpdated onTokenUpdated;

private:
	int Tokens = 10;
	
};
