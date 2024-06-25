// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "RACharacter.generated.h"

class USphereComponent;
class URAAttributes;
class UGameplayAbility;
class URAAbilitySystemComponent;
class UGameplayEffect;

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

	USphereComponent* GetMeleeCollision() const { return MeleeAttackCollision; }

protected:
	UFUNCTION(BlueprintCallable)
	virtual void ActivatePrimaryAbility(const FGameplayTagContainer& PrimaryTags);

private:
	UFUNCTION()
	void OnMeleeColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
protected:
	UPROPERTY()
	TObjectPtr<URAAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<URAAttributes> AttributeSet;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Ability")
	TSubclassOf<UGameplayEffect> DefaultAttributesEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Melee")
	USphereComponent* MeleeAttackCollision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	FName MeleeCollisionAttachmentSocketName { "MeleeSocket" };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	FGameplayTag MeleeAttackEventTag {};
	
};

