// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseArcadeMachine.h"
#include "InteractableComponent.h"

// Sets default values
ABaseArcadeMachine::ABaseArcadeMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("rootComponent"));
	SetRootComponent(rootComp);
	interactableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));

}

// Called when the game starts or when spawned
void ABaseArcadeMachine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseArcadeMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

