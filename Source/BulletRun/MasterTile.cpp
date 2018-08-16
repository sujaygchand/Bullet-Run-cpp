// Fill out your copyright notice in the Description page of Project Settings.

#include "MasterTile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Runtime/Core/Public/Misc/OutputDeviceNull.h"
#include "Engine/World.h"

#include "BulletRunCharacter.h"
#include "BulletRunGameMode.h"
#include "CourseManager.h"


// Sets default values
AMasterTile::AMasterTile()
{

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Root Setup
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	// Tile Mesh setup
	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TitleMesh"));
	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Game/Meshes/SM_BaseTile.SM_BaseTile"));

	if (MeshAsset.Succeeded()) {
		TileMesh->SetStaticMesh(MeshAsset.Object);
		TileMesh->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
		TileMesh->SetRelativeScale3D(FVector(10.0f, 10.0f, 0.1f));
	}
	else {
	}

	TileMesh->SetupAttachment(Root);

	// Attach point aet up
	AttachPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("AttachPoint"));
	AttachPoint->SetRelativeLocation(FVector(500.0f, 0.0f, 0.0f));
	AttachPoint->SetupAttachment(Root);

	// Left Lane set up
	LeftLane = CreateDefaultSubobject<UArrowComponent>(TEXT("LeftLane"));
	LeftLane->SetRelativeLocation(FVector(0.0f, -330.0f, 0.0f));
	LeftLane->SetupAttachment(Root);

	// Center set up
	CenterLane = CreateDefaultSubobject<UArrowComponent>(TEXT("CenterLane"));
	CenterLane->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	CenterLane->SetupAttachment(Root);

	// Right Lane set up
	RightLane = CreateDefaultSubobject<UArrowComponent>(TEXT("RightLane"));
	RightLane->SetRelativeLocation(FVector(0.0f, 320.0f, 0.0f));
	RightLane->SetupAttachment(Root);

	// Box trigger spawn
	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SpawnBox->SetRelativeLocation(FVector(0.0f, -48.0f, 4100.0f));
	SpawnBox->SetRelativeScale3D(FVector(2, 0.5, 150));
	SpawnBox->SetupAttachment(TileMesh);

	SpawnBox->OnComponentBeginOverlap.AddDynamic(this, &AMasterTile::OnBeginOverlap);
}

// Called when the game starts or when spawned
void AMasterTile::BeginPlay()
{
	Super::BeginPlay();

	// Checks if obstable can be spawned
	if (CourseManager->bCanSpawnObstacle) {
		SpawnObstacles();
	}
}

// Called every frame
void AMasterTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
 * Returns the attach arrow component's location
 *
 * @return AttachPoint location
 */
FVector AMasterTile::GetAttachPointLocation()
{
	return AttachPoint->GetComponentLocation();
}

/**
 * Return a lane arrow location
 *
 * @return Lane Arrow Location
 */
FVector AMasterTile::LaneArrowLocation(UArrowComponent* LaneArrow)
{
	return LaneArrow->GetComponentLocation();
}

/**
 * Determines if obstacles are spawned and where
 */
void AMasterTile::SpawnObstacles()
{

	int LeftLaneRan = FMath::RandRange(0, 3);
	int CenterLaneRan = FMath::RandRange(0, 3);
	int RightLaneRan = FMath::RandRange(0, 3);
	
	switch (LeftLaneRan) {
	case 0:
		SpawnObstacles(LowObstacle, LaneArrowLocation(LeftLane), FQuat(0, 0, 90, 0), FVector(2));
	break;
	case 1:
		SpawnObstacles(BoxObstacle, LaneArrowLocation(LeftLane), FQuat(0, 0, 270, 0), FVector(1.7));
		break;
	case 2:
		break;
	case 3:
		break;
	}

	switch (CenterLaneRan) {
	case 0:
		SpawnObstacles(LowObstacle, LaneArrowLocation(CenterLane), FQuat(0, 0, 90, 0), FVector(2));
		break;
	case 1:
		SpawnObstacles(BoxObstacle, LaneArrowLocation(CenterLane), FQuat(0, 0, 270, 0), FVector(1.7));
		break;
	case 2:
		break;
	case 3:
		break;
	}

	switch (RightLaneRan) {
	case 0:
		SpawnObstacles(LowObstacle, LaneArrowLocation(RightLane), FQuat(0, 0, 90, 0), FVector(2));
		break;
	case 1:
		SpawnObstacles(BoxObstacle, LaneArrowLocation(RightLane), FQuat(0, 0, 270, 0), FVector(1.7));
		break;
	case 2:
		break;
	case 3:
		break;
	}

}

/**
 * Spawns the obstacle with the relevent tranform data
 */
void AMasterTile::SpawnObstacles(TSubclassOf<AActor> Class, FVector SpawnLocation, FQuat SpawnRotation, FVector SpawnScale)
{
	if (bSpawnedBox) {
		return;
	}

	if (Class == BoxObstacle) {
		bSpawnedBox = true;
	}

	UE_LOG(LogTemp, Warning, TEXT("Spawned"))

	FTransform SpawnTransfrom{
		SpawnRotation,
		SpawnLocation,
		SpawnScale
	};

	FActorSpawnParameters ActorSpawnParams;

	// Spawns the mesh
	GetWorld()->SpawnActor<AActor>(Class, SpawnTransfrom, ActorSpawnParams);

}

/**
 * On Box collision overlap
 */
void AMasterTile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
		ABulletRunCharacter* PlayerCharacter = Cast<ABulletRunCharacter>(OtherActor);
		

	if (PlayerCharacter && ! bHasOverLapped) {
		bHasOverLapped = true;

			CourseManager->SpawnTile();

		// The destory object is handled in BP
		FOutputDeviceNull ar;
		this->CallFunctionByNameWithArguments(TEXT("DestroyTile"), ar, NULL, true);
	}
	
}