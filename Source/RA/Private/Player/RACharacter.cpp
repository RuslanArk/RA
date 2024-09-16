// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/RACharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/RAAbilitySystemComponent.h"

#include "AbilitySystemComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogRACharacter, All, All);

//////////////////////////////////////////////////////////////////////////
// ARACharacter

ARACharacter::ARACharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	MeleeCombatCollision = CreateDefaultSubobject<UBoxComponent>("MeleeCombatCollision");
	MeleeCombatCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeleeCombatCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeCombatCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	MeleeCombatCollision->SetIsReplicated(true);
}

void ARACharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (HasAuthority() && MeleeCombatCollision)
	{
		MeleeCombatCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, MeleeCollisionAttachmentSocketName);
		MeleeCombatCollision->OnComponentBeginOverlap.AddDynamic(this, &ARACharacter::OnMeleeColliderBeginOverlap);
	}
}

void ARACharacter::GiveDefaultAbilities()
{
	check(AbilitySystemComponent);
	if (!HasAuthority()) return;

	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultAbilities)
	{
		const FGameplayAbilitySpec AbilitySpec { AbilityClass, 1 };
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

void ARACharacter::InitDefaultAttributes()
{
	if (!AbilitySystemComponent || !DefaultAttributesEffect) return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributesEffect, 1.f, EffectContext);

	if (SpecHandle.IsValid())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void ARACharacter::ActivatePrimaryAbility(const FGameplayTagContainer& PrimaryTags)
{
	if (UAbilitySystemComponent* AbilitySystemComp = GetAbilitySystemComponent())
	{
		AbilitySystemComp->TryActivateAbilitiesByTag(PrimaryTags);
	}
}

void ARACharacter::ApplyRecoveryEffectsToSelf()
{
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(HealthRecoveryEffect, CharacterLevel, ContextHandle);
	if (!SpecHandle.IsValid()) return;
				
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

	const FGameplayEffectSpecHandle RecoverySpecHandle = AbilitySystemComponent->MakeOutgoingSpec(StaminaRecoveryEffect, CharacterLevel, ContextHandle);
	if (!RecoverySpecHandle.IsValid()) return;
				
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*RecoverySpecHandle.Data.Get());
}

void ARACharacter::OnMeleeColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!AbilitySystemComponent) return;
	
	Server_ExecuteMeleeAttack(OtherActor);
}

void ARACharacter::Server_ExecuteMeleeAttack_Implementation(AActor* Victim)
{
	if (Victim && Victim != this)
	{
		FGameplayEventData EventData;
		EventData.Instigator = this;
		EventData.Target = Victim;
		EventData.TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(Victim);
		
		AbilitySystemComponent->HandleGameplayEvent(MeleeAttackEventTag, &EventData);

		if (!MeleeEffect) return;
		
		if (IAbilitySystemInterface* AbilityActor = Cast<IAbilitySystemInterface>(Victim))
		{
			FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
			ContextHandle.AddSourceObject(this);

			const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(MeleeEffect, CharacterLevel, ContextHandle);
			if (!SpecHandle.IsValid()) return;
				
			AbilityActor->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

			const FGameplayEffectSpecHandle HealthRecoverySpecHandle = AbilitySystemComponent->MakeOutgoingSpec(HealthRecoveryEffect, CharacterLevel, ContextHandle);
			if (!HealthRecoverySpecHandle.IsValid()) return;
				
			AbilityActor->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*HealthRecoverySpecHandle.Data.Get());
		}
	}

	ApplyRecoveryEffectsToSelf();
}

UAbilitySystemComponent* ARACharacter::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(AbilitySystemComponent);
}

URAAttributes* ARACharacter::GetAttributeSet() const
{
	return AttributeSet;
}
