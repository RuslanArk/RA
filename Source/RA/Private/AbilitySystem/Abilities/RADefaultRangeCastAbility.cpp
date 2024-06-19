// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/RADefaultRangeCastAbility.h"

DEFINE_LOG_CATEGORY_STATIC(LogGADefaultRangeCast, All, All);

void URADefaultRangeCastAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UE_LOG(LogGADefaultRangeCast, Display, TEXT("GADefaultRangeCast ability activated"));
}
