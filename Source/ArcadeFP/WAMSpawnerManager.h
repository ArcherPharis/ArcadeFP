// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WAMSpawnerManager.generated.h"

UCLASS()
class ARCADEFP_API AWAMSpawnerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWAMSpawnerManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "SpawnerManager")
	void SpawnTargets();

private:
	UPROPERTY(EditAnywhere, Category = "Spawners")
	TArray<class AWAMTargetSpawner*> spawners;

};
