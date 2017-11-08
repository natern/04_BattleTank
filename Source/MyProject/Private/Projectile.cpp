// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	moveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	if (moveComponent)
	{
		moveComponent->bAutoActivate = true;
	}
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AProjectile::Launch(float speed)
{
	moveComponent->InitialSpeed = speed;
	moveComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	moveComponent->Activate();
}