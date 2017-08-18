// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "TankWheel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent) )
class BATTLE_TANK_API UTankWheel : public UStaticMeshComponent
{
  GENERATED_BODY()

    public:
    UTankWheel();

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    float Radius = 40.0f;
    
    float SuspensionCompressionLength;
       
 private:
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

    void UpdateRotation(float DeltaTime);
        
};
