// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/RACharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/RAAbilitySystemComponent.h"

#include "AbilitySystemComponent.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(LogRACharacter, All, All);

//////////////////////////////////////////////////////////////////////////
// ARACharacter

ARACharacter::ARACharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
	MeleeAttackCollision = CreateDefaultSubobject<USphereComponent>("Melee AttackCollision");
	MeleeAttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeleeAttackCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeleeAttackCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	MeleeAttackCollision->SetIsReplicated(true);
}

void ARACharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (HasAuthority() && MeleeAttackCollision)
	{
		MeleeAttackCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, MeleeCollisionAttachmentSocketName);
		MeleeAttackCollision->OnComponentBeginOverlap.AddDynamic(this, &ARACharacter::OnMeleeColliderBeginOverlap);
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

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(MeleeEffect, CharacterLevel, ContextHandle);
	if (!SpecHandle.IsValid()) return;
				
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

	const FGameplayEffectSpecHandle RecoverySpecHandle = AbilitySystemComponent->MakeOutgoingSpec(StaminaRecoveryEffect, CharacterLevel, ContextHandle);
	if (!RecoverySpecHandle.IsValid()) return;
				
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*RecoverySpecHandle.Data.Get());
}

void ARACharacter::OnMeleeColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!HasAuthority() || !AbilitySystemComponent) return;
	
	if (OtherActor && OtherActor != this)
	{
		FGameplayEventData EventData;
		EventData.Instigator = this;
		EventData.Target = OtherActor;
		EventData.TargetData = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(OtherActor);
		
		AbilitySystemComponent->HandleGameplayEvent(MeleeAttackEventTag, &EventData);

		if (!MeleeEffect) return;
		
		if (IAbilitySystemInterface* AbilityActor = Cast<IAbilitySystemInterface>(OtherActor))
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
