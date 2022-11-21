// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseArcadeMachine.generated.h"


UCLASS()
class ARCADEFP_API ABaseArcadeMachine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseArcadeMachine();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void BeginGame(AActor* interactor);

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE int GetUIIndex() const { return indexUI; }

	void LoadLevel(FName levelName);

	FName GetLevelName() const { return nameOfLevel; }

private:

	UPROPERTY(EditDefaultsOnly, Category = "ArcadeMachineSetup")
	USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly, Category = "ArcadeMachineSetup")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly, Category = "ArcadeMachineSetup")
	class UInteractableComponent* interactableComponent;

	UPROPERTY(EditDefaultsOnly, Category = "ArcadeMachineSetup")
	int indexUI = 1;

	UPROPERTY(EditDefaultsOnly, Category = "ArcadeMachineSetup")
	FName nameOfLevel = "WhackAMole";

};
