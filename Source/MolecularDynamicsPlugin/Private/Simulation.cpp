// Fill out your copyright notice in the Description page of Project Settings.


//********************************************************************
// Code Organization:
//	UE4 Default Functions
//	Blueprint Accessible Functions
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
//********************************************************************

#include "Simulation.h"



//********************************************************************
// UE4 Default Functions
//********************************************************************
// Sets default values
ASimulation::ASimulation()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::ASimulation() Called."));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SimulationData = NewObject<USimulationData>();
	SimulationData = CreateDefaultSubobject<USimulationData>(TEXT("SimulationData"));

	// Default simulation values.
	//SystemEnergy = 0;
	//SystemEnergyTolerance = 0.01; // FIXME: This is an arbitrary tolerance value!
	Temperature = 298.15;
	SimulationData->SetInitialTemperature(298.15);
	SimulationData->SetSimulationSpeed(1.0f);
	bSimulationActive = false;
}

// Called when the game starts or when spawned
void ASimulation::BeginPlay()
{
	//UE_LOG(LogTemp, Warning, TEXT("ASimulation::BeginPlay() Called."));
	Super::BeginPlay();
}

// Called every frame
void ASimulation::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("ASimulation::Tick() Called."));
	Super::Tick(DeltaTime);
}

//********************************************************************
// Blueprint Accessible Functions
//********************************************************************

//********************************************************************
// Dynamics - Getter Functions
//********************************************************************
float ASimulation::GetMoleculeCounts()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::GetMoleculeCounts() Called - Still needs implementation."));
	return 0.0f;
}

int32 ASimulation::GetNumberOfMoleculesByType()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::GetNumberOfMoleculesByType() Called - Still needs implementation."));
	return 0;
}

int32 ASimulation::GetNumberOfMoleculesTotal()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::GetNumberOfMoleculesTotal() Called - Still needs implementation."));
	return 0;
}

/*
float ASimulation::GetSimulationEnergy()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::GetSimulationEnergy() Called: %E."), SystemEnergy);
	return SystemEnergy;
}
*/

float ASimulation::GetSimulationTemp()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::GetSimulationTemp() Called: %f."), Temperature);
	return Temperature;
}

TArray<FMoleculeConcentration> ASimulation::GetSimulationConcentrations()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::GetSimulationConcentrations() Called - Still needs implementation."));
	return TArray<FMoleculeConcentration>();
}

float ASimulation::GetSolventConcentration()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::GetSolventConcentration() Called - Still needs implementation."));
	return 0.0f;
}

float ASimulation::GetSimulationCellWidth()
{
	return SimulationCell->GetWidth();
}

float ASimulation::GetSimulationVolume()
{
	float volume = SimulationCell->GetVolume();
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::GetSimulationVolume() Called: %f."), volume);
	return volume;
}

float ASimulation::GetSolventDensity()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::GetSolventDensity() Called - Still needs implementation."));
	return 0.0f;
}



//********************************************************************
// Dynamics - Initializer Functions
//********************************************************************
void ASimulation::InitAtomData()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitAtomData() Called."));
	FString ChemDataDirName = TEXT("ChemData");
	FString ChemDataDir = ContentDir + TEXT("/") + ChemDataDirName;

	////////////////////////////////////////
	// Load atom data.

	FString AtomDataFile = ChemDataDir + TEXT("/AtomData.csv");
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitAtomData called.  Huzzah!"));
	if (!FPaths::DirectoryExists(ChemDataDir)) {
		UE_LOG(LogTemp, Error, TEXT("ASimulation::InitAtomData() Could not find dir %s"), *ChemDataDir);
		return;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitAtomData() Found dir %s"), *ChemDataDir);
	}
	if (!FPaths::FileExists(AtomDataFile)) {
		UE_LOG(LogTemp, Error, TEXT("ASimulation::InitAtomData() Could not find file %s"), *AtomDataFile);
		return;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitAtomData() Found file %s"), *AtomDataFile);
	}

	// Create a new data table based on the atom data row struct.
	UDataTable* AtomDataTable = NewObject<UDataTable>();
	AtomDataTable->RowStruct = FAtomData::StaticStruct();

	// Load the atom data file into a single string, and import it into the data table.
	FString FileContent;
	TArray<FString> Problems;
	bool success;
	success = FFileHelper::LoadFileToString(FileContent, *AtomDataFile);
	//UE_LOG(LogTemp, Warning, TEXT("LoadChemData LoadFileToString status: %s, length: %d"), (success ? TEXT("true") : TEXT("false")), FileContent.Len());
	Problems = AtomDataTable->CreateTableFromCSVString(FileContent);
	if (Problems.Num() > 0) {
		UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitAtomData() %d problems loading AtomDataTable."), Problems.Num());
		for (int i = 0; i < Problems.Num(); ++i) {
			UE_LOG(LogTemp, Warning, TEXT("p%d: %s"), i, *Problems[i]);
		}
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitAtomData() Successfully loaded AtomDataTable."))
	SimulationData->SetAtomData(AtomDataTable);
}

void ASimulation::InitData()
{
	InitAtomData();
	InitMoleculeData();
	InitInteractionData();
	InitSimulationData();
}

