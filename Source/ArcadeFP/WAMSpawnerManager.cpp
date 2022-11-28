// Fill out your copyright notice in the Description page of Project Settings.


#include "WAMSpawnerManager.h"
#include "WAMTargetSpawner.h"
#include "Kismet/GameplayStatics.h"
#include "WhackAMoleController.h"

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
	
	switch (round)
	{
		case 1:SpawnLogic(1); break;
		case 2:SpawnLogicHard(3); break;
		case 3:EndGame(); break;
		case 4:SpawnLogicHard(7); break;
		case 5:SpawnLogicHard(7); break;
		case 6:SpawnLogic(3); break;
		case 7:SpawnLogic(4); break;
		case 8:SpawnLogic(4); break;
		case 9:SpawnLogic(2); break;
		case 10:SpawnLogic(3); break;
		case 11:SpawnLogic(2); break;
		case 12:SpawnLogic(1); break;
		case 13:SpawnLogic(5); break;
		case 14:SpawnLogic(4); break;
		case 15:SpawnLogic(6); break;
		case 16:SpawnLogic(5); break;
		case 17:SpawnLogic(8); break;
		case 18:SpawnLogic(9); break;
		//case 19: break; //todo spawn superenemy;
		//case 19: //EndGame(); break;
	}

	


	//for (AWAMTargetSpawner* spawner : spawners)
	//{
	//	spawner->SpawnTarget();
	//}
}

void AWAMSpawnerManager::SpawnLogic(int amountToSpawn)
{

	for (int i = 0; i < amountToSpawn; i++)
	{
		int randomNum = FMath::RandRange(0, 8);
		spawners[randomNum]->SpawnTarget();

	}
	round++;
}

void AWAMSpawnerManager::SpawnLogicNormal(int amountToSpawn)
{
	for (int i = 0; i < amountToSpawn; i++)
	{
		int randomNum = FMath::RandRange(0, 8);
		spawners[randomNum]->SpawnTargetNormal();

	}
	round++;
}

void AWAMSpawnerManager::SpawnLogicHard(int amountToSpawn)
{
	for (int i = 0; i < amountToSpawn; i++)
	{
		int randomNum = FMath::RandRange(0, 8);
		spawners[randomNum]->SpawnTargetHard();

	}
	round++;
}

void AWAMSpawnerManager::EndGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Endgame reached."));
	AWhackAMoleController* controller = Cast<AWhackAMoleController>(UGameplayStatics::GetPlayerController(this, 0));
	controller->FinalScore();
	UGameplayStatics::OpenLevel(GetWorld(), "Arcade");
}



