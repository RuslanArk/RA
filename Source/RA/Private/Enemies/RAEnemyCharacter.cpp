// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/RAEnemyCharacter.h"

#include "AbilitySystem/RAAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/RAAttributes.h"


ARAEnemyCharacter::ARAEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<URAAbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<URAAttributes>("Attributes");
}

void ARAEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	GiveDefaultAbilities();
	InitDefaultAttributes();
}