void ASimulation::InitInteractionData()
{
	FString ChemDataDir = ContentDir + TEXT("/ChemData");
	FString DataFile = ChemDataDir + TEXT("/OH_Interaction_Force_Clamped.csv");
	ULookupTable *ForceTable;
	if (!FPaths::DirectoryExists(ChemDataDir))
	{
		UE_LOG(LogTemp, Error, TEXT("ASimulation::InitInteractionData() Could not find dir %s"), *ChemDataDir);
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitInteractionData() Found dir %s"), *ChemDataDir);
	}
	if (!FPaths::FileExists(DataFile))
	{
		UE_LOG(LogTemp, Error, TEXT("ASimulation::InitInteractionData() Could not find file %s"), *DataFile);
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitInteractionData() Found file %s"), *DataFile);
	}

	ForceTable = NewObject<ULookupTable>();
	ForceTable->InitFromCSVFile(DataFile);
	SimulationData->SetInteractionForceTable(ForceTable);
}

void ASimulation::InitMolecule(FString MoleculeName, FVector Position)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMolecule(%s) Called."), *MoleculeName);

	FString NumberedName = FString(TEXT("Molecule-"));
	NumberedName += FString::FromInt(Molecules.Num());
	NumberedName += FString(TEXT("-"));
	NumberedName += MoleculeName;
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = SimulationCell;
	SpawnInfo.Name = *NumberedName;
	AMolecule* NewMolecule = GetWorld()->SpawnActor<AMolecule>(GetActorLocation(), GetActorRotation(), SpawnInfo);
	NewMolecule->SetActorLabel(*NumberedName);

	if (!this->PrototypeMolecules.Contains(TEXT("Water")))
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR - ASimulation::InitMolecule(%s) - Not found in PrototypeMolecules List."), *MoleculeName);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMolecule(%s) - Prototype Molecule Found."), *MoleculeName);

	NewMolecule->InitMolecule(PrototypeMolecules[MoleculeName], Molecules.Num(), SimulationData);

	//NewMolecule->InitMolecule(PrototypeMolecules[MoleculeName], Molecules.Num(), AtomDataTable, SimulationCell);

	//FRotator RandomRotation = FRotator(FMath::FRandRange(-180.f, 180.f), FMath::FRandRange(-180.f, 180.f), FMath::FRandRange(-180.f, 180.f));
	//NewMolecule->SetActorRotation(RandomRotation);

	//Add Initial movement to molecule
	FVector NewVelocity = RandGen->RandV_MaxwellBoltzmann(NewMolecule->GetMoleculeMass(), SimulationData->GetInitialTemperature());
	NewVelocity = NewVelocity * this->GetActorScale();
	//NewMolecule->SetInitialTemperature(InitialMoleculeTemperature);
	NewMolecule->SetInitialVelocity(NewVelocity);
	// Angular velocity is calculated assuming 3 rotational degrees of freedom;
	// that means rotational energy has the same distribution as kinetic energy. 
	// So we'll pick a rotational energy by sampling another velocity, then pick
	// a random axis and assign the rotational velocity from that energy.
	// Rotational energy = (1/2)I*omega^2.
	// Note that the units of mass should cancel, so as long as everything is in the same mass units it's fine.
	FVector AngVelocity = RandGen->RandV_MaxwellBoltzmann(NewMolecule->GetMoleculeMass(), SimulationData->GetInitialTemperature());
	float Energy = 0.5 * NewMolecule->GetMoleculeMass() * AngVelocity.SizeSquared();
	int32 Axis = FMath::RandRange(0, 2);
	float I = PrototypeMolecules[MoleculeName].MomentOfInertia[Axis];
	float RotationSpeed = FMath::Sqrt(2 * Energy / I);
	if (FMath::RandBool()) RotationSpeed *= -1;
	AngVelocity.Set(0, 0, 0);
	AngVelocity[Axis] = RotationSpeed;
	AngVelocity = AngVelocity * this->GetActorScale();
	NewMolecule->SetAngularVelocity(AngVelocity);


	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMolecule(%s) - Name: %s. Velocity: %s. Angular Velocity: %s."), *MoleculeName, *NewMolecule->GetName(), *NewVelocity.ToString(), *AngVelocity.ToString());
	NewMolecule->AttachToActor(SimulationCell, FAttachmentTransformRules::SnapToTargetIncludingScale);
	NewMolecule->SetActorRelativeLocation(Position);
	NewMolecule->SetInitialPosition(Position);
	Molecules.Add(NewMolecule);
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMolecule(%s) Completed."), *MoleculeName);
}

