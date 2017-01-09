// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();
  AimComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
  if(ensure(AimComp)) { FoundAimingComponent(AimComp); }
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
  Super::SetPawn(InPawn);
  if(InPawn)
    {
      ATank* PossesedTank = Cast<ATank>(InPawn);
      if(!ensure(InPawn)) { return; }

      PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
    }
}

void ATankPlayerController::OnTankDeath()
{
  StartSpectatingOnly();
}

void ATankPlayerController::Tick( float deltatime )
{
  Super::Tick(deltatime);
  AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
  if(!AimComp) { return; }
  FVector HitLocation;
  if(GetSightRayHitLocation(HitLocation))
    {
      AimComp->AimAt(HitLocation);
    }

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
  int32 ViewportSizeX, ViewportSizeY;
  GetViewportSize(ViewportSizeX, ViewportSizeY);
  FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

  FVector LookDirection; // out param
  if (GetLookDirection(ScreenLocation, LookDirection))
    {
      GetLookVectorHitLocation(LookDirection, HitLocation);
    }
  return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D& ScreenLocation, FVector& LookDirection) const
{
  FVector CameraWorldLocation; // throw away
  return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& LookDirection, FVector& HitLocation) const
{
  FHitResult HitResult; // out param
  FVector StartRay = PlayerCameraManager->GetCameraLocation();
  FVector EndRay = StartRay + LookDirection * LineTraceRange;
  if( GetWorld()->LineTraceSingleByChannel(HitResult, StartRay, EndRay, ECollisionChannel::ECC_Visibility) )
    {
      HitLocation = HitResult.Location;
      return true;
    }
  return false;
}
