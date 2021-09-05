// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SimulationConstants.generated.h"

/**
 * UNITS USED IN THE SIMULATION
 * 1 Unreal Unit = 1 picometer
 * 1 Unreal KG = 1 Dalton
 * 1 Unreal Second = 1 picosecond
 *
 * We are working in:
 * elementary Charge for Unit of Charge
 * F = m * a (U
 *
 *energy unit
 * Unreal engine joule UEJ
 */
UCLASS()
class USimulationConstants : public UDataAsset
{
	GENERATED_BODY()

public:
    /** Avogadro's number in mol^-1 */
    static const float AVOGADRO;
	
    /** Boltzmann's Constant (k_B or just k), in J/K */
    static const float BOLTZMANN;

    /** Conversion offset from Celsius to Kelvin */
    static const float C_TO_K_OFFSET;

	/** Coulomb's Constant in SI, kg m^3 s^-2 C^-2 */
    static const float COULOMBS_CONSTANT_SI;

	/** Coulomb's Constant in U pm^3 ps^-2 e^-2 */
    static const float COULOMBS_CONSTANT_SCALED;

    static const float MAX_INTERACTION_FORCE;

	//Area Conversions
	/** Square Meter Conversions */
    static const float M2_TO_PM2;

	/** Square Picometer Conversions */
    static const float PM2_TO_M2;

	
    // Distance Conversions
    /** Centimeter conversions */
	static const float CM_TO_M;
    static const float CM_TO_PM;
	
    /** Meter conversions */
    static const float M_TO_CM;
    static const float M_TO_PM;

	/** Picometer conversions */
    static const float PM_TO_CM;
	static const float PM_TO_M;

	
    // Unit of Charge Conversions
    /** Coulomb Conversions */
    static const float C_TO_E;
    static const float C2_TO_E2;
	
	/** elementary Charge conversion */
    static const float E_TO_C;
    static const float E2_TO_C2;

	
	// ENERGY CONVERSIONS
    /** gram Calorie Conversions */
    static const float CAL_TO_EV;
    static const float CAL_TO_J;
    static const float CAL_TO_KCAL;
    static const float CAL_TO_KJ;
    static const float CAL_TO_UEJ;
	
	/** ElectronVolt Conversions */
    static const float EV_TO_CAL;
    static const float EV_TO_J;
    static const float EV_TO_KCAL;
    static const float EV_TO_KJ;
    static const float EV_TO_UEJ;

	/** Joule Conversions */
    static const float J_TO_CAL;
    static const float J_TO_EV;
    static const float J_TO_KCAL;
    static const float J_TO_KJ;
    static const float J_TO_UEJ;

	/** KiloCalorie conversions */
    static const float KCAL_CAL;
    static const float KCAL_TO_EV;
    static const float KCAL_TO_J;
    static const float KCAL_TO_KJ;
    static const float KCAL_TO_UEJ;
	
    /** KiloJoule Conversions */
    static const float KJ_TO_CAL;
    static const float KJ_TO_EV;
    static const float KJ_TO_J;
    static const float KJ_TO_KCAL;
    static const float KJ_TO_UEJ;

	/** Unreal Engine Joule conversions (The unit of energy we are using) [Da pm^2 ps^-2] */
    static const float UEJ_TO_CAL;
    static const float UEJ_TO_EV;
	static const float UEJ_TO_J;
    static const float UEJ_TO_KCAL;
    static const float UEJ_TO_KJ;
	
	// Mass Conversions
	/** Dalton Conversions*/
    static const float DA_TO_G;
    static const float DA_TO_KG;
	
	/** Gram Conversions */
    static const float G_TO_KG;
    static const float G_TO_DA;
	
	/** Kilogram Conversions */
    static const float KG_TO_DA;
    static const float KG_TO_G;


	// TIME CONVERSIONS
    /** Femtosecond Conversions*/
    static const float FS_TO_PS;
    static const float FS_TO_S;
    static const float FS_TO_TFS;

	/** squared femtosecond conversions */
    static const float FS2_TO_PS2;
    static const float FS2_TO_S2;
    static const float FS2_TO_TFS2;
	
    /** Picosecond conversions */
    static const float PS_TO_FS;
	static const float PS_TO_S;
	static const float PS_TO_TFS;

	/** squared picosecond conversions */
    static const float PS2_TO_FS2;
    static const float PS2_TO_S2;
    static const float PS2_TO_TFS2;
	
    /** Second Conversions */
    static const float S_TO_FS;
    static const float S_TO_PS;
    static const float S_TO_TFS;

	/** squared second conversions */
    static const float S2_TO_FS2;
    static const float S2_TO_PS2;
    static const float S2_TO_TFS2;

	/** Tens of FemtoSeconds */
    static const float TFS_TO_FS;
    static const float TFS_TO_PS;
    static const float TFS_TO_S;
	
	/** Squared tens of Femtoseconds conversion*/
    static const float TFS2_TO_FS2;
    static const float TFS2_TO_PS2;
    static const float TFS2_TO_S2;

	//VOLUME CONVERSIONS
    /** Liter Conversions */
    static const float L_TO_M3;
	static const float L_TO_ML;
    static const float L_TO_PM3;

	/** Cubic meter conversions */
    static const float M3_TO_L;
    static const float M3_TO_ML;
    static const float M3_TO_PM3;

	/** Millilter conversions */
    static const float ML_TO_L;
    static const float ML_TO_M3;
    static const float ML_TO_PM3;

	/** cubic picometer conversions */
	static const float PM3_TO_L;
    static const float PM3_TO_M3;
    static const float PM3_TO_ML;
};


