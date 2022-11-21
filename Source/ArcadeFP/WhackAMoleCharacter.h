
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WhackAMoleCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ARCADEFP_API AWhackAMoleCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AWhackAMoleCharacter();

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);


	void MoveRight(float Value);

	void Attack();

	UPROPERTY(EditDefaultsOnly, Category = "WhackAMole Setup")
	UAnimMontage* attackingMontage;
	
};
