// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrelComponent;
class UTurretComponent;

UCLASS(meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void AimAt(const FVector& hitLocation, float launchSpeed);
	void MoveTurretAndBarrel(const FVector& direction);
	void SetTurretAndBarrelReference(UTurretComponent* turretMesh, UTankBarrelComponent* barrelMesh);
private:
	UTankBarrelComponent* barrel;
	UTurretComponent* turret;
};
