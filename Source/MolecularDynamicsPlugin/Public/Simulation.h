// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//********************************************************************
// Code Organization:
//	UE4 Default Functions
//	Physical Constants
//	Blueprint Accessible Functions
//		Dynamics - Adder Functions
//		Dynamics - Getter Functions
//		Dynamics - Initializer Functions
//		Dynamics - Other Functions
//		Dynamics - Utility Functions
//		Dynamics - Setter Functions
//	C++ Private Functions
//		Adder Functions
//		Other Functions
//		Remover Functions
//		Update Functions
//	Private Variables
//	Public Variables
//********************************************************************


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/IPluginManager.h"
#include "SimulationConstants.h"
#include "Reaction.h"
#include "Molecule.h"
#include "AtomPrototype.h"
#include "BondPrototype.h"
#include "SimulationData.h"
#include "MoleculeConcentration.h"
#include "SimulationCell.h"
#include "AtomData.h"
#include "SimRand.h"
#include "MoleculePrototype.h"
#include "Simulation.generated.h"

UCLASS()
class MOLECULARDYNAMICSPLUGIN_API ASimulation : public AActor
{
/*
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimulation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
*/
	GENERATED_BODY()

	//********************************************************************
	// UE4 Default Functions
	//********************************************************************
public:
	/**
	 * Constructs a simulation object.  Set your simulation parameters with the Init functions, then start it up with InitializeSimulation.
	*/
	ASimulation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//********************************************************************
	// Blueprint Accessible Functions
	//********************************************************************
	
	//********************************************************************
	// Dynamics - Getter Functions
	//********************************************************************

	/** Gets the counts of each molecule in the simulation*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Getter Functions")
	float GetMoleculeCounts();

	/** Gets the number of a certain type of molecule*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Getter Functions")
	int32 GetNumberOfMoleculesByType();

	/** Gets the total number of molecules in the simulation*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Getter Functions")
	int32 GetNumberOfMoleculesTotal();

	/** Gets the total energy of the simulation*/
	//UFUNCTION(BluePrintCallable, Category = "Dynamics - Getter Functions")
	//float GetSimulationEnergy();

	/** Gets the Temperature of the Simulation, in Kelvins
	 * @return temperature, in Kelvins
	*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Getter Functions")
	float GetSimulationTemp();

	/** Gets the concentrations of the molecules in the simulation */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Getter Functions")
	TArray<FMoleculeConcentration> GetSimulationConcentrations();

	/** Gets the concentration of the solute */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Getter Functions")
	float GetSolventConcentration();

