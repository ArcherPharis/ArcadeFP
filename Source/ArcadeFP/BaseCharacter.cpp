// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "BaseArcadeMachine.h"
#include "InteractableComponent.h"
#include "BaseArcadeMachine.h"
#include "Interacter.h"
#include "Kismet/GameplayStatics.h"
#include "ArcadeGameController.h"
#include "InGameUI.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	interacter = CreateDefaultSubobject<UInteracter>(TEXT("Interacter"));
	interacter->SetupAttachment(GetRootComponent());
	

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	controller = Cast<AArcadeGameController>(UGameplayStatics::GetPlayerController(this, 0));

	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ABaseCharacter::Interact);

}

void ABaseCharacter::InitCurrentInteractable()
{
	if (interacter->GetInteractable())
	{
		
		ABaseArcadeMachine* arcade = Cast<ABaseArcadeMachine>(interacter->GetInteractable()->GetOwner());
		arcade->LoadLevel((arcade->GetLevelName()));
	}
	
}

void ABaseCharacter::Interact()
{
	if (interacter->GetInteractable())
	{
		controller->SetInputMode(FInputModeUIOnly());
		controller->SetShowMouseCursor(true);
		ABaseArcadeMachine* arcade = Cast<ABaseArcadeMachine>(interacter->GetInteractable()->GetOwner());
		if (arcade)
		{
			onInteract.Broadcast(arcade);
			InteractEffect();
			interacter->InitiateInteract();
		}
	
		
	}
	
}

