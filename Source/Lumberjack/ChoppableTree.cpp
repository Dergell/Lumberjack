// Fill out your copyright notice in the Description page of Project Settings.

#include "ChoppableTree.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AChoppableTree::AChoppableTree()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	RootComponent = Mesh;

	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionProfileName(FName("Destructible"), false);
}

// Called when the game starts or when spawned
void AChoppableTree::BeginPlay()
{
	Super::BeginPlay();

	OnTakePointDamage.AddDynamic(this, &AChoppableTree::TakePointDamage);
}

// Called every frame
void AChoppableTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AChoppableTree::TakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	UGameplayStatics::SpawnEmitterAtLocation(
		this,
		TakeDamageEffect,
		HitLocation,
		ShotFromDirection.Rotation().GetInverse()
	);

	Health -= Damage;

	if (Health <= 0)
	{
		TriggerCutDown();
	}
}

void AChoppableTree::TriggerCutDown()
{
	if (!ChoppedMesh)
	{
		Destroy();
		return;
	}

	Mesh->SetStaticMesh(ChoppedMesh);
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionProfileName(FName("BlockAllDynamic"));
}