// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WAMTarget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHitTarget, int, pointsToGiveScore);

UCLASS()
class ARCADEFP_API AWAMTarget : public AActor
{
	GENERATED_BODY()
	//FPreviewScene
public:	
	// Sets default values for this actor's properties
	AWAMTarget();

	FOnHitTarget onHitTarget;

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

	FTimerHandle exampleHandle;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};