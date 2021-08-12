#pragma once

/*
Description of a bond between two atoms IN A MOLECULE.  (Not to be used for intermolecular bonds.)
*/

#include "UObject/Class.h"
#include "BondType.h"
#include "BondPrototype.generated.h"

USTRUCT(BlueprintType)
struct FBondPrototype
{
	GENERATED_BODY()

	/** Type of bond ("single", "double", etc). */
	UPROPERTY()
	EBondType BondType;

	/** Index of Atom at one end of the bond, in the molecule's Atoms array.  This should be the SMALLER of the two atom indices. */
	UPROPERTY()
	int32 IndexA;

	/** Index of Atom at the other end of the bond, in the molecule's Atoms array.  This should be the LARGER of the two atom indices. */
	UPROPERTY()
	int32 IndexB;

};
