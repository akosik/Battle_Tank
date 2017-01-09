// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringStatus : uint8
{
  Locked,
    Aiming,
    Reloading,
    OutOfAmmo
    };

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
  void AimAt(FVector& HitLocation);

  UFUNCTION(BlueprintCallable, Category = "Setup")
  void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

  UFUNCTION(BlueprintCallable, Category = "Setup")
  void Fire();

  EFiringStatus GetFiringState() const;

  UFUNCTION(BlueprintCallable, Category = "Firing")
  int32 GetAmmo() const;

 protected:
  UPROPERTY(BluePrintReadOnly, Category = "State")
  EFiringStatus EFiringState = EFiringStatus::Aiming;

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 Ammo = 5;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

        void MoveBarrelTowards();

        virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

        bool IsBarrelMoving();

        UTankBarrel* Barrel = nullptr;

        UTankTurret* Turret = nullptr;

        UPROPERTY(EditDefaultsOnly, Category = "Firing")
          float LaunchSpeed = 4000;

        UPROPERTY(EditDefaultsOnly, Category = "Setup")
          TSubclassOf<AProjectile> ProjectileBlueprint;

        UPROPERTY(EditDefaultsOnly, Category = "Firing")
          float ReloadTime = 3;

        double LastFireTime = 0;

        FVector AimDirection = FVector(0);

};
