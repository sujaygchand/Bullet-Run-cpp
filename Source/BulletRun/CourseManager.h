// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CourseManager.generated.h"

class AMasterTile;

UCLASS()
class BULLETRUN_API ACourseManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACourseManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Spawns Tiles
	 void SpawnTile();
	
	// Stores the course manager
	UPROPERTY( BlueprintReadWrite, Category = "Defaults")
		FVector NewLocation;
	
	/** Tiles class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Tiles")
		TSubclassOf<AMasterTile> TileClass;

	bool bCanSpawnObstacle = false;
};
