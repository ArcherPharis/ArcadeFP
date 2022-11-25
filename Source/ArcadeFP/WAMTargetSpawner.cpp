// Fill out your copyright notice in the Description page of Project Settings.


#include "WAMTargetSpawner.h"
#include "WAMTarget.h"
#include "WhackAMoleController.H"
#include "Kismet/GameplayStatics.h"
// Sets default values
AWAMTargetSpawner::AWAMTargetSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWAMTargetSpawner::BeginPlay()
{
	Super::BeginPlay();
	Controller = Cast<AWhackAMoleController>(UGameplayStatics::GetPlayerController(this, 0));
	//this doesn't work, the actual target has to do it themselves, then tell its target spawner that it's no longer occupied.
	
}

// Called every frame
void AWAMTargetSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWAMTargetSpawner::SpawnTarget()
{
	if (!bIsOccupied)
	{
		SpawnEnemy(targetClasses[0]);
	}
}

void AWAMTargetSpawner::SpawnTargetNormal()
{
	if (!bIsOccupied)
	{
		int randomNum = FMath::RandRange(1, 10);

		if (randomNum <= 6)
		{
			SpawnEnemy(targetClasses[0]);
		}
		else
		{
			SpawnEnemy(targetClasses[1]);
		}


	}
}

void AWAMTargetSpawner::SpawnTargetHard()
{
	int randomNum = FMath::RandRange(1, 10);

	if (randomNum <= 5)
	{
		SpawnEnemy(targetClasses[0]);
	}
	else if(randomNum > 5 && randomNum <= 8)
	{
		SpawnEnemy(targetClasses[1]);
	}
	else if (randomNum > 8)
	{
		
		SpawnEnemy(targetClasses[2]);
	}
}

void AWAMTargetSpawner::SpawnSuperEnemy()
{
	SpawnEnemy(superEvilTarget);
}

void AWAMTargetSpawner::SetOccupancy(bool isOccupied)
{
	bIsOccupied = isOccupied;
}

void AWAMTargetSpawner::SpawnEnemy(TSubclassOf<AWAMTarget> targetClass)
{
	auto newTarget = GetWorld()->SpawnActor<AWAMTarget>(targetClass, GetActorLocation(), GetActorRotation());
	newTarget->SetOwner(this);
	bIsOccupied = true;
	if (Controller)
	{
		newTarget->onHitTarget.AddDynamic(Controller, &AWhackAMoleController::TargetHit);
	}
}

