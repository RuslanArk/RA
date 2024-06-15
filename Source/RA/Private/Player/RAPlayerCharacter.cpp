// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RAPlayerCharacter.h"

#include "AbilitySystem/RAAbilitySystemComponent.h"
#include "Player/RAPlayerState.h"

#include "AbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerCharacter, All, All);

// Sets default values
ARAPlayerCharacter::ARAPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void ARAPlayerCharacter::InitAbilitySystemComponent()
{
	ARAPlayerState* RAPlayerState = GetPlayerState<ARAPlayerState>();
	check(RAPlayerState);

	AbilitySystemComponent = CastChecked<URAAbilitySystemComponent>(RAPlayerState->GetAbilitySystemComponent());

	AbilitySystemComponent->InitAbilityActorInfo(RAPlayerState, this);
}

void ARAPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilitySystemComponent();
	GiveDefaultAbilities();
}

void ARAPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilitySystemComponent();
}

UAbilitySystemComponent* ARAPlayerCharacter::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(AbilitySystemComponent);
}

void ARAPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARAPlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
}
