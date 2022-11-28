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

	UFUNCTION(BlueprintImplementableEvent, Category = "MoleSetup")
	void OnImpact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "WAM Target Spawner")
	void Despawn();

	UFUNCTION(BlueprintCallable, Category = "MoleSetup")
	UMeshComponent* GetMesh() const { return mesh; }


private:

	UPROPERTY(EditAnywhere, Category = "MoleSetup")
	USceneComponent* rootComp;

	UPROPERTY(EditAnywhere, Category = "MoleSetup")
	UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = "MoleSetup")
	int pointValue = 10;

	UPROPERTY(EditAnywhere, Category = "MoleSetup")
	UParticleSystem* explosionFX;



	UPROPERTY(EditDefaultsOnly, Category = "WAM Target Spawner")
	float despawnTimer = 4.5f;

	FTimerHandle despawnHandle;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
