// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/RAGameplayWall.h"

#include "TimerManager.h"


ARAGameplayWall::ARAGameplayWall()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
}

void ARAGameplayWall::BeginPlay()
{
	Super::BeginPlay();
		
}

void ARAGameplayWall::GetWallAway()
{
	FVector TargetPosition = GetActorLocation();
	if (TargetPosition.Z == TargetHeight)
	{
		GetWorldTimerManager().ClearTimer(WallLiftTimer);
		return;
	}
	TargetPosition.Z += LiftingStep;
	SetActorLocation(FMath::VInterpTo(GetActorLocation(), TargetPosition, 0.1f, LiftingSpeed));
}
