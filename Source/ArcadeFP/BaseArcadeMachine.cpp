// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseArcadeMachine.h"
#include "InteractableComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseArcadeMachine::ABaseArcadeMachine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("rootComponent"));
	SetRootComponent(rootComp);
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(GetRootComponent());
	interactableComponent = CreateDefaultSubobject<UInteractableComponent>(TEXT("InteractableComponent"));

}

// Called when the game starts or when spawned
void ABaseArcadeMachine::BeginPlay()
{
	Super::BeginPlay();
	interactableComponent->onInteracted.AddDynamic(this, &ABaseArcadeMachine::BeginGame);
	
}

void ABaseArcadeMachine::BeginGame(AActor* interactor)
{
	UE_LOG(LogTemp, Warning, TEXT("From the base class's Begin Game"));
}

void ABaseArcadeMachine::LoadLevel(FName levelName)
{
	UGameplayStatics::OpenLevel(GetWorld(), levelName);
	
}

// Called every frame
void ABaseArcadeMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

