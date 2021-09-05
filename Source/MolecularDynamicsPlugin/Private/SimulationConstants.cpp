// Fill out your copyright notice in the Description page of Project Settings.


#include "SimulationConstants.h"


const float USimulationConstants::AVOGADRO = 6.0221409e23;

const float USimulationConstants::BOLTZMANN = 1.38064852e-23;

const float USimulationConstants::C_TO_K_OFFSET = 273.15f;

const float USimulationConstants::COULOMBS_CONSTANT_SI = 8.9875517923e9;
//const float USimulationConstants::COULOMBS_CONSTANT_SCALED = COULOMBS_CONSTANT_SI * KG_TO_U * M3_TO_PM3 * (1 / S2_TO_PS2) * (1 / C2_TO_E2);
const float USimulationConstants::COULOMBS_CONSTANT_SCALED = 1.39e11;

const float USimulationConstants::MAX_INTERACTION_FORCE = 4.0e6;

//Area Conversions
const float USimulationConstants::M2_TO_PM2 = 1.0e24;

const float USimulationConstants::PM2_TO_M2 = 1.0e-24;


// Distance Conversions
const float USimulationConstants::CM_TO_M = 1.0e-2;
const float USimulationConstants::CM_TO_PM = 1.0e10;

const float USimulationConstants::M_TO_CM = 1.0e2;
const float USimulationConstants::M_TO_PM = 1.0e12;

const float USimulationConstants::PM_TO_CM = 1.0e-10;
const float USimulationConstants::PM_TO_M = 1.0e-12;


// Unit of Charge Conversions
const float USimulationConstants::C_TO_E = 6.242e18;
const float USimulationConstants::C2_TO_E2 = 3.896e37;

const float USimulationConstants::E_TO_C = 1.60218e-19;
const float USimulationConstants::E2_TO_C2 = 2.56698e-38;


// ENERGY CONVERSIONS
const float USimulationConstants::CAL_TO_EV = 2.611e19;
const float USimulationConstants::CAL_TO_J = 4.184f;
const float USimulationConstants::CAL_TO_KCAL = 1.0e-3;
const float USimulationConstants::CAL_TO_KJ = 4.184e-3;
const float USimulationConstants::CAL_TO_UEJ = 2.5196e27;

const float USimulationConstants::EV_TO_CAL = 3.82929e-29;
const float USimulationConstants::EV_TO_J = 1.602176634e-19;
const float USimulationConstants::EV_TO_KCAL = 3.826732796e-23;
const float USimulationConstants::EV_TO_KJ = 1.60218e-22;
const float USimulationConstants::EV_TO_UEJ = 9.6482677e7;

const float USimulationConstants::J_TO_CAL = 2.39006e-1;
const float USimulationConstants::J_TO_EV = 6.242e18;
const float USimulationConstants::J_TO_KCAL = 2.39006e-4;
const float USimulationConstants::J_TO_KJ = 1.0e-3;
const float USimulationConstants::J_TO_UEJ = 6.022e26;

const float USimulationConstants::KCAL_CAL = 1.0e3;
const float USimulationConstants::KCAL_TO_EV = 2.611e22;
const float USimulationConstants::KCAL_TO_J = 4.184e3;
const float USimulationConstants::KCAL_TO_KJ = 4.81;
const float USimulationConstants::KCAL_TO_UEJ = 2.5196e30;

const float USimulationConstants::KJ_TO_CAL = 239.006e2;
const float USimulationConstants::KJ_TO_EV = 6.242e21;
const float USimulationConstants::KJ_TO_J = 1.0e3;
const float USimulationConstants::KJ_TO_KCAL = 2.39006e-1;
const float USimulationConstants::KJ_TO_UEJ = 6.022e29;

const float USimulationConstants::UEJ_TO_CAL = 3.9689e-28;
const float USimulationConstants::UEJ_TO_EV = 1.0365e-8;
const float USimulationConstants::UEJ_TO_J = 1.6606e-27;
const float USimulationConstants::UEJ_TO_KCAL = 3.9689e-31;
const float USimulationConstants::UEJ_TO_KJ = 1.6606e-30;


// Mass Conversions
const float USimulationConstants::DA_TO_G = 1.66054e-24;
const float USimulationConstants::DA_TO_KG = 1.66054e-27;

const float USimulationConstants::G_TO_DA = 6.022e23;
const float USimulationConstants::G_TO_KG = 1.0e-3;

const float USimulationConstants::KG_TO_DA = 6.022e26;
const float USimulationConstants::KG_TO_G = 1.0e3;


// TIME CONVERSIONS
const float USimulationConstants::FS_TO_PS = 1.0e-3;
const float USimulationConstants::FS_TO_S = 1.0e-15;
const float USimulationConstants::FS_TO_TFS = 1.0e-1;

const float USimulationConstants::FS2_TO_PS2 = 1.0e-6;
const float USimulationConstants::FS2_TO_S2 = 1.0e-24;
const float USimulationConstants::FS2_TO_TFS2 = 1.0e-2;

const float USimulationConstants::PS_TO_FS = 1.0e3;
const float USimulationConstants::PS_TO_S = 1.0e-12;
const float USimulationConstants::PS_TO_TFS = 1.0e2;

const float USimulationConstants::PS2_TO_FS2 = 1.0e6;
const float USimulationConstants::PS2_TO_S2 = 1.0e-24;
const float USimulationConstants::PS2_TO_TFS2 = 1.0e4;

const float USimulationConstants::S_TO_FS = 1.0e15;
const float USimulationConstants::S_TO_PS = 1.0e12;
const float USimulationConstants::S_TO_TFS = 1.0e14;

const float USimulationConstants::S2_TO_FS2 = 1.0e30;
const float USimulationConstants::S2_TO_PS2 = 1.0e24;
const float USimulationConstants::S2_TO_TFS2 = 1.0e28;

const float USimulationConstants::TFS_TO_FS = 1.0e1;
const float USimulationConstants::TFS_TO_PS = 1.0e-2;
const float USimulationConstants::TFS_TO_S = 1.0e-14;

const float USimulationConstants::TFS2_TO_FS2 = 1.0e2;
const float USimulationConstants::TFS2_TO_PS2 = 1.0e-4;
const float USimulationConstants::TFS2_TO_S2 = 1.0e-28;


//VOLUME CONVERSIONS
const float USimulationConstants::L_TO_M3 = 1.0e-3;
const float USimulationConstants::L_TO_ML = 1.0e3;
const float USimulationConstants::L_TO_PM3 = 1.0e33;

const float USimulationConstants::M3_TO_L = 1.0e3;
const float USimulationConstants::M3_TO_ML = 1.0e6;
const float USimulationConstants::M3_TO_PM3 = 1.0e36;

const float USimulationConstants::ML_TO_L = 1.0e-3;
const float USimulationConstants::ML_TO_M3 = 1.0e-6;
const float USimulationConstants::ML_TO_PM3 = 1.0e36;

const float USimulationConstants::PM3_TO_L = 1.0e-33;
const float USimulationConstants::PM3_TO_M3 = 1.0e-36;
const float USimulationConstants::PM3_TO_ML = 1.0e-30;
