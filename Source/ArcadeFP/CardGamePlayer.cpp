// Fill out your copyright notice in the Description page of Project Settings.


#include "CardGamePlayer.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CardGameMode.h"
#include "BaseCard.h"
#include "CardGameMode.h"

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
	ShuffleDeck();
	gameMode = Cast<ACardGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
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
	
	if (gameMode->cardGameState == CardGameState::Blitz)
	{
		APlayerController* APC = UGameplayStatics::GetPlayerController(this, 0);
		if (APC)
		{
			FHitResult hit;
			if (APC->GetHitResultUnderCursor(ECC_Visibility, true, hit))
			{
				ABaseCard* card = Cast<ABaseCard>(hit.GetActor());
				if (card)
				{
					if (card->GetOwner() == this && gameMode->isPlayerInTurn(this))
					{
						gameMode->SetOldPlayerAmount();
						card->UseSpecialEffect();
						GetCardGameMode()->BlitzRound(card->GetCardValue(), this);
						RemoveFromHand(card);
					}
				}
			}
		}
	}
	else if (gameMode->cardGameState == CardGameState::Skirmish)
	{
		APlayerController* APC = UGameplayStatics::GetPlayerController(this, 0);
		if (APC)
		{
			FHitResult hit;
			if (APC->GetHitResultUnderCursor(ECC_GameTraceChannel3, true, hit))
			{
				TSubclassOf<ABaseCard> cardClass = GetDeck()[0];
				if (cardClass && gameMode->isPlayerInTurn(this))
				{
					ABaseCard* card;
					Skirmish(cardClass, card);
					gameMode->SkirmishRound(card->GetCardValue(), this);
				}
			}
		}
	}

}

