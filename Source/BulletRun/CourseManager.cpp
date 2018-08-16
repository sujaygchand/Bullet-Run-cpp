// Fill out your copyright notice in the Description page of Project Settings.

#include "CourseManager.h"
#include "MasterTile.h"
#include "Engine/World.h"

// Sets default values
ACourseManager::ACourseManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACourseManager::BeginPlay()
{
	for (int32 i = 0; i < 9; i++)
	{
		SpawnTile();
	}

	bCanSpawnObstacle = true;
}

// Called every frame
void ACourseManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACourseManager::SpawnTile()
{

	FActorSpawnParameters ActorSpawnParams;
	
	// Spawns the mesh
	AMasterTile* NewTile = GetWorld()->SpawnActor<AMasterTile>(TileClass, NewLocation, FRotator(0,0,0), ActorSpawnParams);

	NewLocation = NewTile->GetAttachPointLocation();
}


