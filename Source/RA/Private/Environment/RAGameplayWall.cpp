// Fill out your copyright notice in the Description page of Project Settings.


#include "Environment/RAGameplayWall.h"

#include "TimerManager.h"


ARAGameplayWall::ARAGameplayWall()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	WallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wall Mesh"));
	WallMesh->SetupAttachment(GetRootComponent());
	WallMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	WallMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	WallMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	
}

void ARAGameplayWall::BeginPlay()
{
	Super::BeginPlay();
	
	GetWallAway();
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
	GetWorldTimerManager().SetTimer(WallLiftTimer, this, &ARAGameplayWall::GetWallAway, 0.1f);
}