void ASimulation::InitMoleculeData()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMoleculeData() Called."));
	FString ChemDataDirName = TEXT("ChemData");
	FString ChemDataDir = ContentDir + TEXT("/") + ChemDataDirName;
	////////////////////////////////////////
	// Load molecule data.

	float LengthScale = 100; // Factor to convert units in PDB (angstroms) to our units (pm).

	// Check the various "Content" folders for ChemData subfolders with PDB files in them.
	TArray<FString> FileList, PartialFileList;
	IFileManager& FileManager = IFileManager::Get();
	FString PDBwildcard = TEXT("*.pdb");
	TArray<FString> SearchDirs;
	SearchDirs.Add(FPaths::ProjectContentDir() + ChemDataDirName);
	SearchDirs.Add(FPaths::EngineContentDir() + ChemDataDirName);
	SearchDirs.Add(ChemDataDir);
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMoleculeData() Searching %d folders for PDB files."), SearchDirs.Num());


	for (int idir = 0; idir < SearchDirs.Num(); ++idir) {
		PartialFileList.Empty();
		FString SearchDir = SearchDirs[idir];
		FString fullpath;
		if (FPaths::DirectoryExists(SearchDir)) {
			fullpath = SearchDir + TEXT("/") + PDBwildcard;
			FileManager.FindFiles(PartialFileList, *fullpath, true, false);
			UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMoleculeData() Found %d PDB files in folder %s"), PartialFileList.Num(), *fullpath);
			for (int i = 0; i < PartialFileList.Num(); ++i) {
				PartialFileList[i] = SearchDir + TEXT("/") + PartialFileList[i];
			}
			FileList += PartialFileList;
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("No ChemData folder at %s"), *SearchDir);
		}
	} // loop over search dirs

	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMoleculeData() Found %d PDB files."), FileList.Num());
	// Read the molecule data from each PDB file.  (We'll be ignoring a lot of what's in there.)
	TArray<FString> MolNames; // For checking for duplicates.
	FString MolName, Record, Symbol, Xstr, Ystr, Zstr;
	int32 PathIdx, Serial;
	for (int ifile = 0; ifile < FileList.Num(); ++ifile) {
		//FString PDBfile = ChemDataDir + TEXT("/") + FileList[ifile];
		FString PDBfile = FileList[ifile];
		PDBfile.FindLastChar('/', PathIdx);
		MolName = PDBfile.Right(PDBfile.Len() - PathIdx - 1);
		MolName = MolName.Replace(TEXT(".pdb"), TEXT(""));

		// If we've already loaded a file with this molecule name, skip it.
		if (MolNames.Contains(MolName)) {
			UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMoleculeData() Molecule %s already loaded!  Skipping file %s"), *MolName, *PDBfile);
			continue;
		}

		UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMoleculeData() Loading molecule %s from file %s"), *MolName, *PDBfile);
		MolNames.Add(MolName);

		TArray<FString> lines;
		bool success;
		success = FFileHelper::LoadFileToStringArray(lines, *PDBfile);
		if (success) {
			UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMoleculeData() Successfully loaded PDB file %s"), *PDBfile);
			FMoleculePrototype Mol;
			//Mol.Name = FileList[ifile].Replace(TEXT(".pdb"), TEXT(""));
			Mol.Name = MolName;
			for (int iline = 0; iline < lines.Num(); ++iline) {
				Record = lines[iline].Left(6);
				if (Record == TEXT("ATOM  ") || Record == TEXT("HETATM")) {
					// An atom in the molecule.
					FAtomPrototype Atom;
					Symbol = lines[iline].Mid(76, 2).TrimStartAndEnd();
					Xstr = lines[iline].Mid(30, 8).TrimStartAndEnd();
					Ystr = lines[iline].Mid(38, 8).TrimStartAndEnd();
					Zstr = lines[iline].Mid(46, 8).TrimStartAndEnd();

					Atom.Symbol = Symbol;
					Atom.Position = FVector(
						FCString::Atof(*Xstr) * LengthScale,
						FCString::Atof(*Ystr) * LengthScale,
						FCString::Atof(*Zstr) * LengthScale
					);

					Atom.SerialNumber = FCString::Atoi(*(lines[iline].Mid(6, 5).TrimStartAndEnd()));

					Mol.Atoms.Push(Atom);
				}
				else if (Record == TEXT("CONECT")) {
					// A bond between two molecules.
					// In PDB format, a CONECT line has a series of serial numbers, each in a 5-character field.  Technically we can't assume that there's any whitespace between fields.
					// The first is the reference atom for that row, and the rest are all the other atoms that _this_ atom is bonded to.  The format is redundant in that each bond is listed TWICE.
					// To get around the redundancy, on any given CONECT line we'll only create a bond when the serial number of the reference atom is lower than the "target" serial number.
					// NOTE: We actually store the array indices instead of serial numbers, for better efficiency later.
					int32 Ref = FCString::Atoi(*(lines[iline].Mid(6, 5).TrimStartAndEnd()));
					int32 IndexA = -1;
					int32 IndexB;
					FBondPrototype Bond;
					FAtomPrototype AtomA, AtomB;
					FAtomData* AtomAData = nullptr;
					FAtomData* AtomBData = nullptr;
					for (int idx = 11; idx < lines[iline].Len(); idx += 5) {
						Serial = FCString::Atoi(*(lines[iline].Mid(idx, 5).TrimStartAndEnd()));
						if (Serial > Ref) {
							if (IndexA < 0) {
								// Now we know we need to set up a bond for this line, so it's
								// worth finding the reference index.
								for (int j = 0; j < Mol.Atoms.Num(); j++) {
									if (Mol.Atoms[j].SerialNumber == Ref) {
										IndexA = j;
										break;
									}
								}
								if (IndexA >= 0) {
									AtomA = Mol.Atoms[IndexA];
									AtomAData = SimulationData->GetAtomData()->FindRow<FAtomData>(FName(*AtomA.Symbol), "");
								}
							}
							IndexB = -1;
							for (int j = 0; j < Mol.Atoms.Num(); j++) {
								if (Mol.Atoms[j].SerialNumber == Serial) {
									IndexB = j;
									break;
								}
							}
							if (IndexA < 0 || IndexB < 0) {
								// FIXME: This should probably stop the program, but I (Rob) don't know how to do that gracefully...
								UE_LOG(LogTemp, Error, TEXT("ASimulation::InitMoleculeData() ERROR! Serial number not found reading line %d of %s!"), (iline + 1), *PDBfile);
								break;
							}

							// Calculate the bond length and compare to the expected lengths for different
							// bond types.
							// (This would be much better code if the lengths for bond types were stored in an array for each atom, but I (Rob) don't think that the data table loader can do that.)
							// Note that for atoms that can't make double/triple bonds (like hydrogen), those bond lengths are set to 0.  That _should_ mean the single-bond length will always be the closest to the actual bond length and we don't have to explicitly check, unless something goes horribly wrong...
							AtomB = Mol.Atoms[IndexB];
							float BondLength = FVector::Dist(AtomA.Position, AtomB.Position);
							AtomBData = SimulationData->GetAtomData()->FindRow<FAtomData>(FName(*AtomB.Symbol), "");
							float L1 = AtomAData->BondLengthSingle + AtomBData->BondLengthSingle;
							float L2 = AtomAData->BondLengthDouble + AtomBData->BondLengthDouble;
							float L3 = AtomAData->BondLengthTriple + AtomBData->BondLengthTriple;
							float Dmin1 = FMath::Abs(L1 - BondLength);
							float Dmin2 = FMath::Abs(L2 - BondLength);
							float Dmin3 = FMath::Abs(L3 - BondLength);
							float Dmin = Dmin1;
							EBondType BondType = EBondType::SINGLE;
							if (Dmin2 < Dmin) {
								Dmin = Dmin2;
								BondType = EBondType::DOUBLE;
							}
							if (Dmin3 < Dmin) {
								Dmin = Dmin3;
								BondType = EBondType::TRIPLE;
							}


							//Bond.BondType = EBondType::SINGLE; // FIXME!
							Bond.BondType = BondType;
							Bond.IndexA = IndexA;
							Bond.IndexB = IndexB;

							// Report the results to the log file.
							uint8 BondOrder = (uint8)(Bond.BondType) + 1;
							UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMoleculeData() Constructed order %d bond between atoms %d and %d."), BondOrder, Bond.IndexA, Bond.IndexB);

							// Store the bond data!
							Mol.Bonds.Push(Bond);
						}
					} // Loop over target atoms in CONECT row.
				} // if chain for record type
			} // Finished reading PDB file.

			// Calculate molar mass, centre of mass, and moments of inertia of the molecule.
			float Mass = 0;
			FVector CM(0);
			FVector MofI(0);
			for (int iatom = 0; iatom < Mol.Atoms.Num(); ++iatom) {
				FAtomData* AtomData = SimulationData->GetAtomData()->FindRow<FAtomData>(FName(*Mol.Atoms[iatom].Symbol), "");
				if (AtomData != nullptr) {
					UE_LOG(LogTemp, Warning, TEXT("InitMoleculeData Table has atom %s with mass %f."),
						*Mol.Atoms[iatom].Symbol, AtomData->Mass);
					Mass += AtomData->Mass;
					CM += AtomData->Mass * Mol.Atoms[iatom].Position;

					// Moment of inertia is currently calculated assuming solid spheres instead of point masses,
					// to match the mass distribution used by Unreal Engine.  This is NOT CORRECT but
					// it's the only way to get the _energy_ right, since UE doesn't have point masses.
					// Treat each atom as a sphere (I=(2/5)m*r^2); parallel axis theorem says we then add
					// a "point mass" term (m*R^2) for the offset from the rotation axis.
					float I = (2 / 5) * AtomData->Mass * AtomData->VDWRadius * AtomData->VDWRadius;
					float R2; // square of perpendicular distance from rotation axis
					R2 = FMath::Pow(Mol.Atoms[iatom].Position.Y, 2) + FMath::Pow(Mol.Atoms[iatom].Position.Z, 2);
					MofI.X += I + AtomData->Mass * R2;
					R2 = FMath::Pow(Mol.Atoms[iatom].Position.X, 2) + FMath::Pow(Mol.Atoms[iatom].Position.Z, 2);
					MofI.Y += I + AtomData->Mass * R2;
					R2 = FMath::Pow(Mol.Atoms[iatom].Position.X, 2) + FMath::Pow(Mol.Atoms[iatom].Position.Y, 2);
					MofI.Z += I + AtomData->Mass * R2;
				}
			}
			CM = CM / Mass;
			Mol.MolarMass = Mass;
			Mol.Density = -1; // Density of this molecule in the simulation; needs to be set later.
			Mol.MomentOfInertia = MofI;

			// Shift atom positions to put the coordinate origin at the centre of mass.
			for (int iatom = 0; iatom < Mol.Atoms.Num(); ++iatom) {
				Mol.Atoms[iatom].Position -= CM;
			}

			PrototypeMolecules.Add(Mol.Name, Mol);

			UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMoleculeData() Loaded molecule (%s), with %d atoms, mass %f, and MofI %s."),
				*Mol.Name, Mol.Atoms.Num(), Mol.MolarMass, *PrototypeMolecules[Mol.Name].MomentOfInertia.ToString());
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("ASimulation::InitMoleculeData() Problem loading PDB file %s"), *PDBfile);
		}
	} // loop over files
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMoleculeData() finished."));
}

