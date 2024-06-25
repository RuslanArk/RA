// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Melee/RAMeleeAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"


void URAMeleeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!MeleeAttackMontage)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	
	UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, MontageTaskInstanceName, MeleeAttackMontage);
	if (!MontageTask)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}

	if (UAbilityTask_WaitGameplayEvent* WaitGameplayEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, MeleeAttackEventTag, nullptr, true))
	{
		WaitGameplayEvent->EventReceived.AddDynamic(this, &URAMeleeAbility::OnEventReceived);
	}	
	
	AbilityEndingStruct = FAbilityEnding(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	MontageTask->OnCompleted.AddDynamic(this, &URAMeleeAbility::OnMontageFinished);
	MontageTask->OnBlendOut.AddDynamic(this, &URAMeleeAbility::OnMontageFinished);
	MontageTask->OnInterrupted.AddDynamic(this, &URAMeleeAbility::OnMontageFinished);
	MontageTask->OnCancelled.AddDynamic(this, &URAMeleeAbility::OnMontageFinished);
	
	MontageTask->Activate();
}

void URAMeleeAbility::OnMontageFinished()
{
	EndAbility(AbilityEndingStruct.StructHandle, AbilityEndingStruct.StructActorInfo, AbilityEndingStruct.StructActivationInfo, true, true);
	AbilityEndingStruct = FAbilityEnding();
}

void URAMeleeAbility::OnEventReceived(FGameplayEventData Payload)
{
	if (!Payload.Target) return;

	
}
