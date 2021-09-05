// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AtomData.h"
#include "InteractionSphere.h"
#include "SimulationData.h"
#include "Components/SphereComponent.h"

#include "Atom.generated.h"


/**
 * 
 */
UCLASS()
//class UAtom : public UPrimitiveComponent
//class UAtom : public UStaticMeshComponent
class UAtom : public USphereComponent
{
	GENERATED_BODY()

public:
	UAtom();

	UFUNCTION()
	FColor GetColor();

	UFUNCTION()
	FString GetSymbol();
	
	//Loads AtomData into the Atom
	void InitAtom(FAtomData* AtomData, FString AtomSymbol, int32 Index, USimulationData* Simulation);

	UFUNCTION()
	void SetHideCollisionSpheres();

	UFUNCTION()
	void SetHideInteractionSpheres();

	UFUNCTION()
	void SetShowCollisionSpheres();

	UFUNCTION()
	void SetShowInteractionSpheres();

	UFUNCTION()
	void SetRenderBallStick();

	UFUNCTION()
	void SetRenderHidden();

	UFUNCTION()
	void SetRenderLinear();

	UFUNCTION()
	void SetRenderSpaceFilling();

	UFUNCTION()
	void UpdateIntermolecularForces();

private:
	UStaticMesh* Asset;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	int32 AtomArrayIndex;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	FString AtomName;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	int32 AtomicNumber;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	UStaticMeshComponent* AtomRepresentation;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	FColor Color;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	AInteractionSphere* InteractionSphere;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	float Mass;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	UMaterialInterface* MaterialBase;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	UMaterialInstanceDynamic* MaterialDynamic;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	FString Symbol;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	float VDWRadius;

	//AActor* Simulation;
	USimulationData* SimulationData;
};
