// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCardPlayer.h"
#include "BaseCard.h"
#include "CardGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABaseCardPlayer::ABaseCardPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	SetRootComponent(rootComp);
	cardSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("CardSpawnPoint"));
	cardSpawnPoint->SetupAttachment(RootComponent);
	deckMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Deck"));
	deckMesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABaseCardPlayer::BeginPlay()
{
	Super::BeginPlay();
	gameMode = Cast<ACardGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
	
}

// Called every frame
void ABaseCardPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCardPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABaseCardPlayer::DealCards()
{
	for (int i = 0; i < 10; i++)
	{
		int randomNum = FMath::RandRange(0, deck.Num()-1);
		ABaseCard* card = GetWorld()->SpawnActor<ABaseCard>(deck[randomNum], cardSpawnPoint->GetComponentTransform());
		card->SetOwner(this);
		hand.Add(card);
		deck.RemoveSingle(card->GetClass());
	}
	OrganizeCards();
	
	
}

void ABaseCardPlayer::SetGamePlayer(ABaseCardPlayer* player, bool isHuman)
{
	if (isHuman)
	{
		gameMode->SetPlayer(player);
	}
	else
	{
		gameMode->SetEnemy(player);
	}
}

void ABaseCardPlayer::OrganizeCards()
{
	for (int i = 1; i < hand.Num(); i++)
	{
		hand[i]->SetActorLocation(FVector(hand[i - 1]->GetActorLocation().X + cardSpacing, hand[0]->GetActorLocation().Y, hand[0]->GetActorLocation().Z));
		
	}
}

void ABaseCardPlayer::RemoveFromHand(ABaseCard* cardToRemove)
{
	hand.Remove(cardToRemove);
	MoveCard(cardToRemove);
	OrganizeCards();
}
