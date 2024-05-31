// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RAGameplayWall.generated.h"

UCLASS()
class RA_API ARAGameplayWall : public AActor
{
	GENERATED_BODY()
	
public:
	ARAGameplayWall();

	UFUNCTION(BlueprintCallable)
	void GetWallAway();
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* WallMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall Params")
	float TargetHeight = 1000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall Params")
	float LiftingSpeed = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wall Params")
	float LiftingStep = 50.f;

private:
	FTimerHandle WallLiftTimer;
	
};
