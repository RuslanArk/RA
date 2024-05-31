// Copyright Epic Games, Inc. All Rights Reserved.

#include "RAGameMode.h"
#include "RACharacter.h"
#include "UObject/ConstructorHelpers.h"

ARAGameMode::ARAGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
