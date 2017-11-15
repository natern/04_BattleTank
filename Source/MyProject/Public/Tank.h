// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;
class UTankAimingComponent;

UCLASS()
class MYPROJECT_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
    UFUNCTION(BlueprintImplementableEvent, Category = "State")
    void FoundAimingComponent(UTankAimingComponent* aimingComponent);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	void AimAt(FVector hitLocation);	

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float launchSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float reloadTime;
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	TSubclassOf<AProjectile> projectileType;

private:
    UTankAimingComponent* tankAimingComponent;
};