	/**
	 * Get the width of one side of the (cube-shaped) simulation cell.
	 * @return Width - Cell width, in pm.
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	float GetSimulationCellWidth();

	/**
	 * Gets the volume of the simulation cell.
	 * @return The volume of the simulation cell, in pm^3
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Getter Functions")
	float GetSimulationVolume();

	/** Gets the density of a solvent*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Getter Functions")
	float GetSolventDensity();

	//********************************************************************
	// Dynamics - Initializer Functions
	//********************************************************************
	/**
	 * Reads in the AtomData.csv and loads the Atom Data for use in the simulation.
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Initializer Functions")
	void InitAtomData();
	
	/**
	 * Loads the Data Files used by the simulation
	 *	- Loads AtomData from AtomData.csv
	 *	- Loads Molecules in .pdb format
	 *	- Loads ElementaryCharges from ElementaryCharge.csv
	 *	- Loads Lennard-Jones Dispersion Energy from LJDispersionEnergy.csv (the Epsilon parameter)
	 *	- Loads Lennard-Jones Equilibrium Distance from LJEqulibrium.csv (the sigma parameter)
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Initializer Functions")
	void InitData();

	
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Initializer Functions")
	void InitInteractionData();

	/**
	 * Adds a molecule to the simulation.
	 * @param MoleculeName - The name (identifier) of the prototype molecule to copy.
	 * @param Position - The location of the new molecule.
	*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Initializer Functions")
	void InitMolecule(FString MoleculeName, FVector Position);
	
	/**
	 * Load all chemical data files (.pdb format) found in the plugin's Content/ChemData folder, and use them to
	 * construct prototypes for atoms and molecules.  Does nothing if no pdb files are found.
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Initializer Functions")
	void InitMoleculeData();

	/**
	 * Adds a number of molecules to the simulation cell distributed evenly in the available space.
	 * @param MoleculeName - the name of the molecule to add, used as a key to load molecule data
	 * @param NumMolecules - the number of molecules that should be added.
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Initializer Functions")
	void InitNumMolecules(FString MoleculeName, int32 NumMolecules);

	/**
	 * Load list of possible reactions from a file.  Should be a text file in a particular format, which we will document soon!
	 * @param FileName - Filename (with full path).
	 * @return True if the data was successfully loaded, false if not.
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Initializer Functions")
	bool InitReactionData(FString FileName);

	/**
	 * Initilizes the Simulation.  Creates the Simulation Cell and populates it with solvent and reactant molecules, then starts the simulation running.
	 * Uses hopefully-reasonably defaults for anything the user has not already set:
	 * - Default simulation cell width is 10000 pm (100 angstroms).
	 * - Default solvent is water.
	 * - Default temperature is 25C.
	 * - If no molecules are loaded, includes two default reactants (for nice visuals), with no reactions.
	*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Initializer Functions")
	void InitSimulation();

	/**
	 * Creates a SimulationCell actor and attaches it to the simulation as the root so that it will follow the simulation for scale and transforms
	 *	@param CellWidth: in Unreal Units the width that the simulation cell should be. 1 UU = 1 pM
	 *	@param CellColor the color that the borders of the cell should be.
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Initializer Functions")
	void InitSimulationCell(float CellWidth, FColor CellColor, bool bTeleportWalls);

	/**
	 * Prepares a UStruct that allows for easy passing of key information into parts of the simulation.
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Initializer Functions")
	void InitSimulationData();

	/**
	 * Sets the solvent molecule to fill the cell with.
	 * Fills the Simulation Cell with the Appropriate number of solvent molecules 
	 * @param Solvent - The molecule to use as solvent.
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Initializer Functions")
	void InitSolvent(FString SolventName);

	//********************************************************************
	// Dynamics - Other Functions
	//********************************************************************
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Other Functions")
	void ActivateSimulation();

	/** Checks if a collision has occurred; if it has, check for reactions. */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Other Functions")
	void CheckCollision();

	UFUNCTION(BluePrintCallable, Category = "Dynamics - Other Functions")
	void DeactivateSimulation();
	
	//UFUNCTION(BluePrintCallable, Category = "Dynamics - Other Functions")
	//	void EnableMoleculePhysics();

	/** Updates the Simulation*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Other Functions")
	void UpdateSimulation();

	/** Updates the Simulation Velocities to reflect the set temperature*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Other Functions")
	void UpdateSimulationTemp();

	//********************************************************************
	// Dynamics - Utility Functions
	//********************************************************************
	/** Uses the Total Kinetic Energy to calculate the average kinetic energy */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float CalculateAverageKineticEnergy();

	/** Converts the Average Kinetic Energy to the equivalent temperature in Kelvin */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float CalculateCurrentTemperature();

	/** Loops through the molecules and obtains the total kinetic energy of the molecules */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float CalculateTotalKineticEnergy();
	
