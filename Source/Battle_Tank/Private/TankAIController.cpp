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
  // Move Toward Player, and Aim at player
  APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
  UTankAimingComponent* AITankAimComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if (PlayerPawn && AITankAimComp)
    {
      MoveToActor(PlayerPawn, AcceptanceRadius);
      FVector PlayerPawnLocation = PlayerPawn->GetActorLocation();
      AITankAimComp->AimAt(PlayerPawnLocation);
      if(AITankAimComp->GetFiringState() == EFiringStatus::Locked) { AITankAimComp->Fire(); }
    }

  // If Controlled Tank is flipped over, die
  if (bIsFlippedOver()) { Cast<ATank>(GetPawn())->Die(); }
}

bool ATankAIController::bIsFlippedOver()
{
  return FVector::DotProduct(GetPawn()->GetActorUpVector(), FVector::UpVector) < 0;
}

void ATankAIController::OnTankDeath()
{
  if (!GetPawn()) { return; }
  GetPawn()->DetachFromControllerPendingDestroy();
}
