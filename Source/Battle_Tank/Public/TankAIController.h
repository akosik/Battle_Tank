// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 *
 */
UCLASS()
class BATTLE_TANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

          private:
        virtual void Tick(float DeltaSeconds) override;

        virtual void SetPawn(APawn* InPawn) override;

        UPROPERTY(EditDefaultsOnly, Category = "Test")
        float AcceptanceRadius = 8000;

        UFUNCTION()
          void OnTankDeath();

};
