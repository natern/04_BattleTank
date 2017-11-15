// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UUserWidget;
class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class MYPROJECT_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

    UFUNCTION(BlueprintImplementableEvent, Category = "State")
    void FoundAimingComponent(UTankAimingComponent* aimingComponent);

    UFUNCTION(BlueprintImplementableEvent, Category = "State")
    void OnFiringStateChanged(UTankAimingComponent* aimingComponent);

	UPROPERTY(EditDefaultsOnly)
	float reticuleX = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float reticuleY = 0.33333f;

	UPROPERTY(EditDefaultsOnly)
	float rayLength = 500000;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;
	
protected:
	//UFUNCTION(BlueprintCallable, Category = "Setup")

private:
	void Aim();
	bool DoRaycast(FVector& hitLocation) const;

    UTankAimingComponent* aimingComponent;
};
