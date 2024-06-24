// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Player/RACharacter.h"
#include "RAPlayerCharacter.generated.h"

class ARAProjectile;

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class RA_API ARAPlayerCharacter : public ARACharacter
{
	GENERATED_BODY()

public:
	ARAPlayerCharacter();	

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void BeginPlay();

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void ActivatePrimary();

	virtual void ActivatePrimaryAbility(const FGameplayTagContainer& PrimaryTags) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	

private:
	void InitAbilitySystemComponent();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer PrimaryAbilityTagsContainer;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attack")
	TSubclassOf<ARAProjectile> PrimaryProjectileClass = nullptr;	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MovementMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* CombatMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ActivatePrimaryAbilityAction;
	
	FTimerHandle AttackTimer;
	
	bool bIsAttacking = false;
	float AttackRate = 0.33f;
	
};