void ASimulation::InitNumMolecules(FString MoleculeName, int32 NumMolecules)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitNumMolecules(%s) Called."), *MoleculeName);
	if (!this->PrototypeMolecules.Contains(MoleculeName))
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR - ASimulation::AddSolvent(%s) - Not found in PrototypeMolecules List."), *MoleculeName);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddSolvent(%s) - Prototype Molecule Found."), *MoleculeName);

	FVector SubDivisions = CalculateDivisionsForNumMolecules(NumMolecules);
	TArray<FVector> Positions = CalculateSubdivisionPositions(SubDivisions);

	UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddSolvent(%s) Number of Positions Calculated:%d"), *MoleculeName, Positions.Num());

	for (int32 i = 0; i < NumMolecules; i++)
	{
		//Random Molecule Insertion
		//Position = FVector(FMath::RandRange(-1 * CellWidth, CellWidth), FMath::RandRange(-1 * CellWidth, CellWidth), FMath::RandRange(-1 * CellWidth, CellWidth));

		//Insert into subdivided volume
		UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddSolvent(%s) Adding Molecule: %d - Positions[%d]: %s"), *MoleculeName, i, i, *Positions[i].ToString());

		InitMolecule(TEXT("Water"), Positions[i]);
	}
}

bool ASimulation::InitReactionData(FString FileName)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitReactionData() Called - Still needs implementation."));
	return false;
}

