// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrelComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))//, hidecategories = ("Collision", "Physics"))
class MYPROJECT_API UTankBarrelComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankBarrelComponent();
	void ElevateBarrel(float relativePitch);
	FVector GetProjectileLaunchPosition() const;
	FRotator GetProjectileLaunchRotation() const;
protected:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float maxDegreesPerSecond;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float minElevationDegrees;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float maxElevationDegrees;
};
