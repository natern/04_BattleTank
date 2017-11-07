// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TankBarrelComponent.h"

UTankBarrelComponent::UTankBarrelComponent() :
	maxDegreesPerSecond(30.f),
	minElevationDegrees(0.f),
	maxElevationDegrees(35.f),
	thresholdDegrees(2.f)
{
}

void UTankBarrelComponent::ElevateBarrel(const float pitch)
{
	FRotator resultElevation = RelativeRotation;
	if(FMath::Abs<float>(pitch - resultElevation.Pitch) < thresholdDegrees)
	{
		return;
	}
	resultElevation.Yaw = 0.f;
	resultElevation.Roll = 0.f;
	float deltaSeconds = GetWorld()->GetDeltaSeconds();
	if (pitch > resultElevation.Pitch)
	{
		resultElevation.Pitch += maxDegreesPerSecond * deltaSeconds;
		resultElevation.Pitch = FMath::Min<float>(resultElevation.Pitch, maxElevationDegrees);
	}
	else
	{
		resultElevation.Pitch -= maxDegreesPerSecond * deltaSeconds;
		resultElevation.Pitch = FMath::Max<float>(resultElevation.Pitch, minElevationDegrees);
	}
	SetRelativeRotation(resultElevation);
}

