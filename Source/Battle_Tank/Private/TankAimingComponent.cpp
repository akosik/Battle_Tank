// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle_Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


void UTankAimingComponent::AimAt(FVector& HitLocation, float LaunchSpeed)
{
  if(!Barrel) { return; }
  FVector OutLaunchVelocity;
  FVector StartLocation = Barrel->GetSocketLocation(FName("FiringPoint"));
  if( UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace) )
    {
      FVector AimDirection = OutLaunchVelocity.GetSafeNormal();
      MoveBarrelTowards(AimDirection);
    }
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
  Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
  Turret = TurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
  // Find difference between aim direction and current direction
  FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
  FRotator AimAsRotator = AimDirection.Rotation();
  FRotator DeltaRotator = AimAsRotator - BarrelRotator;

  Turret->Rotate(DeltaRotator.Yaw);
  Barrel->Elevate(DeltaRotator.Pitch);
}
