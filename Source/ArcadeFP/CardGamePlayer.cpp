// Fill out your copyright notice in the Description page of Project Settings.


#include "CardGamePlayer.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CardGameMode.h"
#include "BaseCard.h"

// Sets default values
ACardGamePlayer::ACardGamePlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	camera->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ACardGamePlayer::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* controller = UGameplayStatics::GetPlayerController(this, 0);
	controller->bShowMouseCursor = true;
	DealCards();
	SetGamePlayer(this, true);
	
}

// Called every frame
void ACardGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACardGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("CardClick", IE_Pressed, this, &ACardGamePlayer::SelectItem);

}


void ACardGamePlayer::SelectItem()
{
	FHitResult hit;
	FVector start;
	FVector  dir;
	UGameplayStatics::GetPlayerController(this, 0)->DeprojectMousePositionToWorld(start, dir);
	FVector end = dir * mouseSelectionDistance;
	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECC_Visibility))
	{
		ABaseCard* card = Cast<ABaseCard>(hit.GetActor());
		if (card && card->GetOwner() == this)
		{
			GetCardGameMode()->SetPlayerSum(card);
			RemoveFromHand(card);
		}
	}
}

