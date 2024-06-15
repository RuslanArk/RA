// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "RAPlayerState.generated.h"

class URAAbilitySystemComponent;

UCLASS()
class RA_API ARAPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARAPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY()	
	TObjectPtr<URAAbilitySystemComponent> AbilitySystemComponent;

		
};