void ASimulation::InitSimulation()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitializeSimulation() Called."));

	ContentDir = IPluginManager::Get().FindPlugin(PLUGIN)->GetContentDir();

	RandGen = NewObject<USimRand>();
	RandGen->Init();
	RandGen->SetSimulationData(SimulationData);

	InitData();
	BuildDefaultPrototypes();
}

void ASimulation::InitSimulationCell(float CellWidth, FColor CellColor, bool bTeleportWalls)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitSimulationCell(%f) Called."), CellWidth);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SimulationCell = GetWorld()->SpawnActor<ASimulationCell>(GetActorLocation(), GetActorRotation(), SpawnInfo);
	SimulationCell->InitSimulationCell(CellWidth, bTeleportWalls, SimulationData);
	//	SimulationCell->SetLineThickness(LineThickness);
	SimulationCell->SetShapeColor(CellColor);
	//AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale, this->GetRootComponent());
	SimulationCell->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	SimulationCell->SetActorRelativeLocation(FVector(0.f, 0.f, (CellWidth / 2.f)));
}

void ASimulation::InitSimulationData()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitSimulationData() Called."));
	SimulationData->SetSimulation(this);
	
}

void ASimulation::InitSolvent(FString SolventName)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitSolvent(%s) Called."), *SolventName);
	if (!this->PrototypeMolecules.Contains(SolventName))
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR - ASimulation::InitSolvent(%s) - Not found in PrototypeMolecules List."), *SolventName);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitSolvent(%s) - Prototype Molecule Found."), *SolventName);

	int32 NumMolecules = CalculateNumberOfSolventMolecules(PrototypeMolecules[SolventName].Density, PrototypeMolecules[SolventName].MolarMass);

	InitNumMolecules(SolventName, NumMolecules);
}


//********************************************************************
// Dynamics - Other Functions
//********************************************************************
void ASimulation::ActivateSimulation()
{
	bSimulationActive = true;
}

void ASimulation::CheckCollision()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::CheckCollision() Called - Still needs implementation."));
}

void ASimulation::DeactivateSimulation()
{
	for(AMolecule* Molecule : Molecules)
	{
		Molecule->Freeze();
	}
	bSimulationActive = false;
}

void ASimulation::UpdateSimulation()
{
	//UE_LOG(LogTemp, Warning, TEXT("ASimulation::UpdateSimulation() Called."));

	if(bSimulationActive)
	{
		UE_LOG(LogTemp, Warning, TEXT("ASimulation::UpdateSimulation() Average Molecule Speed:%f"), CalculateAverageMoleculeSpeed());
		UpdateSimulationTemp();
		UpdateForcesOnMolecules();
		bSimulationWasActive = true;
	}
	else if(bSimulationWasActive)
	{
		bSimulationWasActive = false;
		//freeze Simulation
		for (AMolecule* Molecule : Molecules)
		{
			Molecule->Freeze();
		}
	}
	
}

void ASimulation::UpdateSimulationTemp()
{
	//UE_LOG(LogTemp, Warning, TEXT("ASimulation::UpdateSimulationTemperature() Called."));

	float CurrentTemp = CalculateCurrentTemperature();
	float VelocityModifier;
	
	// Check if the molecules are currently frozen
	if (CurrentTemp <= 0.f)
	{
		// check if they should stay frozen
		if (Temperature <= 0.f)
		{
			//UE_LOG(LogTemp, Warning, TEXT("ASimulation::UpdateSimulationTemp() currentTemp <= 0, desired temp <= 0 returning"));
			return;
		}
		// if not initialize their movement
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ASimulation::UpdateSimulationTemp() currentTemp <= 0, desired temp > 0 Initializing impulse."));
			VelocityModifier = FMath::Sqrt(Temperature / SimulationData->GetInitialTemperature());
			for(AMolecule* Molecule : Molecules)
			{
				Molecule->EnablePhysics();
				FVector NewVelocity = Molecule->GetInitialVelocity() * VelocityModifier;
				Molecule->SetVelocity(NewVelocity);
				//add initial rotation
				FVector NewTorque = Molecule->GetInitialTorque() * VelocityModifier;
				Molecule->AddTorque(NewTorque);
			}
			UE_LOG(LogTemp, Warning, TEXT("ASimulation::UpdateSimulationTemp() Initial Velocity Average speed: %f"), CalculateInitialAverageSpeed());
		}
	}
	// If the molecules are not frozen
	else
	{
		//Check if they should be frozen
		if(Temperature <= 0.f)
		{
			//UE_LOG(LogTemp, Warning, TEXT("ASimulation::UpdateSimulationTemp() currentTemp > 0, desired temp <= 0 Freezing Molecules."));
			for(AMolecule* Molecule : Molecules)
			{
				Molecule->Freeze();
			}
		}
		// Otherwise Maintain the desired Temperature
		else
		{
			//Temporarily disabled the thermostat
			//UE_LOG(LogTemp, Warning, TEXT("ASimulation::UpdateSimulationTemp() currentTemp > 0, desired temp > 0 Adding impulse."));
			VelocityModifier = FMath::Sqrt(Temperature / CurrentTemp);
			for(AMolecule* Molecule : Molecules)
			{
				FVector NewVelocity = Molecule->GetCurrentVelocity() * VelocityModifier;
				FVector NewImpulse = NewVelocity - Molecule->GetCurrentVelocity();
				Molecule->AddImpulse(NewImpulse);
			}
			/*
			*/
		}
	}	
}

