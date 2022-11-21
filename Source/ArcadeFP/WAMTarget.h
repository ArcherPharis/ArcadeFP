// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WAMTarget.generated.h"

UCLASS()
class ARCADEFP_API AWAMTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWAMTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, Category = "MoleSetup")
	USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = "MoleSetup")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = "MoleSetup")
	int pointValue = 10;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
