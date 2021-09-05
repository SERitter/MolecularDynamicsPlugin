// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ResetWall.h"
#include "TeleportWall.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/BodySetup.h"
#include "SimulationCell.generated.h"

UCLASS()
class ASimulationCell : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASimulationCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	float GetVolume();

	UFUNCTION()
	float GetWidth();

	void InitCollisionWalls();

	void InitResetWalls();

	void InitTeleportWalls();

	UFUNCTION()
	void InitSimulationCell(float CellWidth, bool bTeleportWalls, USimulationData* Simulation);

	//LineThickness is a protected member, we will have to add a different representation to adjust this value.
	//UFUNCTION()
	//void SetLineThickness(float LineThickness);

	UFUNCTION()
	void SetCollisionWallsWidth(float EdgeDistance, float WallDistance);

	UFUNCTION()
		void SetResetWallsWidth(float EdgeDistance, float WallDistance);

	UFUNCTION()
	void SetTeleportWallsWidth(float EdgeDistance, float WallDistance);
	
	UFUNCTION()
	void SetShapeColor(FColor LineColor);

	UFUNCTION()
	void SetWidth(float CellWidth);

	/**
	 * sets the dimensions based upon a desired volume
	 * @param Volume: The desired volume in Cubic Unreal Units. 1 UU = 1 pM
	 */
	UFUNCTION()
	void SetVolume(float Volume);

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Simulation")
	float WallThickness = 20.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Simulation")
	TArray<UBoxComponent*> CollisionWalls;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Simulation")
	TArray<AResetWall*> ResetWalls;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Simulation")
	UBoxComponent* SimulationCellIndicator;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Simulation")
	TArray<ATeleportWall*> TeleportWalls;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Simulation")
	USimulationData* SimulationData;
};
