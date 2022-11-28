// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCardPlayer.h"
#include "CardGamePlayer.generated.h"

UCLASS()
class ARCADEFP_API ACardGamePlayer : public ABaseCardPlayer
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACardGamePlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:


	UPROPERTY(EditDefaultsOnly, Category = "Card Player")
	class UCameraComponent* camera;

	UPROPERTY(EditDefaultsOnly, Category = "Card Player")
	float mouseSelectionDistance = 2000.f;

	void SelectItem();


};
