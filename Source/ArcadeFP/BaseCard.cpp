// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCard.h"

// Sets default values
ABaseCard::ABaseCard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(root);
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	mesh->SetupAttachment(root);

}

// Called when the game starts or when spawned
void ABaseCard::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

