// Copyright Epic Games, Inc. All Rights Reserved.

#include "ReclaimersGameMode.h"
#include "ReclaimersCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "ReclaimersCharacter.h"
#include "DinosaurCharacters/Carnivores/Tyrannosaurus/Tyrannosaurus_Character.h"

AReclaimersGameMode::AReclaimersGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Carnivores/Tyrannosaurus/Blueprints/BP_TyrannosaurusCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
