// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/RAEnemyCharacter.h"

#include "AbilitySystem/RAAbilitySystemComponent.h"


ARAEnemyCharacter::ARAEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<URAAbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void ARAEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	GiveDefaultAbilities();
}
