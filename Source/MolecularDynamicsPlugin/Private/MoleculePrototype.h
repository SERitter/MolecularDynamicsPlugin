#pragma once

/*
Data about a specific reaction and its products.
*/

#include "UObject/Class.h"
#include "BondPrototype.h"
#include "AtomPrototype.h"
#include "MoleculePrototype.generated.h"

USTRUCT(BlueprintType)
struct FMoleculePrototype
{
	GENERATED_BODY()

	/**English name of molecule*/
	UPROPERTY()
	FString Name = FString("Unnamed");

	/**English Formula of molecule*/
	UPROPERTY()
	FString Formula = FString("N/A");

	/**Density in kg/m^3*/
	UPROPERTY()
	float Density = 0.0f;

	/**Molar Mass in g/mol*/
	UPROPERTY()
	float MolarMass = 0.0f;

	/**An array of Atoms in the Molecule*/
	UPROPERTY()
	TArray<FAtomPrototype> Atoms;

	/**An array of Bonds in the Molecule*/
	UPROPERTY()
	TArray<FBondPrototype> Bonds;
};
