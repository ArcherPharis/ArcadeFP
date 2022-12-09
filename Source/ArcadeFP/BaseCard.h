// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCard.generated.h"

UCLASS()
class ARCADEFP_API ABaseCard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCard();

	int GetCardValue() const { return cardValue; }

	UFUNCTION(BlueprintCallable, Category = "Card")
	UStaticMeshComponent* GetMesh() const { return mesh; }
	UPROPERTY(EditDefaultsOnly, Category = "Card")
	bool stackableCard = true;
	UPROPERTY(EditDefaultsOnly, Category = "Card")
	bool isBolted = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void UseSpecialEffect();

	

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Card")
	USceneComponent* root;

	UPROPERTY(EditDefaultsOnly, Category = "Card")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Card")
	UParticleSystem* specialEffectFX;

	UPROPERTY(EditDefaultsOnly, Category = "Card")
	int cardValue;
	UPROPERTY(EditDefaultsOnly, Category = "Card")
	USoundBase* playedSound;

};
