// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AtomData.h"
#include "Atom.generated.h"

/**
 * 
 */
UCLASS()
//class UAtom : public UPrimitiveComponent
class UAtom : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UAtom();
	
	//Loads AtomData into the Atom 
	void InitAtom(FAtomData* AtomData, FString AtomSymbol, int32 Index);

	void SetRenderBallStick();

	void SetRenderSpaceFilling();

private:
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	int32 AtomArrayIndex;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	FString AtomName;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	int32 AtomicNumber;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	FColor Color;

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
	
	
};
