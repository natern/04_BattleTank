// Fill out your copyright notice in the Description page of Project Settings.

#include "MyProject.h"
#include "TurretComponent.h"

UTurretComponent::UTurretComponent() :
	maxDegreesPerSecond(30.f)
{
}

void UTurretComponent::RotateTurret(float relativeYaw)
{
	if (relativeYaw > 180.f)
	{
		relativeYaw -= 360.f;
	}
	if (relativeYaw < -180.f)
	{
		relativeYaw += 360.f;
	}
	relativeYaw = FMath::Clamp<float>(relativeYaw, -1.f, 1.f);

	FRotator resultRotation(0.f);
	resultRotation.Yaw = (relativeYaw * maxDegreesPerSecond * GetWorld()->GetDeltaSeconds());
	resultRotation.Yaw += RelativeRotation.Yaw;
	resultRotation.Yaw = resultRotation.Yaw > 360.f ? resultRotation.Yaw - 360.f : resultRotation.Yaw;
	resultRotation.Yaw = resultRotation.Yaw < -360.f ? resultRotation.Yaw + 360.f : resultRotation.Yaw;
	SetRelativeRotation(resultRotation);
}




