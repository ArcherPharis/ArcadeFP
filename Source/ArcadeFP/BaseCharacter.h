// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArcadeFPCharacter.h"
#include "BaseCharacter.generated.h"

class ABaseArcadeMachine;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerInteract, ABaseArcadeMachine*, machine);


UCLASS()
class ARCADEFP_API ABaseCharacter : public AArcadeFPCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	FOnPlayerInteract onInteract;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InitCurrentInteractable();

	UFUNCTION(BlueprintImplementableEvent, Category = "Interactor")
	void InteractEffect();

private:
	UPROPERTY(EditDefaultsOnly, Category = "PlayerSetup")
	class UInteracter* interacter;

	class AArcadeGameController* controller;

	void Interact();

};
