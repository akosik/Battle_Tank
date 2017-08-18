
// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle_Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
  PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
  Super::BeginPlay();
  LastFireTime = FPlatformTime::Seconds();
  OnAimCompReady.Broadcast();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
  if(!Ammo) { EFiringState = EFiringStatus::OutOfAmmo; }
  else if( (FPlatformTime::Seconds() - LastFireTime) < ReloadTime ) { EFiringState = EFiringStatus::Reloading; }
  else if( IsBarrelMoving() ) { EFiringState = EFiringStatus::Aiming; }
  else { EFiringState = EFiringStatus::Locked; }
}

bool UTankAimingComponent::IsBarrelMoving()
{
  if(!ensure(Barrel)) { return true; }
  return !Barrel->GetForwardVector().Equals(AimDirection, .01);
}

EFiringStatus UTankAimingComponent::GetFiringState() const
{
  return EFiringState;
}

int32 UTankAimingComponent::GetAmmo() const
{
  return Ammo;
}


void UTankAimingComponent::AimAt(FVector& HitLocation)
{
  if(!ensure(Barrel)) { return; }
  FVector OutLaunchVelocity;
  FVector StartLocation = Barrel->GetSocketLocation(FName("FiringPoint"));
  if( UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace) )
    {
      AimDirection = OutLaunchVelocity.GetSafeNormal();
      MoveBarrelTowards();
    }
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
  Barrel = BarrelToSet;
  Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards()
{
  if(!ensure(Barrel && Turret)) { return; }
  // Find difference between aim direction and current direction
  FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
  FRotator AimAsRotator = AimDirection.Rotation();
  FRotator DeltaRotator = AimAsRotator - BarrelRotator;

  if(FMath::Abs(DeltaRotator.Yaw) < 180) { Turret->Rotate(DeltaRotator.Yaw); }
  else { Turret->Rotate(-DeltaRotator.Yaw); }
  Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::Fire()
{
  if(EFiringState != EFiringStatus::Reloading && EFiringState != EFiringStatus::OutOfAmmo)
    {
      if(!ensure(Barrel) && !ensure(ProjectileBlueprint)) { return; }
      AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("FiringPoint")), Barrel->GetSocketRotation(FName("FiringPoint")) );
      SpawnedProjectile->LaunchProjectile(LaunchSpeed);
      LastFireTime = FPlatformTime::Seconds();
      --Ammo;
    }
}
