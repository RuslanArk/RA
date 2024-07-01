// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RAInGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/InGameUI/RAAttributewWidget.h"

void ARAInGameHUD::Init()
{
	AttributesWidget = CreateWidget<URAAttributesWidget>(GetOwningPlayerController(), AttributesWidgetClass);
	AttributesWidget->BindToAttributes();
	AttributesWidget->AddToViewport();
}
