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

	void LoadLevel(FName levelName);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "ArcadeMachineSetup")
	USceneComponent* rootComp;

	UPROPERTY(EditDefaultsOnly, Category = "ArcadeMachineSetup")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly, Category = "ArcadeMachineSetup")
	class UInteractableComponent* interactableComponent;

};
