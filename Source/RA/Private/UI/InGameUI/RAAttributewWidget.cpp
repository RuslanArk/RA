// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InGameUI/RAAttributewWidget.h"

#include "AbilitySystem/AttributeSets/RAAttributes.h"
#include "Components/ProgressBar.h"
#include "Player/RAPlayerState.h"

void URAAttributesWidget::BindToAttributes()
{
	const ARAPlayerState* RAPlayerState = Cast<ARAPlayerState>(GetOwningPlayerState());
	if (!RAPlayerState) return;

	UAbilitySystemComponent* AbilityComponent = RAPlayerState->GetAbilitySystemComponent();
	if (!AbilityComponent) return;
	
	const URAAttributes* Attributes = RAPlayerState->GetAttributes();
	if (!Attributes) return;

	// Initial Attributes
	HealthPercent = NUMERIC_VALUE(Attributes, Health) / NUMERIC_VALUE(Attributes, MaxHealth);
	StaminaPercent = NUMERIC_VALUE(Attributes, Stamina) / NUMERIC_VALUE(Attributes, MaxStamina);

	// Attribute Changes
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetHealthAttribute()).AddLambda(
		[this, Attributes](const FOnAttributeChangeData& Data)->void
		{
			HealthPercent = Data.NewValue / NUMERIC_VALUE(Attributes, MaxHealth);
			HealthBar->SetPercent(HealthPercent);
		});
	
	AbilityComponent->GetGameplayAttributeValueChangeDelegate(Attributes->GetStaminaAttribute()).AddLambda(
		[this, Attributes](const FOnAttributeChangeData& Data)->void
		{
			StaminaPercent = Data.NewValue / NUMERIC_VALUE(Attributes, MaxStamina);
			StaminaBar->SetPercent(StaminaPercent);
		});
}
