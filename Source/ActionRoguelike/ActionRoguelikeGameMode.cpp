// Copyright Epic Games, Inc. All Rights Reserved.

#include "ActionRoguelikeGameMode.h"
#include "ActionRoguelikeCharacter.h"
#include "UObject/ConstructorHelpers.h"

AActionRoguelikeGameMode::AActionRoguelikeGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