//********************************************************************
// Dynamics - Utility Functions
//********************************************************************
float ASimulation::CalculateAverageKineticEnergy()
{
	//UE_LOG(LogTemp, Warning, TEXT("ASimulation::CalculateAverageKineticEnergy() Called"));
	float TotalKineticEnergy = CalculateTotalKineticEnergy();
	float AvgKineticEnergy = TotalKineticEnergy / float(Molecules.Num());
	
	//UE_LOG(LogTemp, Warning, TEXT("ASimulation::CalculateAverageKineticEnergy() Total TotalKineticEnergy:%e - NumMolecules:%d - AvgKineticEnergy:%e"), TotalKineticEnergy, Molecules.Num(), AvgKineticEnergy);

	return AvgKineticEnergy;
}

float ASimulation::CalculateCurrentTemperature()
{
	float CurrentTemp = (2.0f / 3.0f) * CalculateAverageKineticEnergy() / USimulationConstants::BOLTZMANN;
	//UE_LOG(LogTemp, Warning, TEXT("ASimulation::CalculateCurrentTemperature() CurrentTemp:%f BOLTZMANN:%e"), CurrentTemp, USimulationConstants::BOLTZMANN);
	return CurrentTemp;
}

float ASimulation::CalculateTotalKineticEnergy()
{
	float TotalKineticEnergy = 0.0f;
	for (AMolecule* Molecule : Molecules)
	{
		TotalKineticEnergy += 0.5 * (Molecule->GetMoleculeMass() * USimulationConstants::DA_TO_KG) * Molecule->GetVelocity().SizeSquared();
		//TotalKineticEnergy += 0.5 * (Molecule->GetMoleculeMass()) * Molecule->GetVelocity().SizeSquared();
	}
	//UE_LOG(LogTemp, Warning, TEXT("ASimulation::CalculateTotalKineticEnergy() TotalKineticEnergy:%e"), TotalKineticEnergy);
	return TotalKineticEnergy;
}

float ASimulation::Convert_C_to_F(float CTemp)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_C_to_F(%f) Called."), CTemp);
	return CTemp * (9.0f / 5.0f) + 32.0f;
}

float ASimulation::Convert_C_to_K(float CTemp)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_C_to_K(%f) Called."), CTemp);
	return CTemp + USimulationConstants::C_TO_K_OFFSET;
}

float ASimulation::Convert_eV_to_J(float eVEnergy)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_eV_to_J() Called"), eVEnergy);
	return eVEnergy * USimulationConstants::EV_TO_J;
}

float ASimulation::Convert_eV_to_kCal(float eVEnergy)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_eV_to_kCal()"), eVEnergy);
	return eVEnergy * USimulationConstants::EV_TO_KCAL;
}

float ASimulation::Convert_F_to_C(float FTemp)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_F_to_C(%f) Called."), FTemp);
	return (FTemp - 32.f) * 5.f / 9.f;
}

float ASimulation::Convert_F_to_K(float FTemp)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_F_to_K(%f) Called."), FTemp);
	return Convert_C_to_K(Convert_F_to_C(FTemp));
}

float ASimulation::Convert_J_to_eV(float JEnergy)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_J_to_eV(%E) Called"), JEnergy);
	return JEnergy * USimulationConstants::J_TO_EV;
}

float ASimulation::Convert_K_to_C(float KTemp)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_K_to_C(%f) Called."), KTemp);
	return KTemp - USimulationConstants::C_TO_K_OFFSET;
}

float ASimulation::Convert_K_to_F(float KTemp)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_K_to_F(%f) Called."), KTemp);
	return Convert_C_to_F(Convert_K_to_C(KTemp));
}

float ASimulation::Convert_kCal_to_eV(float kCalEnergy)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_kCal_to_eV(%E)"), kCalEnergy);
	return kCalEnergy * USimulationConstants::KCAL_TO_EV;
}

float ASimulation::Convert_L_to_pm3(float LVolume)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_L_to_pm3(%E) Called"), LVolume);
	return LVolume * USimulationConstants::L_TO_PM3;
}

float ASimulation::Convert_mL_to_pm3(float mLVolume)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_mL_to_pm3(%E) Called"), mLVolume);
	return mLVolume * USimulationConstants::ML_TO_PM3;
}

float ASimulation::Convert_pm3_to_L(float pm3Volume)
{
	float mLVolume = pm3Volume * USimulationConstants::PM3_TO_L;
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_pm3_to_L(%E) Called: %E"), pm3Volume, mLVolume);
	return mLVolume;
}

float ASimulation::Convert_pm3_to_mL(float pm3Volume)
{
	float mLVolume = pm3Volume * USimulationConstants::PM3_TO_ML;
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_pm3_to_mL(%E) Called: %E"), pm3Volume, mLVolume);
	return mLVolume;
}

void ASimulation::SetHideCollisionSpheres()
{
	for (AMolecule* Molecule : Molecules)
	{
		Molecule->SetHideCollisionSpheres();
	}
}

void ASimulation::SetHideCoM()
{
	for (AMolecule* Molecule : Molecules)
	{
		Molecule->SetHideCoM();
	}
}

void ASimulation::SetHideInteractionSpheres()
{
	for (AMolecule* Molecule : Molecules)
	{
		Molecule->SetHideInteractionSpheres();
	}
}

