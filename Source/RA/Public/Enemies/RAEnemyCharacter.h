// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/RAPlayerCharacter.h"
#include "RAEnemyCharacter.generated.h"


UCLASS()
class RA_API ARAEnemyCharacter : public ARACharacter
{
	GENERATED_BODY()
	
public:
	ARAEnemyCharacter();

protected:
	virtual void BeginPlay() override;
	
};
