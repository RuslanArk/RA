// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void BeginPlay();

private:
	void InitAbilitySystemComponent();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Primary Attack")
	TSubclassOf<ARAProjectile> PrimaryProjectileClass = nullptr;
	
private:	
	
	FTimerHandle AttackTimer;
	
	bool bIsAttacking = false;
	float AttackRate = 0.33f;
	
};
