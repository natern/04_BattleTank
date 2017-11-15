// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrelComponent;
class UTurretComponent;

UENUM()
enum class EFiringState : uint8
{
	E_RELOADING = 0,
	E_AIMING,
	E_READY
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
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

    UFUNCTION(BlueprintCallable, Category = "Setup")
    void Initialize(UTurretComponent* turretMesh, UTankBarrelComponent* barrelMesh);

	void AimAt(const FVector& hitLocation, float launchSpeed);
	void MoveTurretAndBarrel(const FVector& direction);
    bool IsReloaded() const;
	void SetReloading();
	void SetReloaded();

    FVector GetLaunchPosition() const;
    FRotator GetLaunchRotation() const;

	UFUNCTION(BlueprintCallable, Category = "State")
	EFiringState GetFiringState() const;

private:
	EFiringState firingState;
	UTankBarrelComponent* barrel;
	UTurretComponent* turret;
    float reloadTime;
    double lastFireTime;
};
