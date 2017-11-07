// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankBarrelComponent.h"

UTankBarrelComponent::UTankBarrelComponent() :
	maxDegreesPerSecond(100.f),
	minElevationDegrees(0.f),
	maxElevationDegrees(40.f)
{
}

void UTankBarrelComponent::ElevateBarrel(const float degreesPerSecond)
{
	if(degreesPerSecond == 0.f)
	{
		return;
	}

	FRotator resultElevation = GetForwardVector().Rotation();
	resultElevation.Yaw = 0.f;
	resultElevation.Roll = 0.f;
	float deltaSeconds = GetWorld()->GetDeltaSeconds();
	if (degreesPerSecond > 0.f)
	{
		resultElevation.Pitch += maxDegreesPerSecond * deltaSeconds;
		resultElevation.Pitch = resultElevation.Pitch > maxElevationDegrees ? maxElevationDegrees : resultElevation.Pitch;
	}
	else if (degreesPerSecond < 0.f)
	{
		resultElevation.Pitch -= maxDegreesPerSecond * deltaSeconds;
		resultElevation.Pitch = resultElevation.Pitch < minElevationDegrees ? minElevationDegrees : resultElevation.Pitch;
	}
	SetRelativeRotation(resultElevation);
}

