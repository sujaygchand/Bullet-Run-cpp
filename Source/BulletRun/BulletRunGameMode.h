// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BulletRunGameMode.generated.h"

UCLASS(minimalapi)
class ABulletRunGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABulletRunGameMode();

	/** Spawns tile */
	void SpawnTile();
};



