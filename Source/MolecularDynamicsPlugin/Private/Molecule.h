// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Atom.h"
#include "AtomData.h"
#include "Bond.h"
#include "MoleculePrototype.h"
#include "AtomPrototype.h"
#include "Engine/DataTable.h"
#include "Components/SphereComponent.h"
#include "Molecule.generated.h"

UCLASS()
class AMolecule : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMolecule();


	//void InitAtoms();

	void InitMolecule(FMoleculePrototype& Prototype, int32 Index, UDataTable* AtomDataTable);
	
	/**
	 * Initialize a prototype molecule.  Calculates total mass and dipole moment.  Position etc are set to zero.
	 * @param NewName - Name of the molecule ("water" etc).
	 * @param NewMolecularFormula - Chemical formula for the molecule.
	 * @param NewAtoms - Atoms to put into the molecule.  Atom positions are relative to molecule's origin.
	 * @param NewBonds - List of bonds between atoms.
	 * @param NewDipoleMoment - Overall dipole moment of the molecule.
	 */
	//void InitMoleculePrototype(
	//	FString NewName,
	//	FString NewMolecularFormula,
	//	TArray<AAtom*> NewAtoms,
	//	TArray<ABond*> NewBonds,
	//	FVector NewDipoleMoment
	//);

	/**
	 * Copy molecule properties from the Source molecule, including position etc.  Creates new AAtom and ABond objects as copies of those in the prototype.
	 * @param Source - Molecule object to copy properties from.
	 */
	//void InitMoleculeExactCopy(AMolecule* Source);

	/**
	 * Copy molecule properties from the Source molecule.  Creates new AAtom and ABond objects as copies of those in the prototype.
	 * @param Source - Molecule object to copy properties from.
	 * @param NewPosition - Initial position of this molecule's origin.
	 * @param NewVelocity - Initial velocity.
	 * @param NewOrientation - Initial orientation.
	 * @param NewAngularVelocity - Initial rotational speed.
	 */
	//void InitMoleculeCopy(
	//	AMolecule* Source,
	//	FVector NewPosition,
	//	FVector NewVelocity,
	//	FVector NewOrientation,
	//	FVector NewAngularVelocity
	//);


	/** The name of this molecule ("water" etc.). */
	UFUNCTION()
		FString GetMoleculeName();

	/** Chemical formula for the molecule. */
	UFUNCTION()
		FString GetMoleculeFormula();

	/** Sum of all the atom masses in the molecule. */
	UFUNCTION()
		float GetTotalMass();

	/** Dipole moment of the molecule, in appropriate units. */
	UFUNCTION()
		FVector GetDipoleMoment();

	UFUNCTION()
		int32 GetNumAtoms();

	/** @return location of the molecule. */
	//UFUNCTION()
		//FVector GetPosition();

	//UFUNCTION()
	//FVector GetVelocity();
	
	//UFUNCTION()
	//	FString PrintAtom(int32 AtomIndex);

//	UFUNCTION()
//		FVector GetOrientation();

	UFUNCTION()
		FVector GetAngularVelocity();

	/**
	 * Record the list of molecules that are within this molecule's interaction radius.
	 * ASimulation will make a list like this for each molecule, then use it when calculating the forces on the molecule.
	 * (NOTE: Check how Unreal handles many-body forces like this; it might have
	 * a preferred way to handle them.)
	 * */
	UFUNCTION()
		void SetInteractingMolecules(TArray<AMolecule*> MoleculeList);

	UFUNCTION()
		TArray<AMolecule*> GetInteractingMolecules();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	/** Marker showing the location of the center of mass. */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
		USphereComponent* CenterOfMassIndicator;

	/** Is this a "prototype" molecule?  (If so, don't draw or interact.) */
	//UPROPERTY(VisibleAnywhere, Category = "Simulation")
	//	bool IsPrototype;

	/**
	 * Name of the molecule ("water" etc).
	 */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
		FString MoleculeName;

	/** Chemical formula for the molecule. */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
		FString MoleculeFormula;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
		int32 MoleculeIndex;

	/** List of atoms in this molecule.  Atom positions are relative to molecule's origin. */
	UPROPERTY(VisibleAnywhere, Category="Simulation")
		TArray<AAtom*> Atoms;

	/** List of bonds between atoms. */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
		TArray<ABond*> Bonds;

	/** Sum of all the atom masses in the molecule. */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
		float TotalMass;

	/** Dipole moment of the molecule, in appropriate units. */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
		FVector DipoleMoment;

	/** List of molecules within this molecule's interaction radius. */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
		TArray<AMolecule*> InteractingMolecules;

	//UPROPERTY(VisibleAnywhere, Category = "Simulation")
		//FVector Position;

//	UPROPERTY(VisibleAnywhere, Category = "Simulation")
//		FVector Orientation;

	//UPROPERTY(VisibleAnywhere, Category = "Simulation")
		//FVector Velocity;

	/** Rate of rotation of the molecule. */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
		FVector AngularVelocity;

	/** Net force on the molecule (calculated by Simulation). */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
		FVector NetForce;

	/** Net torque on the molecule (calculated by Simulation). */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
		FVector NetTorque;  // TK Maybe?  Check how Unreal does rotations.
};
