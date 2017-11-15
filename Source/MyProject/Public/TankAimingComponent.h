// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Projectile.h"
#include "TankAimingComponent.generated.h"

class UTankBarrelComponent;
class UTurretComponent;

UENUM()
enum class EFiringState : uint8
{
	E_RELOADING = 0,
	E_AIMING,
	E_READY,
    E_EMPTY
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

	UFUNCTION(BlueprintCallable, Category = "State")
	EFiringState GetFiringState() const;

    UFUNCTION(BlueprintCallable, Category = "Firing")
    void Fire();

    UFUNCTION(BlueprintCallable, Category = "Firing")
    uint8 GetAmmoCapacity() const;

    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float launchSpeed;
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    float reloadTime;
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    TSubclassOf<AProjectile> projectileType;

    void AimAt(const FVector& hitLocation);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Firing")
    uint8 ammoCapacity;

private:
    void MoveTurretAndBarrel(const FVector& direction);
    bool IsReloaded() const;
    void SetReloading();
    void SetReloaded();

	EFiringState firingState;
	UTankBarrelComponent* barrel;
	UTurretComponent* turret;
    double lastFireTime;
};
