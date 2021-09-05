#pragma once

/*
Data about a specific reaction and its products.
*/

#include "UObject/Class.h"
#include "AtomPrototype.generated.h"

USTRUCT(BlueprintType)
struct FAtomPrototype
{
	GENERATED_BODY()

	/** English Symbol of the Atom */
	UPROPERTY()
	FString Symbol;

	/** The initial position of the atom */
	UPROPERTY()
	FVector Position;

	/** The serial number of the atom in the molecule (used by other entries in the PDB file. */
	UPROPERTY()
	int32 SerialNumber;
};
