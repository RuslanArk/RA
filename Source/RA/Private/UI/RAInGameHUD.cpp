// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RAInGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "UI/InGameUI/RAAttributewWidget.h"


void ARAInGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (AttributesWidgetClass)
	{
		Init();
	}
}

void ARAInGameHUD::Init()
{
	AttributesWidget = CreateWidget<URAAttributesWidget>(GetOwningPlayerController(), AttributesWidgetClass);
	AttributesWidget->BindToAttributes();
	AttributesWidget->AddToViewport();
	AttributesWidget->HealthBar->SetPercent(1.f);
	AttributesWidget->StaminaBar->SetPercent(1.f);
}
