// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterTile.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UArrowComponent;
class UBoxComponent;
class ACourseManager;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BULLETRUN_API AMasterTile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMasterTile();

	// Stores the course manager
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Defaults")
		ACourseManager* CourseManager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Default Scene Component
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USceneComponent* Root;

	// Title Mesh
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* TileMesh;

	//Attach Point
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UArrowComponent* AttachPoint;

	//Spawn trigger box
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UBoxComponent* SpawnBox;

	// Lane Arrows
	UPROPERTY(VisibleAnywhere, Category = "Components")
		UArrowComponent* LeftLane;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UArrowComponent* CenterLane;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UArrowComponent* RightLane;


	// On Overlap implementation
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Bool to check if box collision has been overlapped
	bool bHasOverLapped = false;

	// Checks if a box obstacle has been spawned
	bool bSpawnedBox = false;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// gets a reference to the attach location
	FVector GetAttachPointLocation();

	// Returns Lane Arrow Location
	FVector LaneArrowLocation(UArrowComponent* LaneArrow);

	/** Spawns lows obstacles */ 
	void SpawnObstacles();

	/** Spawns obstacles */
	void SpawnObstacles(TSubclassOf<AActor> Class, FVector SpawnLocation, FQuat SpawnRotation, FVector SpawnScale);

	/** Low obstacle class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Obstacles")
	TSubclassOf<AActor> LowObstacle;

	/** Box obstacle class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Obstacles")
		TSubclassOf<AActor> BoxObstacle;

};
