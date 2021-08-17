// Fill out your copyright notice in the Description page of Project Settings.

/*
Utility class providing functions to generate random properties for the molecule simulation, using appropriate probability distributions.
*/

#pragma once

#include "CoreMinimal.h"
#include "LookupTable.h"
#include "SimRand.generated.h"

UCLASS()
class USimRand : public UObject
{
    GENERATED_BODY()

public:

    USimRand();

    /** Initialize the lookup tables. */
    UFUNCTION()
        void Init();

    /**
    * Get a random value from a standard normal (Gaussian) distribution.
    */
    UFUNCTION()
    float RandF_Normal();

    /**
     * Generate a random 3D velocity from the Maxwell-Boltzmann distribution for ideal gases.
     * @param Mass_u - Particle mass, in u (atomic mass units).
     * @param Temperature - Ensemble temperature, in kelvin.
    */
    UFUNCTION()
    FVector RandV_MaxwellBoltzmann(float Mass_u, float Temperature);
    

private:


    /**
    * Normal distribution CDF (cumultative distribution function).  Can use this to convert a uniform random number between 0 and 1 into a normally distributed random number with mean 0 and SD 1.
    */
    UPROPERTY()
    ULookupTable *NormalDist;

};

/*
    // FIXME: For testing.
    USimRand *sr = NewObject<USimRand>();
    sr->Init();
    FVector foo = sr->RandV_MaxwellBoltzmann(18, 300);
    UE_LOG(LogTemp, Warning, TEXT("ASimulation SimRand test: %s"), *foo.ToCompactString());

*/
