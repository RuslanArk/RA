// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RAAttributewWidget.generated.h"

class UProgressBar;

UCLASS()
class RA_API URAAttributesWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindToAttributes();

	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthBar = nullptr;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* StaminaBar = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly)
	float HealthPercent;
	
	UPROPERTY(BlueprintReadOnly)
	float StaminaPercent;
};
