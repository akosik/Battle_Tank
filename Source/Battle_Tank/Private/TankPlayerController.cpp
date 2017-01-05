// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
  Super::BeginPlay();
}

ATank* ATankPlayerController::GetControlledTank() const
{
  return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Tick( float deltatime )
{
  Super::Tick(deltatime);
  AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
  if(!GetControlledTank()) { return; }

  FVector HitLocation;
  if(GetSightRayHitLocation(HitLocation))
    {
      GetControlledTank()->AimAt(HitLocation);
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
