// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"
#include "Projectile.h"


// Sets default values
ATank::ATank() :
	launchSpeed(50000.f)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    tankAimingComponent = FindComponentByClass<UTankAimingComponent>();
    if(ensure(tankAimingComponent))
    {
        FoundAimingComponent(tankAimingComponent);
    }
}

void ATank::AimAt(FVector hitLocation)
{
    if(ensure(tankAimingComponent))
    {
        tankAimingComponent->AimAt(hitLocation, launchSpeed);
    }
}

void ATank::Fire()
{
	if(ensure(tankAimingComponent))
    {
        if(tankAimingComponent->IsReloaded())
		{
			tankAimingComponent->SetReloading();
			AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileType, tankAimingComponent->GetLaunchPosition(), tankAimingComponent->GetLaunchRotation());
			if (projectile)
			{
				projectile->Launch(launchSpeed);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Tank got NULL projectile"));
			}
		}
		else
		{
			tankAimingComponent->SetReloading();
		}
	}
}

