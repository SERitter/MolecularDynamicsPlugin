// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/Material.h"
#include "Math/Color.h"
//#include "AtomOLD.h"
#include "Bond.generated.h"

UCLASS()
class ABond : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * Default constructor; all zeroes, no Tick().
	 */
	ABond();

	/**
	 * Construct a bond with the given properties, connected to the given atoms.
	 * Use this constructor if you're not making "prototype" bonds.
	 * @param Name - String to identify the bond.
	 * @param Type - Type of bond (hydrogen, single, double, etc.).
	 * @param EquilibriumLength - Bond length without oscillations etc., in Angstroms.
	 * @param SpringConstant - Measure of bond strength, in kcal/(mol*A^2).
	 * @param Color - What colour to use when drawing this bond.
	 * @param AtomA - The first atom to connect to.
	 * @param AtomB - The second atom to connect to.
	UFUNCTION()
		void InitBond(
			FString Name,
			FString Type,
			float EquilibriumLength,
			float SpringConstant,
			FLinearColor Color);
//			FLinearColor Color,
	//		AAtom* AtomA,
	//		AAtom* AtomB);
	 */

	/**
	 * Construct a prototype bond.  Does not connect to any atoms.
	 * @param Name - String to identify the bond.
	 * @param Type - Type of bond (hydrogen, single, double, etc.).
	 * @param EquilibriumLength - Bond length without oscillations etc., in Angstroms.
	 * @param SpringConstant - Measure of bond strength, in kcal/(mol*A^2).
	 * @param Color - What colour to use when drawing this bond.
	 */
	UFUNCTION()
		void InitBondPrototype(
			FString Name,
			FString Type,
			float EquilibriumLength,
			float SpringConstant,
			FLinearColor Color
		);

	/**
	 * Copy constructor.  Copies properties from the Source, and connects the
	 * bond to the specified atoms.
	 * @param Source - The object to copy properties from.
	 * @param AtomA - The first atom to connect to.
	 * @param AtomB - The second atom to connect to.
	 */
	//UFUNCTION()
		//void InitBondCopy(ABond* Source, AAtom* AtomA, AAtom* AtomB);

	/**
	 * Copies properties from the Source, including the linked atoms.
	 * Used when copying a molecule.
	 */
	 // UFUNCTION()
	 // void InitBondExactCopy(ABond *Source);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * @return The identifier for the bond prototype.
	 */
	UFUNCTION()
		FString GetBondName();

	/**
	 * @return The type of bond (single, double, etc).
	 */
	UFUNCTION()
		FString GetBondType();

	/**
	 * Accesses the energy value for the bond
	 * @return - The current Energy of this bond
	 */
	UFUNCTION()
		float GetBondEnergy();

	/**
	 * Accesses the bond length for the bond
	 * @return - The stored bond length
	 */
	UFUNCTION()
		float GetBondLength();

	/**
	 * @return Pointer to the atom at one end of the bond.
	UFUNCTION()
		AAtom* GetAtomA();
	 */

	/**
	 * @return Pointer to the atom at one end of the bond.
	UFUNCTION()
		AAtom* GetAtomB();
	 */

	/**
	 * Connects one end of the bond to the given atom.
	 * @param Atom - The atom to connect to.
	UFUNCTION()
		void SetAtomA(AAtom* Atom);
	 */

	/**
	 * Connects one end of the bond to the given atom.
	 * @param Atom - The atom to connect to.
	UFUNCTION()
		void SetAtomB(AAtom* Atom);
	 */

	/** Calculates the energy stored in the bond */
	UFUNCTION()
		void UpdateBondEnergy();

	/** Calculates the distance between the two atoms involved in the bond */
	UFUNCTION()
		void UpdateBondLength();

private:
	/** A pointer to AtomA in the bond */
	//UPROPERTY()
		//AAtom* AtomA;

	/** A pointer to AtomB in the bond */
	//UPROPERTY()
		//AAtom* AtomB;

	/** Identifier for the prototype of this bond. */
	UPROPERTY()
		FString Name;

	/** Type of bond (hydrogen, single, double, etc.). */
	UPROPERTY()
		FString Type;

	/** Stores the Equilibrium BondLength in [Angstroms] */
	UPROPERTY()
		float EquilibriumLength;

	/** Stores the Current BondLength in [Angstroms] */
	UPROPERTY()
		float Length;

	/** Stores the bond spring constant in [eV/(mol*A^2)] */
	UPROPERTY()
		float SpringConstant;

	/** Stores a representation of the bond for use in engine. */
	UPROPERTY()
		UStaticMeshComponent* Representation;

	/** Stores the material for the static mesh of the representation. */
	UPROPERTY()
		UMaterial* Material;

	/** Stores the desired Color for the Material for the representation. */
	UPROPERTY()
		FLinearColor Color;
};