void ASimulation::SetHideSpline()
{
	for (AMolecule* Molecule : Molecules)
	{
		Molecule->SetHideSpline();
	}
}

void ASimulation::SetShowCollisionSpheres()
{
	for (AMolecule* Molecule : Molecules)
	{
	Molecule->SetShowCollisionSpheres();
	}
}

void ASimulation::SetShowCoM()
{
	for (AMolecule* Molecule : Molecules)
	{
		Molecule->SetShowCoM();
	}
}

void ASimulation::SetShowSpline()
{
	for (AMolecule* Molecule : Molecules)
	{
		Molecule->SetShowSpline();
	}
}

void ASimulation::SetShowInteractionSpheres()
{
	for (AMolecule* Molecule : Molecules)
	{
		Molecule->SetShowInteractionSpheres();
	}
}

void ASimulation::SetRenderBallStick()
{
	for (AMolecule* Molecule : Molecules)
	{
		Molecule->SetRenderBallStick();
	}
}

void ASimulation::SetRenderHidden()
{
	for (AMolecule* Molecule : Molecules)
	{
		Molecule->SetRenderHidden();
	}
}

void ASimulation::SetRenderLinear()
{
	for (AMolecule* Molecule : Molecules)
	{
		Molecule->SetRenderLinear();
	}
}

void ASimulation::SetRenderSpaceFilling()
{
	for (AMolecule* Molecule : Molecules)
	{
		Molecule->SetRenderSpaceFilling();
	}
}

//********************************************************************
// Dynamics - Setter Functions
//********************************************************************
void ASimulation::SetSimulationCellVolume(float Volume)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::SetSimulationCellVolume(%f) Called."), Volume);
	SimulationCell->SetVolume(Volume);
}

void ASimulation::SetSimulationCellWidth(float Width)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::SetSimulationCellWidth(%f) Called."), Width);
	SimulationCell->SetWidth(Width);
}

void ASimulation::SetSimulationTemp(float temp)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::SetSimulationTemp(%f) Called - Still needs implementation."), temp);
	Temperature = temp;
}

void ASimulation::SetSoluteConcentration(float NewConcentration)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::SetSoluteConcentration() Called - Still needs implementation."));
}

void ASimulation::SetSolventModifier(float NewSolventModifier)
{
	SolventModifier = NewSolventModifier;
}

void ASimulation::SetTimeScale(float ScaleFactor)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::SetTimeScale(%f) Called."), ScaleFactor);
	TimeScale = ScaleFactor;
}

//********************************************************************
// C++ Private Functions
//********************************************************************
//********************************************************************
// Adder Functions
//********************************************************************
void ASimulation::AddHydrogenBond()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddHydrogenBond() Called - Still needs implementation."));
}

void ASimulation::AddReaction()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddReaction() Called - Still needs implementation."));
}

//********************************************************************
// Other Functions
//********************************************************************

void ASimulation::BuildDefaultPrototypes()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() Called."));

	FMoleculePrototype Water;

	UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() MoleculePrototype Name:%s - Formula:%s - Density:%f - MolarMass:%f NumAtoms:%d"), *Water.Name, *Water.Formula, Water.Density, Water.MolarMass, Water.Atoms.Num());

	Water.Name = TEXT("water");
	Water.Formula = TEXT("H2O");
	Water.Density = 997.f;

	UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() Number of prototypeAtoms before add: %d."), PrototypeMolecules.Num());
	if (PrototypeMolecules.Contains(Water.Name)) {
		PrototypeMolecules[Water.Name].Formula = Water.Formula;
		PrototypeMolecules[Water.Name].Density = Water.Density;
		UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() Water alread loaded.  Density is now: %f"), PrototypeMolecules[Water.Name].Density);
	} else {
		Water.MolarMass = 18.01528f;
		FAtomPrototype AtomO;
		AtomO.Symbol = TEXT("O");
		AtomO.Position = FVector(000.0, 000.0, 000.0);
		Water.Atoms.Add(AtomO);
		FAtomPrototype AtomH1;
		AtomH1.Symbol = TEXT("H");
		AtomH1.Position = FVector(96.6, 0.0, -8.5);
		Water.Atoms.Add(AtomH1);
		FAtomPrototype AtomH2;
		AtomH2.Symbol = TEXT("H");
		AtomH2.Position = FVector(-35.4, -84.0, -33.3);
		Water.Atoms.Add(AtomH2);
	
		UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() MoleculePrototype Name:%s - Formula:%s - Density:%f - MolarMass:%f NumAtoms:%d"), *Water.Name, *Water.Formula, Water.Density, Water.MolarMass, Water.Atoms.Num());
	
		PrototypeMolecules.Add(Water.Name, Water);
		UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() Number of prototypeAtoms:%d."), PrototypeMolecules.Num());
	}
	
}

float ASimulation::CalculateAverageMoleculeSpeed()
{
	float TotalSpeed = 0.0f;
	for(AMolecule* Molecule : Molecules)
	{
		TotalSpeed += Molecule->GetSpeed();
	}
	float NumMolecules = float(Molecules.Num());
	float AvgSpeed = TotalSpeed / NumMolecules;
	//UE_LOG(LogTemp, Warning, TEXT("ASimulation::CalculateAverageMoleculeSpeed() TotalSpeed:%f - Molecules.Num():%f - AverageSpeed:%f"), TotalSpeed, NumMolecules, AvgSpeed);
	return AvgSpeed;
}


