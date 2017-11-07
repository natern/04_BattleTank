// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"
#include "TurretComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() :
	barrel(nullptr),
	turret(nullptr)
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

	// ...
}

void UTankAimingComponent::AimAt(const FVector& hitLocation, float launchSpeed)
{
	if(!barrel)
	{
		return;
	}

	FVector launchVelocity;
	FVector launchPosition = barrel->GetSocketLocation(FName("LaunchPosition"));
	float traceRadius(50.f);
	const auto ownerName = GetOwner()->GetName();
	if(UGameplayStatics::SuggestProjectileVelocity(this, launchVelocity, launchPosition, hitLocation, launchSpeed, false, traceRadius, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		FVector direction = launchVelocity.GetSafeNormal();
		MoveTurretAndBarrel(direction);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank (%s) AimAt could not suggest projectile velocity"), *ownerName);
	}
}

void UTankAimingComponent::MoveTurretAndBarrel(const FVector& direction)
{
	auto rotation = direction.Rotation();

	barrel->ElevateBarrel(rotation.Pitch);
	turret->RotateTurret(rotation.Yaw);
}

void UTankAimingComponent::SetTurretAndBarrelReference(UTurretComponent* turretMesh, UTankBarrelComponent* barrelMesh)
{
	turret = turretMesh;
	barrel = barrelMesh;
}