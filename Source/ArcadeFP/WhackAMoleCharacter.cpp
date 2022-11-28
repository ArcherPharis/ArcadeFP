// Fill out your copyright notice in the Description page of Project Settings.


#include "WhackAMoleCharacter.h"
#include "Components/BoxComponent.h"

AWhackAMoleCharacter::AWhackAMoleCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	hammerHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hammer Hitbox"));
	hammerHitBox->SetupAttachment(GetMesh(), "HammerSocket");
	hammerHitBox->SetCollisionResponseToChannels(ECR_Ignore);
	


}

void AWhackAMoleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AWhackAMoleCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AWhackAMoleCharacter::MoveRight);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AWhackAMoleCharacter::Attack);
}

void AWhackAMoleCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AWhackAMoleCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AWhackAMoleCharacter::Attack()
{
	if (CanAttack())
	{
		GetWorldTimerManager().SetTimer(firingHandle, 1 / fireRate, false);
		GetMesh()->GetAnimInstance()->Montage_Play(attackingMontage);
	}
	
}

bool AWhackAMoleCharacter::CanAttack()
{
	return !GetWorldTimerManager().IsTimerActive(firingHandle);
}
