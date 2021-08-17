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
#include "SimRand.h"


/*
// Sets default values
ASimulation::ASimulation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASimulation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASimulation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

//********************************************************************
// Physical Constants
//********************************************************************

/** Avogadro's Number, in mol^-1 */
const float ASimulation::AVOGADRO = 6.0221409e23;

/** Boltzmann's Constant (k_B or just k), in J/K */
const float ASimulation::BOLTZMANN = 1.38064852e-23;

/** Conversion from atomic mass units to kg */
const float ASimulation::KG_PER_U = 1.66054e-27;


//********************************************************************
// UE4 Default Functions
//********************************************************************
// Sets default values
ASimulation::ASimulation()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::ASimulation() Called."));
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Default simulation values.
	SystemEnergy = 0;
	SystemEnergyTolerance = 0.01; // FIXME: This is an arbitrary tolerance value!
	Temperature = 298.15;
	TimeScale = 1;
}

// Called when the game starts or when spawned
void ASimulation::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::BeginPlay() Called."));
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

float ASimulation::GetSimulationEnergy()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::GetSimulationEnergy() Called: %E."), SystemEnergy);
	return SystemEnergy;
}

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
void ASimulation::InitializeSimulation()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitializeSimulation() Called - Incomplete implementation."));

	ContentDir = IPluginManager::Get().FindPlugin(PLUGIN)->GetContentDir();

	UE_LOG(LogTemp, Warning, TEXT("ASimulation's Location is: %s"), *GetActorLocation().ToString());

	RandGen = NewObject<USimRand>();
	RandGen->Init();

	LoadChemData();
	BuildDefaultPrototypes();
	
	AddSolvent("Water");

	//EnableMoleculePhysics();
}

void ASimulation::InitInteractionRadius(float Radius)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitInteractionRadius() Called - Still needs implementation."));
}

bool ASimulation::InitMoleculeData(FString FileName)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitMoleculeData() Called - Still needs implementation."));
	return false;
}

bool ASimulation::InitReactionData(FString FileName)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitReactionData() Called - Still needs implementation."));
	return false;
}

void ASimulation::InitSimulationCell(float CellWidth, FColor CellColor)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitSimulationCell(%f) Called."), CellWidth);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SimulationCell = GetWorld()->SpawnActor<ASimulationCell>(GetActorLocation(), GetActorRotation(), SpawnInfo);
	SimulationCell->InitVolume(CellWidth);
	//	SimulationCell->SetLineThickness(LineThickness);
	SimulationCell->SetShapeColor(CellColor);
	//AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale, this->GetRootComponent());
	SimulationCell->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	SimulationCell->SetActorRelativeLocation(FVector(0.f, 0.f, (CellWidth / 2.f)));
}

void ASimulation::InitSolvent(AMolecule* Solvent)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::InitSolvent() Called - Still needs implementation."));
}

//********************************************************************
// Dynamics - Other Functions
//********************************************************************
void ASimulation::CheckCollision()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::CheckCollision() Called - Still needs implementation."));
}

void ASimulation::UpdateSimulation()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::UpdateSimulation() Called - Still needs implementation."));
}

//********************************************************************
// Dynamics - Utility Functions
//********************************************************************
float ASimulation::Convert_C_to_F(float CTemp)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_C_to_F(%f) Called."), CTemp);
	return CTemp * (9 / 5) + 32;
}

float ASimulation::Convert_C_to_K(float CTemp)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_C_to_K(%f) Called."), CTemp);
	return CTemp + 273.15f;
}

float ASimulation::Convert_eV_to_J(float eVEnergy)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_eV_to_J() Called"), eVEnergy);
	return eVEnergy * 1.602176634e-19f;
}

float ASimulation::Convert_eV_to_kCal(float eVEnergy)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_eV_to_kCal()"), eVEnergy);
	return eVEnergy * 3.826732796e-23f;
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
	return JEnergy / 1.602176634e-19f;
}

float ASimulation::Convert_K_to_C(float KTemp)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_K_to_C(%f) Called."), KTemp);
	return KTemp - 273.15f;
}

float ASimulation::Convert_K_to_F(float KTemp)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_K_to_F(%f) Called."), KTemp);
	return Convert_C_to_F(Convert_K_to_C(KTemp));
}

float ASimulation::Convert_kCal_to_eV(float kCalEnergy)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_kCal_to_eV(%E)"), kCalEnergy);
	return kCalEnergy / 3.826732796e-23f;
}