FVector ASimulation::CalculateDivisionsForNumMolecules(int32 NumAtoms)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::CalculateDivisionsForNumMolecules(%d) Called"), NumAtoms);
	FVector SubDivisions = FVector(1.f);
	int32 NumDivisions = SubDivisions.X * SubDivisions.Y * SubDivisions.Z;
	int32 SubDivisionIndex = 0;
	UE_LOG(LogTemp, Warning, TEXT("------%s : %d"), *SubDivisions.ToString(), NumDivisions);
	//While there are not enough subdivisions for the numAtoms, iterate through the x,y,z to add an additional subdivision until there are enough compartments. 
	while(NumDivisions < NumAtoms)
	{
		SubDivisions[SubDivisionIndex] += 1.0f;
		if (SubDivisionIndex < 2)
			SubDivisionIndex++;
		else
			SubDivisionIndex = 0;
		NumDivisions = SubDivisions.X * SubDivisions.Y * SubDivisions.Z;
		UE_LOG(LogTemp, Warning, TEXT("------%s : %d"), *SubDivisions.ToString(), NumDivisions);
	}
	return SubDivisions;
}

float ASimulation::CalculateInitialAverageSpeed()
{
	float TotalInitialSpeed = 0.0f;
	for (AMolecule* Molecule : Molecules)
	{
		TotalInitialSpeed += Molecule->GetInitialVelocity().Size();
	}
	float NumMolecules = float(Molecules.Num());
	float AvgSpeed = TotalInitialSpeed / NumMolecules;
	//UE_LOG(LogTemp, Warning, TEXT("ASimulation::CalculateInitialAverageSpeed() TotalInitialSpeed:%f - Molecules.Num():%f - InitialAverageSpeed:%f"), TotalInitialSpeed, NumMolecules, AvgSpeed);
	return AvgSpeed;
}

float ASimulation::CalculateNetForceForMolecule()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::CalculateNetForceForMolecule() Called - Still needs implementation."));
	return 0.0f;
}

bool ASimulation::CheckReaction()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::CheckReaction() Called - Still needs implementation."));
	return false;
}

int32 ASimulation::CalculateNumberOfSolventMolecules(float Density, float MolarMass)
{
	float Atoms = (((Density * 1e-33) / MolarMass) * USimulationConstants::AVOGADRO) * GetSimulationVolume();
	Atoms = Atoms * SolventModifier;
	//kg to g and m^3 to pm^3
	int32 NumAtoms = FMath::CeilToInt(Atoms);

	UE_LOG(LogTemp, Warning, TEXT("ASimulation::CalculateNumberOfSolventMolecules(%f, %f) Called: %E, %d"), Density, MolarMass, Atoms, NumAtoms);
	return NumAtoms;
}

FVector ASimulation::CalculateSolventMoleculePosition(int32 CurrentCount, int TotalNum)
{
	return FVector();
}


TArray<FVector> ASimulation::CalculateSubdivisionPositions(FVector& SubDivisions)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::CalculateSubdivisionPositions(%s) called."), *SubDivisions.ToString());
	TArray<FVector> Positions;
	float BaseWidth = GetSimulationCellWidth();
	int32 NumDivisions = SubDivisions.X * SubDivisions.Y * SubDivisions.Z;
	FVector SubBoxDimensions = FVector(BaseWidth/SubDivisions.X, BaseWidth / SubDivisions.Y, BaseWidth / SubDivisions.Z);
	FVector CurrentPosition = FVector(0.f);
	//Calculate Z Position
	for(int32 ZIndex = 1; ZIndex <= SubDivisions.Z; ZIndex++)
	{
		CurrentPosition.Z = (SubBoxDimensions.Z * ZIndex) - (SubBoxDimensions.Z /2);
		for(int32 YIndex = 1; YIndex <= SubDivisions.Y; YIndex++)
		{
			CurrentPosition.Y = (SubBoxDimensions.Y * YIndex) - (SubBoxDimensions.Y / 2);
			for (int32 XIndex = 1; XIndex <= SubDivisions.X; XIndex++)
			{
				CurrentPosition.X = (SubBoxDimensions.X * XIndex) - (SubBoxDimensions.X / 2);

				//likely need to add adjustment to position for cube offset to origin in bottom center to fit in cube
				Positions.Add(FVector(CurrentPosition.X - (BaseWidth / 2), CurrentPosition.Y - (BaseWidth / 2), CurrentPosition.Z - (BaseWidth / 2)));
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("SubBoxDimensions: %s"), *SubBoxDimensions.ToString());
	for(FVector Position : Positions)
	{
		UE_LOG(LogTemp, Warning, TEXT("Position: %s"), *Position.ToString());
	}
	return Positions;
}


void ASimulation::ProcessHBonds()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::ProcessHBonds() Called - Still needs implementation."));
}

void ASimulation::SetReactionDistance()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::SetReactionDistance() Called - Still needs implementation."));
}

//********************************************************************
// Remover Functions
//********************************************************************
void ASimulation::RemoveHydrogenBond()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::RemoveHydrogenBond() Called - Still needs implementation."));
}

void ASimulation::RemoveMolecule(AMolecule* Target)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::RemoveMolecule() Called - Still needs implementation."));
}

void ASimulation::RemoveReaction()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::RemoveReaction() Called - Still needs implementation."));
}

//********************************************************************
// Update Functions
//********************************************************************
void ASimulation::UpdateForcesOnMolecules()
{
	//UE_LOG(LogTemp, Warning, TEXT("ASimulation::UpdateForcesOnMolecules() Called."));
	for(AMolecule* Molecule : Molecules)
	{
		Molecule->UpdateIntermolecularForces();
	}
}

/*
void ASimulation::UpdateSystemEnergy()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::UpdateSystemEnergy() Called - Still needs implementation."));
}
*/

