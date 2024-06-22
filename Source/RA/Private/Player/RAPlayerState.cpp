// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RAPlayerState.h"

#include "AbilitySystem/RAAbilitySystemComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/RAAttributes.h"


ARAPlayerState::ARAPlayerState()
{
	NetUpdateFrequency = 100.f;
	
	AbilitySystemComponent = CreateDefaultSubobject<URAAbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<URAAttributes>("Attributes");
}

void ARAPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* ARAPlayerState::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(AbilitySystemComponent);
}

URAAttributes* ARAPlayerState::GetAttributes() const
{
	return AttributeSet;
}