float ASimulation::Convert_L_to_pm3(float LVolume)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_L_to_pm3(%E) Called"), LVolume);
	return LVolume * 1e+33f;
}

float ASimulation::Convert_mL_to_pm3(float mLVolume)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_mL_to_pm3(%E) Called"), mLVolume);
	return mLVolume * 1e+30f;
}

float ASimulation::Convert_pm3_to_L(float pm3Volume)
{
	float mLVolume = pm3Volume * 1e-33;
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_pm3_to_L(%E) Called: %E"), pm3Volume, mLVolume);
	return mLVolume;
}

float ASimulation::Convert_pm3_to_mL(float pm3Volume)
{
	float mLVolume = pm3Volume * 1e-30;
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::Convert_pm3_to_mL(%E) Called: %E"), pm3Volume, mLVolume);
	return mLVolume;
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

void ASimulation::AddMolecule(FString MoleculeName, FVector Position)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddMolecule(%s) Called."), *MoleculeName);
	
	FString NumberedName = FString(TEXT("Molecule-"));
	NumberedName += FString::FromInt(Molecules.Num());
	NumberedName += FString(TEXT("-"));
	NumberedName += MoleculeName;
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = SimulationCell;
	SpawnInfo.Name = *NumberedName;
	AMolecule* NewMolecule = GetWorld()->SpawnActor<AMolecule>(GetActorLocation(), GetActorRotation(), SpawnInfo);
	NewMolecule->SetActorLabel(*NumberedName);
	FRotator RandomRotation = FRotator(FMath::FRandRange(-180.f, 180.f), FMath::FRandRange(-180.f, 180.f), FMath::FRandRange(-180.f, 180.f));
	NewMolecule->SetActorRotation(RandomRotation);

	if (!this->PrototypeMolecules.Contains(TEXT("Water")))
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR - ASimulation::AddMolecule(%s) - Not found in PrototypeMolecules List."), *MoleculeName);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddMolecule(%s) - Prototype Molecule Found."), *MoleculeName);

	NewMolecule->InitMolecule(PrototypeMolecules[MoleculeName], Molecules.Num(), AtomDataTable);

	//Add Initial movement to molecule
	//float MaxSpeed = 0.f;
	//FVector NewVelocity = FVector(FMath::RandRange(-1 * MaxSpeed, MaxSpeed), FMath::RandRange(-1 * MaxSpeed, MaxSpeed), FMath::RandRange(-1 * MaxSpeed, MaxSpeed));
	FVector NewVelocity = RandGen->RandV_MaxwellBoltzmann(PrototypeMolecules[MoleculeName].MolarMass, Temperature);
	NewMolecule->SetVelocity(NewVelocity);
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddMolecule(%s) - Name: %s. Molecule Velocity: %s."), *MoleculeName, *NewMolecule->GetName(), *NewVelocity.ToString());
	
	NewMolecule->AttachToActor(SimulationCell, FAttachmentTransformRules::SnapToTargetIncludingScale);
	NewMolecule->SetActorRelativeLocation(Position);
	Molecules.Add(NewMolecule);
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddMolecule(%s) Completed."), *MoleculeName);
}

void ASimulation::AddReaction()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddReaction() Called - Still needs implementation."));
}

void ASimulation::AddSolvent(FString MoleculeName)
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddSolvent(%s) Called."), *MoleculeName);
	if (!this->PrototypeMolecules.Contains(MoleculeName))
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR - ASimulation::AddSolvent(%s) - Not found in PrototypeMolecules List."), *MoleculeName);
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddSolvent(%s) - Prototype Molecule Found."), *MoleculeName);
	
	int32 NumAtoms = CalculateNumberOfSolventMolecules(PrototypeMolecules[MoleculeName].Density, PrototypeMolecules[MoleculeName].MolarMass);
	//NumAtoms = 1;
	
	FVector SubDivisions = CalculateDivisionsForNumMolecules(NumAtoms);
	TArray<FVector> Positions = CalculateSubdivisionPositions(SubDivisions);

	UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddSolvent(%s) Number of Positions Calculated:%d"), *MoleculeName, Positions.Num());
	
	for (int32 i = 0; i < NumAtoms; i++)
	{
		//Random Molecule Insertion
		//Position = FVector(FMath::RandRange(-1 * CellWidth, CellWidth), FMath::RandRange(-1 * CellWidth, CellWidth), FMath::RandRange(-1 * CellWidth, CellWidth));

		//Insert into subdivided volume
		UE_LOG(LogTemp, Warning, TEXT("ASimulation::AddSolvent(%s) Adding Molecule: %d - Positions[%d]: %s"), *MoleculeName, i, i, *Positions[i].ToString());

		AddMolecule(TEXT("Water"), Positions[i]);
	//	AddMolecule(TEXT("Water"), FVector(0.f));
	}

}

