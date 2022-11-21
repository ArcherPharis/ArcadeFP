// Fill out your copyright notice in the Description page of Project Settings.


#include "WAMTargetSpawner.h"
#include "WAMTarget.h"

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
		GetWorld()->SpawnActor<AWAMTarget>(normalEvilTarget, GetActorLocation(), GetActorRotation());
		bIsOccupied = true;
	}
}

