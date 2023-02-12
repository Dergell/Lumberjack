// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"

#include "Components/BoxComponent.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<UBoxComponent>(FName("Collision"));
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("Mesh"));

	RootComponent = Mesh;
	Collision->SetupAttachment(Mesh);

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionProfileName(FName("Destructible"), false);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::BeginOverlap);
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::SetDamageEnabled(bool NewValue)
{
	bDamageEnabled = NewValue;
}

void AWeapon::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep, const FHitResult& SweepResult)
{
	if (!bDamageEnabled)
	{
		return;
	}

	// Manually set the ImpactPoint to the collision box location, because SweepResult is empty for overlaps
	// TODO: find a better way to get the impact point
	FHitResult AdjustedHit(SweepResult);
	AdjustedHit.ImpactPoint = Collision->GetComponentLocation();
	FPointDamageEvent DamageEvent(DamageAmount, AdjustedHit, AdjustedHit.Normal, UDamageType::StaticClass());
	OtherActor->TakeDamage(DamageAmount, DamageEvent, GetInstigatorController(), this);
}