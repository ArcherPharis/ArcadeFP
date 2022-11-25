// Fill out your copyright notice in the Description page of Project Settings.


#include "WAMTarget.h"
#include "WAMTargetSpawner.h"

// Sets default values
AWAMTarget::AWAMTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(rootComp);
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(rootComp);
	mesh->SetCollisionResponseToChannels(ECR_Ignore);
	mesh->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECR_Overlap);

}

// Called when the game starts or when spawned
void AWAMTarget::BeginPlay()
{
	Super::BeginPlay();
	mesh->OnComponentBeginOverlap.AddDynamic(this, &AWAMTarget::OnOverlap);
	GetWorldTimerManager().SetTimer(despawnHandle, this, &AWAMTarget::Despawn, despawnTimer, false);
}

// Called every frame
void AWAMTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWAMTarget::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	onHitTarget.Broadcast(pointValue);
	AWAMTargetSpawner* spawner = Cast<AWAMTargetSpawner>(GetOwner());
	if (spawner)
	{
		spawner->SetOccupancy(false);
	}
	//todo, send event to play animation/timeline and then destroy.
	Destroy();
}

