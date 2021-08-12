// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/*
Structure for storing one row of the AtomData CSV file.
*/

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "AtomData.generated.h"

USTRUCT(BlueprintType)
struct FAtomData : public FTableRowBase {
GENERATED_USTRUCT_BODY()

public:

	// FIXME: I (Rob) am not sure if these UPROPERTY parameters are correct...

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtomData")
		int32 AtomicNumber;

	/** The full English name of the element (e.g. "Hydrogen"). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtomData")
		FString ElementName;

	/** The base colour to use for this atom, in RGB hex format. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtomData")
		FString Color;

	/** The van der Waals covalent radius of the atom, in picometres.  This sets the size of the atom in space-filling representation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtomData")
		float Radius;

	/** The atom's (average, standard, default) mass in amu. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtomData")
		float Mass;

	/** The length of this atom's side of a single bond, in picometres. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtomData")
		float BondLengthSingle;

	/** The length of this atom's side of a double bond, in picometres. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtomData")
		float BondLengthDouble;

	/** The length of this atom's side of a triple bond, in picometres. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AtomData")
		float BondLengthTriple;

};

