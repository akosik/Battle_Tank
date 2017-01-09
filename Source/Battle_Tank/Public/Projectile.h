// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLE_TANK_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

        void LaunchProjectile(float LaunchSpeed);

        void OnTimerExpire();

 private:

        UFUNCTION()
        void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

        UProjectileMovementComponent* ProjectileMovement = nullptr;

        UPROPERTY(VisibleAnywhere, Category = "Setup")
          UStaticMeshComponent* CollisionMeshComp = nullptr;

        UPROPERTY(VisibleAnywhere, Category = "Setup")
          UParticleSystemComponent* LaunchBlast = nullptr;

        UPROPERTY(VisibleAnywhere, Category = "Setup")
          UParticleSystemComponent* ImpactBlast = nullptr;

        UPROPERTY(VisibleAnywhere, Category = "Setup")
          URadialForceComponent* ExplosionForce = nullptr;

        UPROPERTY(EditDefaultsOnly, Category = "Setup")
          float DestroyDelay = 5.f;

        UPROPERTY(EditDefaultsOnly, Category = "Setup")
          float ProjectileDamage = 1.f;
};
