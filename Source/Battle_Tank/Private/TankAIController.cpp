// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::SetPawn(APawn* InPawn)
{
  Super::SetPawn(InPawn);
  if(InPawn)
    {
      ATank* PossessedTank = Cast<ATank>(InPawn);
      if(!ensure(PossessedTank)) { return; }

      PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
    }

}

void ATankAIController::Tick(float DeltaSeconds)
{
  APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
  UTankAimingComponent* AITankAimComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if(ensure(PlayerPawn && AITankAimComp))
    {
      MoveToActor(PlayerPawn, AcceptanceRadius);
      FVector PlayerPawnLocation = PlayerPawn->GetActorLocation();
      AITankAimComp->AimAt(PlayerPawnLocation);
      if(AITankAimComp->GetFiringState() == EFiringStatus::Locked) { AITankAimComp->Fire(); }
    }
}


void ATankAIController::OnTankDeath()
{
  if(!GetPawn()) { return; }
  GetPawn()->DetachFromControllerPendingDestroy();
}
