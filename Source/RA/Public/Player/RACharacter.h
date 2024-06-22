// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "RACharacter.generated.h"

class URAAttributes;
struct FGameplayTagContainer;
class UGameplayAbility;
class URAAbilitySystemComponent;
class UGameplayEffect;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ARACharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARACharacter();
	
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	virtual URAAttributes* GetAttributeSet() const;

	// To add mapping context
	virtual void BeginPlay();

	void GiveDefaultAbilities();
	void InitDefaultAttributes();

protected:
	UFUNCTION(BlueprintCallable)
	virtual void ActivatePrimaryAbility(const FGameplayTagContainer& PrimaryTags);

protected:
	UPROPERTY()
	TObjectPtr<URAAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<URAAttributes> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TSubclassOf<UGameplayEffect> DefaultAttributesEffect;

};

