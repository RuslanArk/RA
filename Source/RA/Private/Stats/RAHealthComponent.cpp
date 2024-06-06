// Fill out your copyright notice in the Description page of Project Settings.


#include "Stats/RAHealthComponent.h"

#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY_STATIC(LogRAHealthComponent, All, All);

URAHealthComponent::URAHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
	
}

void URAHealthComponent::AddHealth(const int32 Quantity)
{
	if (Health + Quantity <= 0)
	{
		Health = 0;
		return;
	}
	else if (Health + Quantity >= MaxHealth)
	{
		Health = MaxHealth;
		return;
	}
	
	Health += Quantity;
}

void URAHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URAHealthComponent, Health);
	DOREPLIFETIME(URAHealthComponent, MaxHealth);
}

void URAHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void URAHealthComponent::OnRep_Health()
{
	UE_LOG(LogRAHealthComponent, Warning, TEXT("Health replicated, quantity: %i"), Health);
}

