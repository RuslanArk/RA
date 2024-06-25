// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimNotifies/RAMeleeAttackState.h"

#include "Components/SphereComponent.h"
#include "Player/RACharacter.h"

void URAMeleeAttackState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (!MeshComp) return;

	const ARACharacter* Attacker = Cast<ARACharacter>(MeshComp->GetOwner());
	if (!Attacker || !Attacker->GetMeleeCollision()) return;

	Attacker->GetMeleeCollision()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void URAMeleeAttackState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!MeshComp) return;

	const ARACharacter* Attacker = Cast<ARACharacter>(MeshComp->GetOwner());
	if (!Attacker || !Attacker->GetMeleeCollision()) return;

	Attacker->GetMeleeCollision()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
