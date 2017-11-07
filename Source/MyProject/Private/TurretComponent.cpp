// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TurretComponent.h"

UTurretComponent::UTurretComponent() :
	maxDegreesPerSecond(30.f),
	thresholdDegrees(2.f)
{
}

void UTurretComponent::RotateTurret(float yaw)
{
	FRotator resultElevation = RelativeRotation;
	if(FMath::Abs<float>(yaw - resultElevation.Yaw) < thresholdDegrees)
	{
		return;
	}

	resultElevation.Roll = 0.f;
	resultElevation.Pitch = 0.f;
	float deltaSeconds = GetWorld()->GetDeltaSeconds();
	
	float diff = FMath::Abs(yaw - resultElevation.Yaw);
	
	if(diff < 180.f)
	{
		if (yaw > resultElevation.Yaw)
		{
			resultElevation.Yaw += maxDegreesPerSecond * deltaSeconds;
		}
		else
		{
			resultElevation.Yaw -= maxDegreesPerSecond * deltaSeconds;
		}
	}
	else
	{
		if (yaw > resultElevation.Yaw)
		{
			resultElevation.Yaw -= maxDegreesPerSecond * deltaSeconds;
		}
		else
		{
			resultElevation.Yaw += maxDegreesPerSecond * deltaSeconds;
		}
	}
	while(resultElevation.Yaw > 360.f)
	{
		resultElevation.Yaw -= 360.f;
	}
	SetRelativeRotation(resultElevation);
}




