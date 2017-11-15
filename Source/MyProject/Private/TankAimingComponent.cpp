// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"
#include "TurretComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() :
    launchSpeed(50000.f),
    reloadTime(1.f),
	firingState(EFiringState::E_RELOADING),
	barrel(nullptr),
	turret(nullptr),
    lastFireTime(0.0)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    if(firingState == EFiringState::E_RELOADING)
    {
        bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTime;
        if(isReloaded)
        {
            firingState = EFiringState::E_AIMING;
        }
    }
	// ...
}

void UTankAimingComponent::AimAt(const FVector& hitLocation)
{
	if(!ensure(barrel))
	{
		UE_LOG(LogTemp, Warning, TEXT("Error: barrel of UTankAimingComponent is NULL"));
		return;
	}
	FVector launchVelocity;
	FVector launchPosition = barrel->GetProjectileLaunchPosition();
	float traceRadius(50.f);
	const auto ownerName = GetOwner()->GetName();
	if(UGameplayStatics::SuggestProjectileVelocity(this, launchVelocity, launchPosition, hitLocation, launchSpeed, false, traceRadius, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		FVector direction = launchVelocity.GetSafeNormal();
		MoveTurretAndBarrel(direction);
	}
	else
	{
		launchVelocity = hitLocation - launchPosition;
		launchVelocity = launchVelocity.GetSafeNormal();
		MoveTurretAndBarrel(launchVelocity);
		//UE_LOG(LogTemp, Warning, TEXT("Tank (%s) AimAt could not suggest projectile velocity"), *ownerName);
	}
}

void UTankAimingComponent::MoveTurretAndBarrel(const FVector& direction)
{
	auto barrelRotator = barrel->GetForwardVector().Rotation();
	auto aimRotator = direction.Rotation();
	auto deltaRotator = aimRotator - barrelRotator;
	if (deltaRotator.Vector().SizeSquared() < 0.1f)
	{
		firingState = EFiringState::E_READY;
	}
	else if(firingState != EFiringState::E_AIMING)
	{
		firingState = EFiringState::E_AIMING;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Barrel yaw: %f, aim yaw: %f, delta yaw: %f"), barrelRotator.Yaw, aimRotator.Yaw, deltaRotator.Yaw);
	barrel->ElevateBarrel(deltaRotator.Pitch);
	turret->RotateTurret(deltaRotator.Yaw);
}

void UTankAimingComponent::Initialize(UTurretComponent* turretMesh, UTankBarrelComponent* barrelMesh)
{
	turret = turretMesh;
	barrel = barrelMesh;
}

bool UTankAimingComponent::IsReloaded() const
{
    return(firingState != EFiringState::E_RELOADING);
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return(firingState);
}

void UTankAimingComponent::SetReloading()
{
    if(firingState != EFiringState::E_RELOADING)
    {
        firingState = EFiringState::E_RELOADING;
        lastFireTime = FPlatformTime::Seconds();
    }
}

void UTankAimingComponent::SetReloaded()
{
	if(firingState == EFiringState::E_RELOADING)
	{
		firingState = EFiringState::E_AIMING;
	}
}

void UTankAimingComponent::Fire()
{
    if(IsReloaded())
    {
        SetReloading();
        AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(projectileType, barrel->GetProjectileLaunchPosition(), barrel->GetProjectileLaunchRotation());
        if(projectile)
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
        SetReloading();
    }
}