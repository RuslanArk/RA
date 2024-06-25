// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/RAGameplayAbility.h"
#include "RAMeleeAbility.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct FAbilityEnding
{
	GENERATED_USTRUCT_BODY()
	FAbilityEnding()
	{
		StructHandle = FGameplayAbilitySpecHandle();
		StructActorInfo = nullptr;
		StructActivationInfo = FGameplayAbilityActivationInfo();
		StructTriggerEventData = nullptr;
	}
	
	FAbilityEnding(const FGameplayAbilitySpecHandle Handle,
									  const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
									  const FGameplayEventData* TriggerEventData)
	{
		StructHandle = Handle;
		StructActorInfo = ActorInfo;
		StructActivationInfo = ActivationInfo;
		StructTriggerEventData = TriggerEventData;
	}

	FGameplayAbilitySpecHandle StructHandle;	
	const FGameplayAbilityActorInfo* StructActorInfo;
	FGameplayAbilityActivationInfo StructActivationInfo;
	const FGameplayEventData* StructTriggerEventData;
};

UCLASS()
class RA_API URAMeleeAbility : public URAGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UFUNCTION()
	void OnMontageFinished();

	UFUNCTION()
	void OnEventReceived(FGameplayEventData Payload);
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MontageTaskInstanceName { TEXT("None") };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Melee")
	FGameplayTag MeleeAttackEventTag {};
		
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* MeleeAttackMontage = nullptr;

private:
	FAbilityEnding AbilityEndingStruct;
	
};
