// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTreadComponent;
/**
 * Provides Fly-By-Wire movement to a tank with AI-Nav support for AI
 */
UCLASS(ClassGroup =(Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:
	UTankMovementComponent();
	
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankTreadComponent* leftTrack, UTankTreadComponent* rightTrack);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward();

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveReverse();

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnLeft();

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight();

	UPROPERTY(EditDefaultsOnly, Category = Input)
	FKey forwardKey;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	FKey reverseKey;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	FKey leftKey;
	UPROPERTY(EditDefaultsOnly, Category = Input)
	FKey rightKey;
private:
	UTankTreadComponent* trackLeft;
	UTankTreadComponent* trackRight;

	float leftThrottle, rightThrottle;
	
};