//********************************************************************
// Other Functions
//********************************************************************
//void ASimulation::AdjustSystemEnergy()
//{
//	UE_LOG(LogTemp, Warning, TEXT("ASimulation::AdjustSystemEnergy() Called - Still needs implementation."));
//}

void ASimulation::BuildDefaultPrototypes()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() Called."));
	FMoleculePrototype Water;
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() MoleculePrototype Name:%s - Formula:%s - Density:%f - MolarMass:%f NumAtoms:%d"), *Water.Name, *Water.Formula, Water.Density, Water.MolarMass, Water.Atoms.Num());
	Water.Name = TEXT("Water");
	Water.Formula = TEXT("H2O");
	Water.Density = 997.f;
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
	
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() Number of prototypeAtoms:%d."), PrototypeMolecules.Num());
	this->PrototypeMolecules.Add(TEXT("Water"), Water);
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() Number of prototypeAtoms:%d."), PrototypeMolecules.Num());
	
	
	/*
	FString Name = TEXT("Water");
	FString MolecularFormula = TEXT("H2O");

	TArray<AAtom*> WaterAtoms;
	TArray<ABond*> WaterBonds;

	AAtom* NewAtom;
	AAtom* O;
	AAtom* H1;
	AAtom* H2;
	ABond* NewBond;
	AMolecule* WaterMolecule;

	UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() Build Default Atom Prototypes."));
	// Define atom prototypes.
	NewAtom = NewObject<AAtom>();
	NewAtom->InitAtomPrototype(
		TEXT("Hydrogen"),
		TEXT("H"),
		TEXT("HW"), // Hydrogen in water
		FColor::White,
		1.00794,
		0,
		0.37,
		0.0001,
		0.0000);
	this->PrototypeAtoms.Add(NewAtom->GetName(), NewAtom);
	NewAtom = NewObject<AAtom>();
	NewAtom->InitAtomPrototype(
		TEXT("Oxygen"),
		TEXT("O"),
		TEXT("OW"), // Hydrogen in water
		FColor::Red,
		15.9994,
		0,
		0.73,
		1.7683,
		0.1520);
	this->PrototypeAtoms.Add(NewAtom->GetName(), NewAtom);

	UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() Build Water Atoms."));
	// Water atoms.
	O = NewObject<AAtom>();
	O->InitAtomCopy(this->PrototypeAtoms[TEXT("Oxygen")], FVector(0.53890, 0.65566, 0.00000));
	WaterAtoms.Add(O);
	H1 = NewObject<AAtom>();
	H1->InitAtomCopy(this->PrototypeAtoms[TEXT("Hydrogen")], FVector(1.50890, 0.65566, 0.00000));
	WaterAtoms.Add(H1);
	H2 = NewObject<AAtom>();
	H2->InitAtomCopy(this->PrototypeAtoms[TEXT("Hydrogen")], FVector(0.21557, 1.56969, -0.03013));
	WaterAtoms.Add(H2);

	UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() Build Water Bonds."));
	// Water bonds.
	NewBond = NewObject<ABond>();
	NewBond->InitBond(
		TEXT("O-H1"),
		TEXT("Single"),
		0.9572,
		553.0,
		FColor::Blue,
		O,
		H1);
	WaterBonds.Add(NewBond);
	NewBond = NewObject<ABond>();
	NewBond->InitBond(
		TEXT("O-H2"),
		TEXT("Single"),
		0.9572,
		553.0,
		FColor::Blue,
		O,
		H2);
	WaterBonds.Add(NewBond);
	
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::BuildDefaultPrototypes() Build Water Molecules."));
	WaterMolecule = NewObject<AMolecule>();
	WaterMolecule->InitMoleculePrototype(
		Name,
		MolecularFormula,
		WaterAtoms,
		WaterBonds,
		FVector(0, 0, 0)
	);

	//UE_LOG(LogTemp, Warning, TEXT("ProtoypeMolecule Name: %s"), *Name);
	//UE_LOG(LogTemp, Warning, TEXT("ProtoypeMolecule Atoms: %d"), WaterMolecule->GetNumAtoms());
	for(int32 i = 0; i < WaterMolecule->GetNumAtoms(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("Atom[%d]: %s"), i, *WaterMolecule->PrintAtom(i));
	}
	this->PrototypeMolecules.Add(TEXT("Water"), WaterMolecule);
	*/
}

