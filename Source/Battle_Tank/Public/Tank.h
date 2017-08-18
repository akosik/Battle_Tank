// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLE_TANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
  UFUNCTION(BlueprintPure, Category = "Health")
  float GetHealthPercent() const;

  // Multicast dynamic delegate, alerts controllers of tank death
  FTankDelegate OnDeath;

  UFUNCTION(BlueprintCallable, Category = "Death")
    void Die();

  UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FVector CenterOfMass;

 protected:
  UFUNCTION(BlueprintCallable, Category = "Forces")
    void UprightTank();

private:
	// Sets default values for this pawn's properties
	ATank();

        virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

        float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

        // Wrapper for calling Destroy after tank death
        void DestroyTank();

        UPROPERTY(EditDefaultsOnly, Category = "Setup")
         int32 MaxHealth = 5;

        int32 CurrentHealth;

        UPROPERTY(EditDefaultsOnly, Category = "Setup")
          int32 UprightForceStrength = 100000000;
};
