// Fill out your copyright notice in the Description page of Project Settings.


#include "WAMTarget.h"

// Sets default values
AWAMTarget::AWAMTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(rootComp);

}

// Called when the game starts or when spawned
void AWAMTarget::BeginPlay()
{
	Super::BeginPlay();
	mesh->OnComponentHit.AddDynamic(this, &AWAMTarget::OnHit);
	
}

// Called every frame
void AWAMTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWAMTarget::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OW! This person hit me!: %s"), *OtherActor->GetName());
}

