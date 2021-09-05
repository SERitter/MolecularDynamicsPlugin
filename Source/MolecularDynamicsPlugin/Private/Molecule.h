// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Atom.h"
#include "AtomData.h"
#include "Bond.h"
#include "MoleculePrototype.h"
#include "AtomPrototype.h"
#include "SimulationData.h"
#include "Engine/DataTable.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

#include "Molecule.generated.h"

UCLASS()
class AMolecule : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMolecule();

	void InitMolecule(FMoleculePrototype& Prototype, int32 Index, USimulationData* Simulation);

	UFUNCTION()
	void AddImpulse(FVector ImpulseVector);

	UFUNCTION()
	void AddTorque(FVector TorqueVector);
	
	UFUNCTION()
	void EnablePhysics();

	UFUNCTION()
	void Freeze();

	UFUNCTION()
	FVector GetCurrentVelocity();

	UFUNCTION()
	FVector GetInitialPosition();
	
	//UFUNCTION()
	//float GetInitialTemperature();

	UFUNCTION()
	FVector GetInitialTorque();
	
	UFUNCTION()
	FVector GetInitialVelocity();

	/** Chemical formula for the molecule. */
	UFUNCTION()
	FString GetMoleculeFormula();

	/** Sum of all the atom masses in the molecule. */
	UFUNCTION()
	float GetMoleculeMass();

	/** The name of this molecule ("water" etc.). */
	UFUNCTION()
	FString GetMoleculeName();
	
	UFUNCTION()
	int32 GetNumAtoms();

	UFUNCTION()
	float GetSpeed();

	//UFUNCTION()
	//FVector GetCurrentTorque();

	UFUNCTION()
	void ResetMolecule();

	UFUNCTION()
	void SetAngularVelocity(FVector NewAngularVelocity);

	UFUNCTION()
	void SetInitialPosition(FVector Position);

	UFUNCTION()
	void SetInitialVelocity(FVector NewVelocity);
	
	//UFUNCTION()
	//void SetInitialTemperature(float InitialTemperature);
	
	UFUNCTION()
	void SetHideCollisionSpheres();

	UFUNCTION()
	void SetHideCoM();

	UFUNCTION()
	void SetHideInteractionSpheres();

	UFUNCTION()
	void SetHideSpline();
	
	UFUNCTION()
	void SetShowCollisionSpheres();

	UFUNCTION()
	void SetShowInteractionSpheres();

	UFUNCTION()
	void SetShowCoM();

	UFUNCTION()
	void SetShowSpline();

	UFUNCTION()
	void SetRenderBallStick();

	UFUNCTION()
	void SetRenderHidden();

	UFUNCTION()
	void SetRenderLinear();
	
	UFUNCTION()
	void SetRenderSpaceFilling();
	
	UFUNCTION()
	void SetVelocity(FVector NewVelocity);

	UFUNCTION()
	void UpdateIntermolecularForces();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/** List of atoms in this molecule.  Atom positions are relative to molecule's origin. */
	UPROPERTY(VisibleAnywhere, Category="Simulation")
	TArray<UAtom*> Atoms;
	
	/** List of bonds between atoms. */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	TArray<UBond*> Bonds;

	/** List of bonds between atoms. */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	TArray<USphereComponent*> CollisionSpheres;

	UPROPERTY(EditAnywhere, Category = "Simulation")
	FVector InitialPosition;

	//UPROPERTY(VisibleAnywhere, Category = "Simulation")
	//float InitialTemp;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	FVector InitialTorque;
	
	UPROPERTY(EditAnywhere, Category = "Simulation")
	FVector InitialVelocity;
	
	/** Marker showing the location of the center of mass. */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	USphereComponent* MoleculeCoMIndicator;

	/** Chemical formula for the molecule. */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	FString MoleculeFormula;
	
	/** Index of the Molecule in the simulation Molecules TArray */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	int32 MoleculeIndex;
	
	/** Name of the molecule ("water" etc). */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	FString MoleculeName;

	/** Sum of all the atom masses in the molecule. */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	float MoleculeMass;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	UProjectileMovementComponent* MoleculeMovementComponent;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	URotatingMovementComponent* MoleculeRotationComponent;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	USimulationData* SimulationData;
	//ASimulationCell* SimulationCell;
	//AActor* Simulation;
};
