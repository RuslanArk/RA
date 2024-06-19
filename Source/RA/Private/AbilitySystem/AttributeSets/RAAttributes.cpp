// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSets/RAAttributes.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

URAAttributes::URAAttributes()
{
	InitHealth(200.f);
}

void URAAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(URAAttributes, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URAAttributes, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URAAttributes, Stamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URAAttributes, MaxStamina, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URAAttributes, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URAAttributes, MaxStrength, COND_None, REPNOTIFY_Always);
}

void URAAttributes::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}
// Best to evaluate runtime attribute changes
void URAAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
}

void URAAttributes::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URAAttributes, Health, OldHealth);
}

void URAAttributes::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URAAttributes, MaxHealth, OldMaxHealth);
}

void URAAttributes::OnRep_Stamina(const FGameplayAttributeData& OldStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URAAttributes, Stamina, OldStamina);
}

void URAAttributes::OnRep_MaxStamina(const FGameplayAttributeData& OldSMaxStamina)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URAAttributes, MaxStamina, OldSMaxStamina);
}

void URAAttributes::OnRep_Strength(const FGameplayAttributeData& OldStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URAAttributes, Strength, OldStrength);
}

void URAAttributes::OnRep_MaxStrength(const FGameplayAttributeData& OldSMaxStrength)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URAAttributes, MaxStrength, OldSMaxStrength);
}
