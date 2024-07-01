// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "RAAttributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

#define NUMERIC_VALUE(AttributeSetName, PropertyName) \
	AttributeSetName->Get##PropertyName##Attribute().GetNumericValue(AttributeSetName)

UCLASS()
class RA_API URAAttributes : public UAttributeSet
{
	GENERATED_BODY()

public:
	URAAttributes();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UFUNCTION(BlueprintCallable)
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION(BlueprintCallable)
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION(BlueprintCallable)
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	UFUNCTION(BlueprintCallable)
	void OnRep_MaxStamina(const FGameplayAttributeData& OldSMaxStamina);

	UFUNCTION(BlueprintCallable)
	void OnRep_Strength(const FGameplayAttributeData& OldStrength);

	UFUNCTION(BlueprintCallable)
	void OnRep_MaxStrength(const FGameplayAttributeData& OldSMaxStrength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Attributes")
	FGameplayAttributeData Health;

	ATTRIBUTE_ACCESSORS(URAAttributes, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Attributes")
	FGameplayAttributeData MaxHealth;

	ATTRIBUTE_ACCESSORS(URAAttributes, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Attributes")
	FGameplayAttributeData Stamina;

	ATTRIBUTE_ACCESSORS(URAAttributes, Stamina);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Attributes")
	FGameplayAttributeData MaxStamina;

	ATTRIBUTE_ACCESSORS(URAAttributes, MaxStamina);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Attributes")
	FGameplayAttributeData Strength;

	ATTRIBUTE_ACCESSORS(URAAttributes, Strength);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStrength, Category = "Attributes")
	FGameplayAttributeData MaxStrength;

	ATTRIBUTE_ACCESSORS(URAAttributes, MaxStrength);
};
