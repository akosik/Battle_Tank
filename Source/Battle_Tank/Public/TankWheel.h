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
    float Radius = 35;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FName WheelSocket;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FVector InwardDirection = FVector(0,0,1);

    float SuspensionCompressionLength;

    float VerticalAcceleration;
    float VerticalVelocity = .00001f;
       
 private:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

    void UpdateRotation(float DeltaTime);
    void UpdateLocation(float DeltaTime);
    
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
    
};
