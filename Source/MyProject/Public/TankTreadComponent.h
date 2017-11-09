// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTreadComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UTankTreadComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UTankTreadComponent();
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float val);

protected:

	//Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float maxDrivingForce;
};
