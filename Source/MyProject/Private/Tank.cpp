// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"
#include "Projectile.h"


// Sets default values
ATank::ATank() :
	launchSpeed(50000.f),
	reloadTime(1.0f),
	lastFireTime(0.0)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	tankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::SetTurretAndBarrelReference(UTurretComponent* turretComponent, UTankBarrelComponent* barrelComponent)
{
	barrel = barrelComponent;
	tankAimingComponent->SetTurretAndBarrelReference(turretComponent, barrelComponent);
}

void ATank::AimAt(FVector hitLocation)
{
	tankAimingComponent->AimAt(hitLocation, launchSpeed);
}

void ATank::Fire()
{
	if (barrel)
	{
		bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTime;
		if (isReloaded)
		{
			lastFireTime = FPlatformTime::Seconds();
			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileType, barrel->GetProjectileLaunchPosition(), barrel->GetProjectileLaunchRotation());
			if (projectile)
			{
				projectile->Launch(launchSpeed);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Tank got NULL projectile"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank tried to fire with NULL barrel"));
	}
}

