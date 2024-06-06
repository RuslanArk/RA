// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RAProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class RA_API ARAProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	ARAProjectile();

protected:
	virtual void BeginPlay() override;

private:	
	UFUNCTION()
	void OnProjectileImpact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UProjectileMovementComponent* ProjectileMovement = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	USphereComponent* ProjectileCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ProjectileMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	float CollisionInitialRadius = 20.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	float InitialSpeed = 2000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	float MaxSpeed = 2500.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parameters")
	float Damage = 25.f;
	
};
