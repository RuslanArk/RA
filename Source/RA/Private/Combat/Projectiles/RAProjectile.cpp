// Fill out your copyright notice in the Description page of Project Settings.


#include "Combat/Projectiles/RAProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ARAProjectile::ARAProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Projectile Collision"));
	ProjectileCollision->InitSphereRadius(CollisionInitialRadius);
	ProjectileCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	ProjectileCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileCollision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	SetRootComponent(ProjectileCollision);
	
	if (GetLocalRole() == ROLE_Authority)
	{
		ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &ARAProjectile::OnProjectileImpact);
	}
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = InitialSpeed;
	ProjectileMovement->MaxSpeed = MaxSpeed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	
}

void ARAProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARAProjectile::OnProjectileImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}
