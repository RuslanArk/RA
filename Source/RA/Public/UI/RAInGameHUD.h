// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RAInGameHUD.generated.h"

class URAAttributesWidget;

UCLASS()
class RA_API ARAInGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	void Init();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<URAAttributesWidget> AttributesWidgetClass = nullptr;

private:
	UPROPERTY()
	TObjectPtr<URAAttributesWidget> AttributesWidget = nullptr;
};