void ASimulation::EnableMoleculePhysics()
{
	/*
	for(int32 i = 0; i < Molecules.Num(); i++)
	{
		Molecules[i]->EnablePhysics();
	}
	 */

	for(AMolecule* Molecule : Molecules)
	{
		Molecule->EnablePhysics();
	}
}


void ASimulation::LoadChemData() {
	FString ChemDataDirName = TEXT("ChemData");
	FString ChemDataDir = ContentDir + TEXT("/") + ChemDataDirName;

	////////////////////////////////////////
	// Load atom data.

	FString AtomDataFile = ChemDataDir + TEXT("/AtomData.csv");
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::LoadChemData called.  Huzzah!"));
	if (!FPaths::DirectoryExists(ChemDataDir)) {
		UE_LOG(LogTemp, Warning, TEXT("LoadChemData Could not find dir %s"), *ChemDataDir);
		return;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("LoadChemData Found dir %s"), *ChemDataDir);
	}
	if (!FPaths::FileExists(AtomDataFile)) {
		UE_LOG(LogTemp, Warning, TEXT("LoadChemData Could not find file %s"), *AtomDataFile);
		return;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("LoadChemData Found file %s"), *AtomDataFile);
	}

	// Create a new data table based on the atom data row struct.
	AtomDataTable = NewObject<UDataTable>();
	AtomDataTable->RowStruct = FAtomData::StaticStruct();

	// Load the atom data file into a single string, and import it into the data table.
	FString FileContent;
	TArray<FString> Problems;
	bool success;
	success = FFileHelper::LoadFileToString(FileContent, *AtomDataFile);
	//UE_LOG(LogTemp, Warning, TEXT("LoadChemData LoadFileToString status: %s, length: %d"), (success ? TEXT("true") : TEXT("false")), FileContent.Len());
	Problems = AtomDataTable->CreateTableFromCSVString(FileContent);
	if (Problems.Num() > 0) {
		UE_LOG(LogTemp, Warning, TEXT("LoadChemData  %d problems loading AtomDataTable."), Problems.Num());
		for (int i = 0; i < Problems.Num(); ++i) {
			UE_LOG(LogTemp, Warning, TEXT("p%d: %s"), i, *Problems[i]);
		}
		return;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("LoadChemData Successfully loaded AtomDataTable ."))
	}

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
	UE_LOG(LogTemp, Warning, TEXT("LoadChemData Searching %d folders for PDB files."), SearchDirs.Num());


	for (int idir = 0; idir < SearchDirs.Num(); ++idir) {
		PartialFileList.Empty();
		FString SearchDir = SearchDirs[idir];
		FString fullpath;
		if (FPaths::DirectoryExists(SearchDir)) {
			fullpath = SearchDir + TEXT("/") + PDBwildcard;
			FileManager.FindFiles(PartialFileList, *fullpath, true, false);
			UE_LOG(LogTemp, Warning, TEXT("LoadChemData Found %d PDB files in folder %s"), PartialFileList.Num(), *fullpath);
			for (int i = 0; i < PartialFileList.Num(); ++i) {
				PartialFileList[i] = SearchDir + TEXT("/") + PartialFileList[i];
			}
			FileList += PartialFileList;
		} else {
			UE_LOG(LogTemp, Warning, TEXT("No ChemData folder at %s"), *SearchDir);
		}
	} // loop over search dirs

	UE_LOG(LogTemp, Warning, TEXT("LoadChemData Found %d PDB files."), FileList.Num());
	// Read the molecule data from each PDB file.  (We'll be ignoring a lot of what's in there.)
	TArray<FString> MolNames; // For checking for duplicates.
	FString MolName, Record, Symbol, Xstr, Ystr, Zstr;
	int32 PathIdx, Serial;
	for (int ifile = 0; ifile < FileList.Num(); ++ifile) {
		//FString PDBfile = ChemDataDir + TEXT("/") + FileList[ifile];
		FString PDBfile = FileList[ifile];
		PDBfile.FindLastChar('/', PathIdx);
		MolName = PDBfile.Right(PDBfile.Len() - PathIdx - 1);

		// If we've already loaded a file with this molecule name, skip it.
		if (MolNames.Contains(MolName)) {
			UE_LOG(LogTemp, Warning, TEXT("LoadChemData Molecule %s already loaded!  Skipping file %s"), *MolName, *PDBfile);
			continue;
		}

		UE_LOG(LogTemp, Warning, TEXT("LoadChemData Loading molecule %s from file %s"), *MolName, *PDBfile);
		MolNames.Add(MolName);

		TArray<FString> lines;
		success = FFileHelper::LoadFileToStringArray(lines, *PDBfile);
		if (success) {
			UE_LOG(LogTemp, Warning, TEXT("LoadChemData Successfully loaded PDB file %s"), *PDBfile);
			FMoleculePrototype Mol;
			Mol.Name = FileList[ifile].Replace(TEXT(".pdb"), TEXT(""));
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
					FAtomData *AtomAData = nullptr; 
					FAtomData *AtomBData = nullptr;
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
									AtomAData = AtomDataTable->FindRow<FAtomData>(FName(*AtomA.Symbol), "");
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
								UE_LOG(LogTemp, Warning, TEXT("LoadChemData ERROR! Serial number not found reading line %d of %s!"), (iline + 1), *PDBfile);
								break;
							}

							// Calculate the bond length and compare to the expected lengths for different
							// bond types.
							// (This would be much better code if the lengths for bond types were stored in an array for each atom, but I (Rob) don't think that the data table loader can do that.)
							// Note that for atoms that can't make double/triple bonds (like hydrogen), those bond lengths are set to 0.  That _should_ mean the single-bond length will always be the closest to the actual bond length and we don't have to explicitly check, unless something goes horribly wrong...
							AtomB = Mol.Atoms[IndexB];
							float BondLength = FVector::Dist(AtomA.Position, AtomB.Position);
							AtomBData = AtomDataTable->FindRow<FAtomData>(FName(*AtomB.Symbol), "");
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
							UE_LOG(LogTemp, Warning, TEXT("LoadChemData Constructed order %d bond between atoms %d and %d."), BondOrder, Bond.IndexA, Bond.IndexB);

							// Store the bond data!
							Mol.Bonds.Push(Bond);
						}
					} // Loop over target atoms in CONECT row.
				} // if chain for record type
			} // Finished reading PDB file.
			
			// Calculate molar mass and centre of mass of the molecule.
			float Mass = 0;
			FVector CM(0);
			for (int iatom = 0; iatom < Mol.Atoms.Num(); ++iatom) {
				FAtomData* AtomData = AtomDataTable->FindRow<FAtomData>(FName(*Mol.Atoms[iatom].Symbol), "");
				if (AtomData != nullptr) {
					UE_LOG(LogTemp, Warning, TEXT("LoadChemData Table has atom %s with mass %f."),
						*Mol.Atoms[iatom].Symbol, AtomData->Mass);
					Mass += AtomData->Mass;
					CM += AtomData->Mass * Mol.Atoms[iatom].Position;
				}
			}
			CM = CM / Mass;
			Mol.MolarMass = Mass;
			Mol.Density = -1;

			// Shift atom positions to put the coordinate origin at the centre of mass.
			for (int iatom = 0; iatom < Mol.Atoms.Num(); ++iatom) {
				Mol.Atoms[iatom].Position -= CM;
			}

			UE_LOG(LogTemp, Warning, TEXT("LoadChemData Loaded molecule (%s), with %d atoms and mass %f."),
				*Mol.Name, Mol.Atoms.Num(), Mol.MolarMass);

			PrototypeMolecules.Add(Mol.Name, Mol);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("LoadChemData Problem loading PDB file %s"), *PDBfile);
		}
	} // loop over files


	UE_LOG(LogTemp, Warning, TEXT("LoadChemData finished."));

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
	float Atoms = (((Density * 1e-33) / MolarMass) * AVOGADRO) * GetSimulationVolume();
	//kg to g and m^3 to pm^3
	int32 NumAtoms = FMath::Floor(Atoms);

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
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::UpdateForcesOnMolecules() Called - Still needs implementation."));
}

void ASimulation::UpdateSystemEnergy()
{
	UE_LOG(LogTemp, Warning, TEXT("ASimulation::UpdateSystemEnergy() Called - Still needs implementation."));
}

