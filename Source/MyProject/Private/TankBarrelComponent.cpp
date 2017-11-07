// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankBarrelComponent.h"

UTankBarrelComponent::UTankBarrelComponent() :
	maxDegreesPerSecond(30.f),
	minElevationDegrees(0.f),
	maxElevationDegrees(35.f)
{
}

void UTankBarrelComponent::ElevateBarrel(const float degreesPerSecond)
{
	if(degreesPerSecond == 0.f)
	{
		return;
	}

	FRotator resultElevation = RelativeRotation;
	resultElevation.Yaw = 0.f;
	resultElevation.Roll = 0.f;
	float deltaSeconds = GetWorld()->GetDeltaSeconds();
	if (degreesPerSecond > 0.f)
	{
		resultElevation.Pitch += maxDegreesPerSecond * deltaSeconds;
		resultElevation.Pitch = FMath::Min<float>(resultElevation.Pitch, maxElevationDegrees);
	}
	else if (degreesPerSecond < 0.f)
	{
		resultElevation.Pitch -= maxDegreesPerSecond * deltaSeconds;
		resultElevation.Pitch = FMath::Max<float>(resultElevation.Pitch, minElevationDegrees);
	}
	SetRelativeRotation(resultElevation);
}

