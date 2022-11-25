// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WAMTargetSpawner.generated.h"

UCLASS()
class ARCADEFP_API AWAMTargetSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWAMTargetSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnTarget();
	void SpawnTargetNormal();
	void SpawnTargetHard();
	void SpawnSuperEnemy();



	UFUNCTION(BlueprintCallable, Category = "WAM Target Spawner")
	void SetOccupancy(bool isOccupied);



private:

	bool bIsOccupied = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "WAM Target Spawner")
	TArray<TSubclassOf<class AWAMTarget>> targetClasses;

	UPROPERTY(EditDefaultsOnly, Category = "WAM Target Spawner")
	TSubclassOf<AWAMTarget> superEvilTarget;

	void SpawnEnemy(TSubclassOf<AWAMTarget> targetClass);



	class AWhackAMoleController* Controller;
};
