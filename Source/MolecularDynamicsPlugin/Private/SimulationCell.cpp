// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulationCell.h"

#include <string>

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

void ASimulationCell::InitCollisionWalls()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulationCell::InitCollisionWalls() Called."));
	for(int32 i = 0; i < 6; i++)
	{
		UBoxComponent* NewCollisionWall = NewObject<UBoxComponent>(this);
		FString Name = TEXT("CollisionWall_");
		Name += FString::FromInt(i);
		//UBoxComponent* NewCollisionWall = CreateDefaultSubobject<UBoxComponent>(*Name);
		NewCollisionWall->SetupAttachment(SimulationCellIndicator);
		//NewCollisionWall->AttachToComponent(SimulationCellIndicator, FAttachmentTransformRules::SnapToTargetIncludingScale);
		NewCollisionWall->RegisterComponent();
		this->AddInstanceComponent(NewCollisionWall);
		NewCollisionWall->BodyInstance.SetCollisionProfileName(TEXT("Wall"));
		NewCollisionWall->BodyInstance.LinearDamping = 0.f;
		NewCollisionWall->BodyInstance.AngularDamping = 0.f;
		NewCollisionWall->SetHiddenInGame(true);
		
		CollisionWalls.Add(NewCollisionWall);
	}
}

void ASimulationCell::InitResetWalls()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulationCell::InitResetWalls() Called."));
	for (int32 i = 0; i < 6; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		AResetWall* NewResetWall = GetWorld()->SpawnActor<AResetWall>(GetActorLocation(), GetActorRotation(), SpawnInfo);
		NewResetWall->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		NewResetWall->SetActorHiddenInGame(true);

		ResetWalls.Add(NewResetWall);
	}
}

void ASimulationCell::InitTeleportWalls()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulationCell::InitTeleportWalls() Called."));
	for (int32 i = 0; i < 6; i++)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		ATeleportWall* NewTeleportWall = GetWorld()->SpawnActor<ATeleportWall>(GetActorLocation(), GetActorRotation(), SpawnInfo);
		NewTeleportWall->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		NewTeleportWall->SetActorHiddenInGame(true);

		TeleportWalls.Add(NewTeleportWall);
	}
}

void ASimulationCell::InitSimulationCell(float CellWidth, bool bTeleportWalls, USimulationData* Simulation)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulationCell::InitVolume(%f) Called."), CellWidth);

	SimulationData = Simulation;

	if (bTeleportWalls)
		InitTeleportWalls();
	else
		InitCollisionWalls();

	InitResetWalls();
	
	SetWidth(CellWidth);
}

void ASimulationCell::SetCollisionWallsWidth(float EdgeDistance, float WallDistance)
{
	if(CollisionWalls.Num() > 0)
	{
		//ZPos Wall (+z)
		CollisionWalls[0]->SetBoxExtent(FVector(EdgeDistance + (2 * WallThickness), EdgeDistance + 2 * WallThickness, WallThickness));
		CollisionWalls[0]->SetRelativeLocation(FVector(0.f, 0.f, WallDistance));
		//ZNeg Wall (-Z)
		CollisionWalls[1]->SetBoxExtent(FVector(EdgeDistance + 2 * WallThickness, EdgeDistance + 2 * WallThickness, WallThickness));
		CollisionWalls[1]->SetRelativeLocation(FVector(0.f, 0.f, -1.f * WallDistance));
		//XPos Wall (+x)
		CollisionWalls[2]->SetBoxExtent(FVector(WallThickness, EdgeDistance + 2 * WallThickness, EdgeDistance + 2 * WallThickness));
		CollisionWalls[2]->SetRelativeLocation(FVector(WallDistance, 0.f, 0.f));
		//XNeg Wall (-x)
		CollisionWalls[3]->SetBoxExtent(FVector(WallThickness, EdgeDistance + 2 * WallThickness, EdgeDistance + 2 * WallThickness));
		CollisionWalls[3]->SetRelativeLocation(FVector(-1.f * WallDistance, 0.f, 0.f));
		//YPos Wall(+Y)
		CollisionWalls[4]->SetBoxExtent(FVector(EdgeDistance + 2 * WallThickness, WallThickness, EdgeDistance + 2 * WallThickness));
		CollisionWalls[4]->SetRelativeLocation(FVector(0.f, WallDistance,0.f));
		//YNeg Wall (-Y)
		CollisionWalls[5]->SetBoxExtent(FVector(EdgeDistance + 2 * WallThickness, WallThickness, EdgeDistance + 2 * WallThickness));
		CollisionWalls[5]->SetRelativeLocation(FVector(0.f, -1.f * WallDistance, 0.f));
	}
}

