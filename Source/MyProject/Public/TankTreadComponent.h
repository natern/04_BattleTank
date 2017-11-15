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
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float val);

protected:

	//Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float maxDrivingForce;

    UPROPERTY(EditDefaultsOnly)
    float timeUntilAirborne;

private:
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    void ApplyDrivingForce();
    void CancelSidewaysMovement();

    float currentThrottle;
    double lastHitTime;
};
