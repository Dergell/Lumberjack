// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UBoxComponent;

UCLASS()
class LUMBERJACK_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Setter to enable/disable damage on overlap
	UFUNCTION(BlueprintSetter)
	void SetDamageEnabled(bool NewValue);

protected:
	// Callback for OnComponentBeginOverlap
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult);

private:
	// Mesh of the weapon
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	// Overlap collision trigger
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* Collision;

	// Damage amount on hit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int DamageAmount = 10;

	// Controls if an overlap can apply damage
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bDamageEnabled = false;
};