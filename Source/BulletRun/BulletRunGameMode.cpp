// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BulletRunGameMode.h"
#include "BulletRunCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABulletRunGameMode::ABulletRunGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ABulletRunGameMode::SpawnTile()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawned"))
}
