// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseCardPlayer.generated.h"

UCLASS()
class ARCADEFP_API ABaseCardPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseCardPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OrganizeCards();

	void RemoveFromHand(class ABaseCard* cardToRemove);

	virtual void DealCards();

	void SetGamePlayer(ABaseCardPlayer* player, bool isHuman);

	TArray<ABaseCard*> GetHand() { return hand; }

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	class ACardGameMode* GetCardGameMode() const { return gameMode; }

	UFUNCTION(BlueprintImplementableEvent, Category = "BaseCardPlayer")
	void MoveCard(ABaseCard* cardToMove);

private:
	UPROPERTY(EditAnywhere, Category = "BaseCardPlayer")
	TArray<TSubclassOf<ABaseCard>> deck;

	UPROPERTY(EditAnywhere, Category = "BaseCardPlayer")
	TArray<ABaseCard*> hand;

	UPROPERTY(EditDefaultsOnly, Category = "Card Player")
	USceneComponent* rootComp;


	UPROPERTY(EditDefaultsOnly, Category = "Card Player")
	USceneComponent* cardSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Card Player")
	UStaticMeshComponent* deckMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Card Player")
	float cardSpacing = 10.f;

	ACardGameMode* gameMode;

	
	

};