	/**
	 * Converts a temperature from Celsius to Fahrenheit
	 * @param CTemp - The temperature, in degrees Celsius
	 * @return The temperature, in Fahrenheit
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_C_to_F(float CTemp);

	/**
	 * Converts a temperature from Celsius to Kelvin
	 * @param CTemp - The temperature, in degrees Celsius
	 * @return The temperature, in Kelvins
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_C_to_K(float CTemp);

	/**
	 * Converts a value in eV to Joules
	 * @param eVEnergy - Energy, in eV
	 * @return The energy in Joules
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_eV_to_J(float eVEnergy);

	/**
	 * Converts a value in eV to kCal
	 * @param eVEnergy - Energy, in eV
	 * @return The energy in kCal
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_eV_to_kCal(float eVEnergy);

	/**
	 * Converts a temperature from Fahrenheit to degrees Celsius
	 * @param FTemp - The temperature to convert, in degrees Fahrenheit
	 * @return -The Temperature, in Degrees Celsius
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_F_to_C(float KTemp);

	/**
	 * Converts a temperature from Fahrenheit to Kelvins
	 * @param FTemp - The temperature to convert, in degrees Fahrenheit
	 * @return -The Temperature, in Kelvins
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_F_to_K(float FTemp);

	/**
	 * Converts a value in Joules to eV
	 * @param JEnergy - Energy, in kCal
	 * @return The energy in eV*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_J_to_eV(float JEnergy);

	/**
	 * Converts a temperature from Kelvin to Celsius
	 * @param KTemp - The temperature, in Kelvins
	 * @return The temperature, in degrees Celsius
	*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_K_to_C(float KTemp);

	/**
	 * Converts a temperature from Kelvin to Fahrenheit
	 * @param KTemp - The temperature to convert, in Kelvins
	 * @return -The Temperature, in degrees Fahrenheit
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_K_to_F(float KTemp);

	/**
	 * Converts a value in kCal to eV
	 * @param kCalEnergy - Energy in kCal
	 * @return The energy in eV
	*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_kCal_to_eV(float kCalEnergy);

	/**
  * Converts units from L to pm^3
	 * @param LVolume - volume, in litres
	 * @return The volume in pm^3
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_L_to_pm3(float LVolume);

	/**
  * Converts units from mL to pm^3
	 * @param mLVolume - volume, in mL
	 * @return The volume in pm^3
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_mL_to_pm3(float mLVolume);

	/**
	 * Converts units from pm^3 to litres
	 * @param pm3Volume - Volume, in p^3
	 * @return Volume in litres
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_pm3_to_L(float pm3Volume);

	/**
	 * Converts units from pm^3 to mL
	 * @param pm3Volume - volume, in pm^3
	 * @return The volume in mL
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Utility Functions")
	float Convert_pm3_to_mL(float pm3Volume);

	//********************************************************************
	// Dynamics - Setter Functions
	//********************************************************************
	/** Loops through all the molecules and sets the collision spheres to be hidden in game */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetHideCollisionSpheres();

	/** Loops through all the molecules and sets the CoM spheres to be hidden in game */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetHideCoM();

	/** Loops through all the molecules and sets the CoM spheres to be hidden in game */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetHideInteractionSpheres();

	/** Loops through all the molecules and sets the bond Splines to be hidden in game */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetHideSpline();

	/** Loops through all the molecules and sets the collision spheres to be visible in game */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetShowCollisionSpheres();

	/** Loops through all the molecules and sets the CoM spheres to be visible in game */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetShowCoM();

	/** Loops through all the molecules and sets the Bond Splines to be visible in game */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetShowSpline();

	/** Loops through all the molecules and sets the CoM spheres to be hidden in game */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetShowInteractionSpheres();
	
	/**
	 * Loops through all the molecules and sets their render style to the Ball and Stick Model
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetRenderBallStick();

	/**
	 * Loops through all the molecules and sets their render style to be hidden
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetRenderHidden();

	/**
	 * Loops through all the molecules and sets their render style to the linear style
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetRenderLinear();

	/**
	 * Loops through all the molecules and sets their render style to the Space Filling style
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetRenderSpaceFilling();

	/**
	 * Set the total volume of the (cube-shaped) simulation cell.
	 * @param Volume - Cell volume, in pm3 (pm cubed).
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetSimulationCellVolume(float Volume);

	/**
	 * Set the width of one side of the (cube-shaped) simulation cell.
	 * @param Width - Cell width, in pm.
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetSimulationCellWidth(float Width);

	/**
	 * Sets the temperature of the simulation
	 * @param Temp - Desired Temperature, in Kelvins
	*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetSimulationTemp(float temp);

	/**
	 * Sets the concentration of the solute.
	 * @param NewConcentration - Desired concentration, in moles per litre solution.
	*/
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetSoluteConcentration(float NewConcentration);

	/** Multiplier that adjusts the number of solvent molecules added to the simulation cell */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetSolventModifier(float SolventModifier);

	/**
	 * Sets a scale factor to speed up/slow down the simulation motion.
	 * @param ScaleFactor - Speed multiplier (1=default; larger is faster)
	 */
	UFUNCTION(BluePrintCallable, Category = "Dynamics - Setter Functions")
	void SetTimeScale(float ScaleFactor);

	//********************************************************************
	// C++ Private Functions
	//********************************************************************
private:
	//********************************************************************
	// Adder Functions
	//********************************************************************
	/** Add a hydrogen bond to the simulation */
	UFUNCTION()
	void AddHydrogenBond();

	/** Adds a reaction to the simulation */
	UFUNCTION()
	void AddReaction();

	//********************************************************************
	// Other Functions
	//********************************************************************

