// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
  Super::BeginPlay();

  ATank* player_tank = GetPlayerTank();
}

void ATankAIController::Tick(float DeltaSeconds)
{
  if(GetPlayerTank())
    {
      FVector PlayerTankLocation = GetPlayerTank()->GetActorLocation();
      GetAITank()->AimAt(PlayerTankLocation);
    }
}

ATank* ATankAIController::GetAITank() const
{
  return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
  ATank* player_tank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
  if(!player_tank) return nullptr;
  else return player_tank;
}
