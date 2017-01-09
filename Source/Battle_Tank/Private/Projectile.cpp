// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
        CollisionMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(FName("CollisionMeshComp"));
        SetRootComponent(CollisionMeshComp);
        CollisionMeshComp->SetNotifyRigidBodyCollision(true);
        CollisionMeshComp->SetVisibility(false); //TODO set to false

        LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaunchBlast"));
        LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

        ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("ImpactBlast"));
        ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
        ImpactBlast->bAutoActivate = false;

        ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
        ProjectileMovement->bAutoActivate = false;

        ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("ExplosionForce"));
        ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
        CollisionMeshComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
  LaunchBlast->Deactivate();
  ImpactBlast->Activate();
  ExplosionForce->FireImpulse();

  SetRootComponent(ImpactBlast);
  CollisionMeshComp->DestroyComponent();
  FTimerHandle ProjectileTimerHandler;
  GetWorld()->GetTimerManager().SetTimer(ProjectileTimerHandler, this, &AProjectile::OnTimerExpire, DestroyDelay);

  UGameplayStatics::ApplyRadialDamage(this, ProjectileDamage, GetActorLocation(), ExplosionForce->Radius, UDamageType::StaticClass(), TArray<AActor*>() );
}

void AProjectile::OnTimerExpire()
{
  Destroy();
}

void AProjectile::LaunchProjectile(float LaunchSpeed)
{
  ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
  ProjectileMovement->Activate();
}
