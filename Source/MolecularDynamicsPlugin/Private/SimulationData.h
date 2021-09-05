#pragma once

/*
Data about a specific reaction and its products.
*/

#include "UObject/Class.h"
//#include "GameFramework/Actor.h"
#include "AtomData.h"
#include "LookupTable.h"
#include "Engine/DataAsset.h"
#include "SimulationData.generated.h"

/*
USTRUCT(BlueprintType)
struct FSimulationData
{
	GENERATED_BODY()

	// Pointer to the Object controlling and containing the simulation
	AActor* Simulation;

	UPROPERTY()
	UDataTable* AtomDataTable;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	float SimulationCellWidth;
};
*/

UCLASS()
class USimulationData : public UDataAsset
{
	GENERATED_BODY()

public:
	USimulationData();

	UFUNCTION()
	UDataTable* GetAtomData();

	UFUNCTION()
	ULookupTable* GetInteractionForceTable();

	UFUNCTION()
	float GetCellWidth();

	UFUNCTION()
	float GetInitialTemperature();
	
	UFUNCTION()
	AActor* GetSimulation();

	UFUNCTION()
	float GetSimulationSpeed();
	
	UFUNCTION()
	void SetAtomData(UDataTable* AtomData);

	UFUNCTION()
	void SetInteractionForceTable(ULookupTable* ForceTable);

	UFUNCTION()
	void SetCellWidth(float Width);

	UFUNCTION()
	void SetInitialTemperature(float Temperature);
	
	UFUNCTION()
	void SetSimulation(AActor* SimulationPointer);

	UFUNCTION()
	void SetSimulationSpeed(float Speed);

private:
	UPROPERTY()
	float InitialTemperature;
	
	AActor* Simulation;
	
	UPROPERTY()
	float SimulationCellWidth;

	UPROPERTY()
	float SimulationSpeed;

	UPROPERTY()
	UDataTable* AtomDataTable;

	/** Lookup table for interaction forces. */
	ULookupTable* InteractionForceTable;
};
