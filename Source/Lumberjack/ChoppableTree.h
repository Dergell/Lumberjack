// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChoppableTree.generated.h"

UCLASS()
class LUMBERJACK_API AChoppableTree : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChoppableTree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Callback for OnTakePointDamage
	UFUNCTION()
	void TakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser);

private:
	// Replace mesh, enable physics
	void TriggerCutDown();
	
	// Mesh of the tree
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	// Mesh will be replaced with ChoppedMesh once chopped down
	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* ChoppedMesh;
	
	// Particle effect spawned when taking damage
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* TakeDamageEffect;

	// Simple health attribute
	UPROPERTY(EditAnywhere)
	float Health = 100;
};