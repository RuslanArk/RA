// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/RAAbilitySystemComponent.h"


URAAbilitySystemComponent::URAAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
	
}

void URAAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void URAAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

