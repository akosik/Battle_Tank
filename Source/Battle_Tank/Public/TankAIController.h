// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 *
 */
UCLASS()
class BATTLE_TANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

          private:
          ATank* GetAITank() const;
        virtual void BeginPlay() override;
        virtual void Tick(float DeltaSeconds) override;
        ATank* GetPlayerTank() const;

};
