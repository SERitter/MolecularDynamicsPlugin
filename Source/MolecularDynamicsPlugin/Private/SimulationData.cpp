// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulationData.h"


USimulationData::USimulationData()
{
	Simulation = NULL;
	AtomDataTable = NULL;
	SimulationCellWidth = 0.0f;
	SimulationSpeed = 1.0f;
}

UDataTable* USimulationData::GetAtomData()
{
	return AtomDataTable;
}

ULookupTable* USimulationData::GetInteractionForceTable()
{
	return InteractionForceTable;
}

float USimulationData::GetCellWidth()
{
	return SimulationCellWidth;
}

float USimulationData::GetInitialTemperature()
{
	return InitialTemperature;
}

AActor* USimulationData::GetSimulation()
{
	return Simulation;
}

float USimulationData::GetSimulationSpeed()
{
	return SimulationSpeed;
}

void USimulationData::SetAtomData(UDataTable* AtomData)
{
	AtomDataTable = AtomData;
}

void USimulationData::SetInteractionForceTable(ULookupTable* ForceTable)
{
	InteractionForceTable = ForceTable;
}

void USimulationData::SetCellWidth(float Width)
{
	SimulationCellWidth = Width;
}

void USimulationData::SetInitialTemperature(float Temperature)
{
	InitialTemperature = Temperature;
}

void USimulationData::SetSimulation(AActor* SimulationPointer)
{
	Simulation = SimulationPointer;
}

void USimulationData::SetSimulationSpeed(float Speed)
{
	SimulationSpeed = Speed;
}
