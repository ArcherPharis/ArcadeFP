// Fill out your copyright notice in the Description page of Project Settings.


#include "WAMSpawnerManager.h"
#include "WAMTargetSpawner.h"

// Sets default values
AWAMSpawnerManager::AWAMSpawnerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWAMSpawnerManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWAMSpawnerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWAMSpawnerManager::SpawnTargets()
{
	//to make it less random, we could keep a "Round" variable, and switch based on the round, giving
	//the amount amount of spawns per round per game. Something to consider.

	int randomNum = FMath::RandRange(1, 9);

	for (int i = 0; i < randomNum; i++)
	{
		spawners[i]->SpawnTarget();
	}

	//for (AWAMTargetSpawner* spawner : spawners)
	//{
	//	spawner->SpawnTarget();
	//}
}

