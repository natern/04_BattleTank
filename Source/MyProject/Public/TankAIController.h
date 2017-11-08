// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class MYPROJECT_API ATankAIController : public AAIController
{
	GENERATED_BODY()
public:
	ATankAIController();
	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	bool fireConstantly;
private:
	void Aim();
};
