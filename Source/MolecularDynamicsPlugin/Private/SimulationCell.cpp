// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulationCell.h"

// Sets default values
ASimulationCell::ASimulationCell()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("ASimulationCell::ASimulationCell() Called."));

	SimulationVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SimulationVolume"));
	SetRootComponent(SimulationVolume);
	SimulationVolume->SetHiddenInGame(false);
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
	FVector BoxExtent = SimulationVolume->GetUnscaledBoxExtent();
	return (BoxExtent.X * 2.f) * (BoxExtent.Y * 2.f) * (BoxExtent.Z * 2.f);
}

float ASimulationCell::GetWidth()
{
	return SimulationVolume->GetUnscaledBoxExtent().X * 2.f;
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
	SimulationVolume->ShapeColor = CellColor;
}

void ASimulationCell::SetWidth(float CellWidth)
{
	SimulationVolume->SetBoxExtent(FVector(CellWidth / 2.f));
}

void ASimulationCell::SetVolume(float Volume)
{
	SetWidth(FMath::Pow(Volume, (1.0f / 3.0f)));
}

