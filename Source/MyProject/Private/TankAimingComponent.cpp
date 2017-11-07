// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankAimingComponent.h"
#include "TankBarrelComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent() :
	barrel(nullptr)
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
		MoveBarrel(direction);
		UE_LOG(LogTemp, Warning, TEXT("Tank (%s) aiming at %s with launch speed %f"), *ownerName, *direction.ToString(), launchSpeed);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank (%s) AimAt could not suggest projectile velocity"), *ownerName);
	}
}

void UTankAimingComponent::MoveBarrel(const FVector& direction)
{
	auto rotation = direction.Rotation();
	if (rotation.Pitch > 0.f)
	{
		barrel->ElevateBarrel(1.f);
	}
	else if (rotation.Pitch < 0.f)
	{
		barrel->ElevateBarrel(-1.f);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrelComponent* barrelMesh)
{
	barrel = barrelMesh;
}