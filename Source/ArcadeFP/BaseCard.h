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

	UStaticMeshComponent* GetMesh() const { return mesh; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Card")
	USceneComponent* root;

	UPROPERTY(EditDefaultsOnly, Category = "Card")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Card")
	int cardValue;

};
