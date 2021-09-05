#pragma once

/*
Data about a specific reaction and its products.
*/

#include "UObject/Class.h"
#include "Reaction.generated.h"

USTRUCT(BlueprintType)
struct FReaction
{
	GENERATED_BODY()

	/**English name of Reactant A molecule*/
	UPROPERTY()
	FString ReactantAName;

	/**English name of reactant B molecule*/
	UPROPERTY()
		FString ReactantBName;

	/**Energy threshold required for the reaction to occur, in eV*/
	UPROPERTY()
		float EnergyThreshold;

	/**Probability that the reaction will occur*/
	UPROPERTY()
		float ReactionProbability;

	/**An array of English names of molecules*/
	UPROPERTY()
		TArray<FString> ListOfProducts;

	/**the amount of energy released in a reaction, in eV.*/
	UPROPERTY()
		float EnergyProduct;

};
