// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent), hidecategories = ("Collision", "Physics"))
class MYPROJECT_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankBarrelComponent();
	void ElevateBarrel(const float degreesPerSecond);

protected:
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxDegreesPerSecond;
	UPROPERTY(EditAnywhere, Category = Setup)
	float minElevationDegrees;
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxElevationDegrees;
	UPROPERTY(EditAnywhere, Category = Setup)
	float thresholdDegrees;
};
