
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

	UFUNCTION(BlueprintPure, Category = "WhackAMole Character")
	UBoxComponent* GetHammerHitBox() const { return hammerHitBox; }


private:
	void MoveForward(float Value);


	void MoveRight(float Value);

	void Attack();

	bool CanAttack();

	FTimerHandle firingHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "FireRate")
	float fireRate = 1;

	UPROPERTY(EditDefaultsOnly, Category = "WhackAMole Setup")
	UAnimMontage* attackingMontage;

	UPROPERTY(EditDefaultsOnly, Category = "WhackAMole Setup")
	class UBoxComponent* hammerHitBox;


	
};
