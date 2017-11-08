// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TurretComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))//, hidecategories = ("Collision", "Physics") )
class MYPROJECT_API UTurretComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTurretComponent();
	void RotateTurret(float relativeYaw);

protected:
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxDegreesPerSecond;
};
