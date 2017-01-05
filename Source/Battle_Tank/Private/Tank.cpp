// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

        TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector& HitLocation)
{
  TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
  TankAimingComponent->SetBarrelReference(BarrelToSet);
  Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
  TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
  UE_LOG(LogTemp, Warning, TEXT("Firing at: %f"), LaunchSpeed)

  if(!Barrel) { return; }
  AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("FiringPoint")), Barrel->GetSocketRotation(FName("FiringPoint")) );

  SpawnedProjectile->LaunchProjectile(LaunchSpeed);
}
