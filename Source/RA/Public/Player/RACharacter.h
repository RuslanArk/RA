// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "RACharacter.generated.h"

struct FGameplayTagContainer;
class UGameplayAbility;
class URAAbilitySystemComponent;

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ARACharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARACharacter();
	
	UFUNCTION(BlueprintCallable)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// To add mapping context
	virtual void BeginPlay();

	void GiveDefaultAbilities();

protected:
	UFUNCTION(BlueprintCallable)
	virtual void ActivatePrimaryAbility(const FGameplayTagContainer& PrimaryTags);

protected:	
	UPROPERTY()
	TObjectPtr<URAAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

};

