// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankBarrelComponent.h"

UTankBarrelComponent::UTankBarrelComponent() :
	maxDegreesPerSecond(30.f),
	minElevationDegrees(0.f),
	maxElevationDegrees(35.f)
{
}

void UTankBarrelComponent::ElevateBarrel( float relativePitch)
{
	relativePitch = FMath::Clamp<float>(relativePitch, -1.f, 1.f);
	FRotator resultElevation(0.f);
	resultElevation.Pitch = relativePitch * maxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	resultElevation.Pitch += RelativeRotation.Pitch;
	resultElevation.Pitch = FMath::Clamp<float>(resultElevation.Pitch, minElevationDegrees, maxElevationDegrees);
	SetRelativeRotation(resultElevation);
}

FVector UTankBarrelComponent::GetProjectileLaunchPosition() const
{
	return(GetSocketLocation(FName("LaunchPosition")));
}

FRotator UTankBarrelComponent::GetProjectileLaunchRotation() const
{
	return(GetSocketRotation(FName("LaunchPosition")));
}
