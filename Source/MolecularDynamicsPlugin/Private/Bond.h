// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Atom.h"
#include "BondType.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

#include "Bond.generated.h"


//UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
//class UBond : public USceneComponent

UCLASS()
class UBond : public USplineComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBond();

	void InitBond(UAtom* AtomAIn, UAtom* AtomBIn, EBondType& BondTypeIn);

	void InitBondRep();

	void InitBondType();

	void InitSpline();

	void SetHideSpline();

	void SetShowSpline();

	void SetRenderBallStick();

	void SetRenderHidden();

	void SetRenderLinear();

	void SetRenderSpaceFilling();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	UAtom* AtomA;
	//FVector StartPosition;

	UPROPERTY()
	UAtom* AtomB;
	//FVector EndPosition;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	UStaticMesh* BondMesh;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	UPhysicsConstraintComponent* BondPhysicsConstraint;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	EBondType BondType;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	FColor Color;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	FColor ColorA; 

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	FColor ColorB;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	UMaterialInterface* MaterialBase;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	UMaterialInstanceDynamic* MaterialDynamic;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	USplineMeshComponent* SplineMeshComponent;
	
};
