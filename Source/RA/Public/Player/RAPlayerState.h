// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "RAPlayerState.generated.h"

class URAAbilitySystemComponent;
class URAAttributes;
class UGameplayEffect;

UCLASS()
class RA_API ARAPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARAPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual URAAttributes* GetAttributes() const;
	
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY()	
	TObjectPtr<URAAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<URAAttributes> AttributeSet;
	
	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TSubclassOf<UGameplayEffect> DefaultAttributesEffect;

		
};
