// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
  void AimAt(FVector& HitLocation, float LaunchSpeed);

  void SetBarrelReference(UTankBarrel* BarrelToSet);

  void SetTurretReference(UTankTurret* TurretToSet);

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

        UTankBarrel* Barrel = nullptr;

        UTankTurret* Turret = nullptr;

        void MoveBarrelTowards(FVector AimDirection);

};