void ASimulationCell::SetResetWallsWidth(float EdgeDistance, float WallDistance)
{
	//Increase the distance by an double the WallThickness
	float ModifiedWallThickness = WallThickness * 10;
	EdgeDistance = EdgeDistance + 3 * ModifiedWallThickness;
	WallDistance = WallDistance + 2 * ModifiedWallThickness;
	
	if (ResetWalls.Num() > 0)
	{
		//ZPos Wall (+z)
		ResetWalls[0]->SetBoxExtent(FVector(EdgeDistance, EdgeDistance, ModifiedWallThickness));
		ResetWalls[0]->SetActorRelativeLocation(FVector(0.f, 0.f, WallDistance));
		//ZNeg Wall (-Z)
		ResetWalls[1]->SetBoxExtent(FVector(EdgeDistance, EdgeDistance, ModifiedWallThickness));
		ResetWalls[1]->SetActorRelativeLocation(FVector(0.f, 0.f, -1.f * WallDistance));
		//XPos Wall (+x)
		ResetWalls[2]->SetBoxExtent(FVector(ModifiedWallThickness, EdgeDistance, EdgeDistance));
		ResetWalls[2]->SetActorRelativeLocation(FVector(WallDistance, 0.f, 0.f));
		//XNeg Wall (-x)
		ResetWalls[3]->SetBoxExtent(FVector(ModifiedWallThickness, EdgeDistance, EdgeDistance));
		ResetWalls[3]->SetActorRelativeLocation(FVector(-1.f * WallDistance, 0.f, 0.f));
		//YPos Wall(+Y)
		ResetWalls[4]->SetBoxExtent(FVector(EdgeDistance, ModifiedWallThickness, EdgeDistance));
		ResetWalls[4]->SetActorRelativeLocation(FVector(0.f, WallDistance, 0.f));
		//YNeg Wall (-Y)
		ResetWalls[5]->SetBoxExtent(FVector(EdgeDistance, ModifiedWallThickness, EdgeDistance));
		ResetWalls[5]->SetActorRelativeLocation(FVector(0.f, -1.f * WallDistance, 0.f));
	}
}

void ASimulationCell::SetTeleportWallsWidth(float EdgeDistance, float WallDistance)
{
	if (TeleportWalls.Num() > 0)
	{
		//ZPos Wall (+z)
		TeleportWalls[0]->SetBoxExtent(FVector(EdgeDistance + (2 * WallThickness), EdgeDistance + 2 * WallThickness, WallThickness));
		TeleportWalls[0]->SetActorRelativeLocation(FVector(0.f, 0.f, WallDistance));
		TeleportWalls[0]->InitTeleporter(TeleportWalls[1], EAxis::Z);
		//ZNeg Wall (-Z)
		TeleportWalls[1]->SetBoxExtent(FVector(EdgeDistance + 2 * WallThickness, EdgeDistance + 2 * WallThickness, WallThickness));
		TeleportWalls[1]->SetActorRelativeLocation(FVector(0.f, 0.f, -1.f * WallDistance));
		TeleportWalls[1]->InitTeleporter(TeleportWalls[0], EAxis::Z);
		//XPos Wall (+x)
		TeleportWalls[2]->SetBoxExtent(FVector(WallThickness, EdgeDistance + 2 * WallThickness, EdgeDistance + 2 * WallThickness));
		TeleportWalls[2]->SetActorRelativeLocation(FVector(WallDistance, 0.f, 0.f));
		TeleportWalls[2]->InitTeleporter(TeleportWalls[3], EAxis::X);
		//XNeg Wall (-x)
		TeleportWalls[3]->SetBoxExtent(FVector(WallThickness, EdgeDistance + 2 * WallThickness, EdgeDistance + 2 * WallThickness));
		TeleportWalls[3]->SetActorRelativeLocation(FVector(-1.f * WallDistance, 0.f, 0.f));
		TeleportWalls[3]->InitTeleporter(TeleportWalls[2], EAxis::X);
		//YPos Wall(+Y)
		TeleportWalls[4]->SetBoxExtent(FVector(EdgeDistance + 2 * WallThickness, WallThickness, EdgeDistance + 2 * WallThickness));
		TeleportWalls[4]->SetActorRelativeLocation(FVector(0.f, WallDistance, 0.f));
		TeleportWalls[4]->InitTeleporter(TeleportWalls[5], EAxis::Y);
		//YNeg Wall (-Y)
		TeleportWalls[5]->SetBoxExtent(FVector(EdgeDistance + 2 * WallThickness, WallThickness, EdgeDistance + 2 * WallThickness));
		TeleportWalls[5]->SetActorRelativeLocation(FVector(0.f, -1.f * WallDistance, 0.f));
		TeleportWalls[5]->InitTeleporter(TeleportWalls[4], EAxis::Y);
	}
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
	SimulationData->SetCellWidth(CellWidth);
	UE_LOG(LogTemp, Warning, TEXT("ASimulationCell::SetWidth(%f) Setting SimulationData->SimulationCellWidth:%f"), CellWidth, SimulationData->GetCellWidth());
	float EdgeDistance = CellWidth / 2.f;
	float WallDistance = EdgeDistance + (WallThickness);
	SimulationCellIndicator->SetBoxExtent(FVector(EdgeDistance));
	if(CollisionWalls.Num() > 0)
		SetCollisionWallsWidth(EdgeDistance, WallDistance);
	if (TeleportWalls.Num() > 0)
		SetTeleportWallsWidth(EdgeDistance, WallDistance);
	SetResetWallsWidth(EdgeDistance, WallDistance);
}

void ASimulationCell::SetVolume(float Volume)
{
	SetWidth(FMath::Pow(Volume, (1.0f / 3.0f)));
}

