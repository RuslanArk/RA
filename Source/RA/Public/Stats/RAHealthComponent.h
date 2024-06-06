// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RAHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RA_API URAHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URAHealthComponent();

	UFUNCTION(BlueprintCallable)
	void AddHealth(const int32 Quantity);

	FORCEINLINE float GetHealth() const { return Health; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnRep_Health();

protected:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_Health, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 Health = 200.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
	int32 MaxHealth = 200.f;
	
};