	/** Prepares a (hard-coded) default set of atoms and molecules.  This is called by InitializeSimulation if the prototypes have not yet been built (e.g. loaded from files). */
	UFUNCTION()
	void BuildDefaultPrototypes();

	UFUNCTION()
	float CalculateAverageMoleculeSpeed();
	
	UFUNCTION()
	FVector CalculateDivisionsForNumMolecules(int32 NumAtoms);

	UFUNCTION()
	float CalculateInitialAverageSpeed();
	
	/** Calculates the net force on a molecule */
	UFUNCTION()
	float CalculateNetForceForMolecule();

	/**
	 * Determines how many solvent molecules we'll need, given the density and molecular mass.
	 * TODO: Similar function based on the molarity instead of mass density.
	 */
	UFUNCTION()
	int32 CalculateNumberOfSolventMolecules(float Density, float MolarMass);

	UFUNCTION()
	FVector CalculateSolventMoleculePosition(int32 CurrentCount, int TotalNum);

	UFUNCTION()
	TArray<FVector> CalculateSubdivisionPositions(FVector& SubDivisions);

	/** Checks to see if a reaction has occured. */
	UFUNCTION()
	bool CheckReaction();

	/** Processes the H bonds in the simulation */
	UFUNCTION()
	void ProcessHBonds();

	/** Sets the reaction distance in the smulation */
	UFUNCTION()
	void SetReactionDistance();

	//********************************************************************
	// Remover Functions
	//********************************************************************
	/** Removes a hydrogen bond from the simulation */
	UFUNCTION()
	void RemoveHydrogenBond();

	/** Removes a molecule from the simulation
	 * @param Target - The molecule to remove.
	*/
	UFUNCTION()
	void RemoveMolecule(AMolecule* Target);

	/** Removes a reaction from the simulation*/
	UFUNCTION()
	void RemoveReaction();

	//********************************************************************
	// Update Functions
	//********************************************************************
	/** Updated all the forces on the molecule */
	UFUNCTION()
	void UpdateForcesOnMolecules();

	/** Updates the total energy of the simulation */
	//UFUNCTION()
	//void UpdateSystemEnergy();

	//********************************************************************
	// Private Variables
	//********************************************************************
private:
	/** Name of this plugin; needed for paths. (If there's a built-in way to get this, please change the code!) */
	const FString PLUGIN = TEXT("MolecularDynamicsPlugin");

	/** An array of active reaction objects*/
	UPROPERTY()
	TArray<FReaction> ActiveReactions;

	/** Table describing each available atom. */
	//UPROPERTY()
	//UDataTable *AtomDataTable;

	/** Path to the plugin's Content directory, where data files are stored. */
	FString ContentDir;

	/** Array of molecule objects in the simulation*/
	UPROPERTY()
	TArray<AMolecule*> Molecules;

	/** Array of Possible reactions*/
	UPROPERTY()
	TArray<FReaction> PossibleReactions;

	/** An array of prototype molecule objects. Keys are molecule names. */
	UPROPERTY()
	TMap<FString, FMoleculePrototype> PrototypeMolecules;

	/** Random number generator. */
	UPROPERTY()
	USimRand* RandGen;

	/** Controls if UpdateSimulation Should fire */
	UPROPERTY(EditAnywhere, Category = "Simulation")
	bool bSimulationActive;

	/** Used to check if the simulation just deactivated */
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	bool bSimulationWasActive;

	/** SimulationCell object*/
	UPROPERTY()
	ASimulationCell* SimulationCell;

	UPROPERTY()
	USimulationData* SimulationData;

	UPROPERTY()
	float SolventModifier = 1.0f;

	/** Total Energy of the system, in eV. */
	//UPROPERTY()
	//float SystemEnergy;

	/**Allowable change in the total system in one time step, in eV*/
	//UPROPERTY()
	//float SystemEnergyTolerance;

	/** Factor affecting speed of simulation*/
	UPROPERTY()
	float TimeScale;

	//********************************************************************
	// Public Variables
	//********************************************************************
public:
	/** Temperature setpoint of the simulation, in Kelvins.  Default is 25 C, the IUPAC standard ambient temperature. */
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Simulation")
	float Temperature;
	
	//Atom Static Mesh
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Dynamics - Representation")
	UStaticMesh* SM_Atom;

	//Atom Base Material
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Dynamics - Representation")
	UMaterialInterface* M_AtomBase;
};
