// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulationCell.h"

// Sets default values
ASimulationCell::ASimulationCell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("ASimulationCell::ASimulationCell() Called."));

	SimulationCellIndicator = CreateDefaultSubobject<UBoxComponent>(TEXT("SimulationCell"));
	SetRootComponent(SimulationCellIndicator);
	SimulationCellIndicator->SetHiddenInGame(false);
	SimulationCellIndicator->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));

	bool bWallsHidden = true;
	//SimulationVolume->GetBodySetup()->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseSimpleAsComplex;
	//Collision Ceiling
	SimulationCellCeiling = CreateDefaultSubobject<UBoxComponent>(TEXT("SimulationCeiling"));
	SimulationCellCeiling->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
	SimulationCellCeiling->SetHiddenInGame(bWallsHidden);
	SimulationCellCeiling->AttachToComponent(SimulationCellIndicator, FAttachmentTransformRules::SnapToTargetIncludingScale);
	//CollisionFloor
	SimulationCellFloor = CreateDefaultSubobject<UBoxComponent>(TEXT("SimulationCellFloor"));
	SimulationCellFloor->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
	SimulationCellFloor->SetHiddenInGame(bWallsHidden);
	SimulationCellFloor->AttachToComponent(SimulationCellIndicator, FAttachmentTransformRules::SnapToTargetIncludingScale);
	//XPos Wall (+x)
	SimulationCellXPosWall = CreateDefaultSubobject<UBoxComponent>(TEXT("SimulationCellXPosWall"));
	SimulationCellXPosWall->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
	SimulationCellXPosWall->SetHiddenInGame(bWallsHidden);
	SimulationCellXPosWall->AttachToComponent(SimulationCellIndicator, FAttachmentTransformRules::SnapToTargetIncludingScale);
	//XNeg Wall (-x)
	SimulationCellXNegWall = CreateDefaultSubobject<UBoxComponent>(TEXT("SimulationCellXNegWall"));
	SimulationCellXNegWall->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
	SimulationCellXNegWall->SetHiddenInGame(bWallsHidden);
	SimulationCellXNegWall->AttachToComponent(SimulationCellIndicator, FAttachmentTransformRules::SnapToTargetIncludingScale);
	//YPos Wall(+Y)
	SimulationCellYPosWall = CreateDefaultSubobject<UBoxComponent>(TEXT("SimulationCellYPosWall"));
	SimulationCellYPosWall->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
	SimulationCellYPosWall->SetHiddenInGame(bWallsHidden);
	SimulationCellYPosWall->AttachToComponent(SimulationCellIndicator, FAttachmentTransformRules::SnapToTargetIncludingScale);
	//YNeg Wall (-Y)
	SimulationCellYNegWall = CreateDefaultSubobject<UBoxComponent>(TEXT("SimulationCellYNegWall"));
	SimulationCellYNegWall->BodyInstance.SetCollisionProfileName(TEXT("BlockAll"));
	SimulationCellYNegWall->SetHiddenInGame(bWallsHidden);
	SimulationCellYNegWall->AttachToComponent(SimulationCellIndicator, FAttachmentTransformRules::SnapToTargetIncludingScale);
	
}

// Called when the game starts or when spawned
void ASimulationCell::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASimulationCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ASimulationCell::GetVolume()
{
	FVector BoxExtent = SimulationCellIndicator->GetUnscaledBoxExtent();
	return (BoxExtent.X * 2.f) * (BoxExtent.Y * 2.f) * (BoxExtent.Z * 2.f);
}

float ASimulationCell::GetWidth()
{
	return SimulationCellIndicator->GetUnscaledBoxExtent().X * 2.f;
}

void ASimulationCell::InitVolume(float CellWidth)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulationCell::InitVolume(%f) Called."), CellWidth);
	SetWidth(CellWidth);
}

//void ASimulationCell::SetLineThickness(float LineThickness)
//{
//	SimulationVolume->LineThickness = LineThickness;
//}

void ASimulationCell::SetShapeColor(FColor CellColor)
{
	SimulationCellIndicator->ShapeColor = CellColor;
}

void ASimulationCell::SetWidth(float CellWidth)
{
	float EdgeDistance = CellWidth / 2.f;
	float WallDistance = EdgeDistance + (WallThickness / 2.f);
	SimulationCellIndicator->SetBoxExtent(FVector(EdgeDistance));
	
	//ceiling
	SimulationCellCeiling->SetBoxExtent(FVector(EdgeDistance + (2 * WallThickness), EdgeDistance + 2 * WallThickness, WallThickness));
	SimulationCellCeiling->SetRelativeLocation(FVector(0.f, 0.f, WallDistance));
	//floor
	SimulationCellFloor->SetBoxExtent(FVector(EdgeDistance + 2 * WallThickness, EdgeDistance + 2 * WallThickness, WallThickness));
	SimulationCellFloor->SetRelativeLocation(FVector(0.f, 0.f, -1.f * WallDistance));
	//XPos Wall (+x)
	SimulationCellXPosWall->SetBoxExtent(FVector(WallThickness, EdgeDistance + 2 * WallThickness, EdgeDistance + 2 * WallThickness));
	SimulationCellXPosWall->SetRelativeLocation(FVector(WallDistance, 0.f, 0.f));
	//XNeg Wall (-x)
	SimulationCellXNegWall->SetBoxExtent(FVector(WallThickness, EdgeDistance + 2 * WallThickness, EdgeDistance + 2 * WallThickness));
	SimulationCellXNegWall->SetRelativeLocation(FVector(-1.f * WallDistance, 0.f, 0.f));
	//YPos Wall(+Y)
	SimulationCellYPosWall->SetBoxExtent(FVector(EdgeDistance + 2 * WallThickness, WallThickness, EdgeDistance + 2 * WallThickness));
	SimulationCellYPosWall->SetRelativeLocation(FVector(0.f, WallDistance,0.f));
	//YNeg Wall (-Y)
	SimulationCellYNegWall->SetBoxExtent(FVector(EdgeDistance + 2 * WallThickness, WallThickness, EdgeDistance + 2 * WallThickness));
	SimulationCellYNegWall->SetRelativeLocation(FVector(0.f, -1.f * WallDistance, 0.f));
	
}

void ASimulationCell::SetVolume(float Volume)
{
	SetWidth(FMath::Pow(Volume, (1.0f / 3.0f)));
}

