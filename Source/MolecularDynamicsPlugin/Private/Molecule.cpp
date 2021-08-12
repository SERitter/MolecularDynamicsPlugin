// Fill out your copyright notice in the Description page of Project Settings.


#include "Molecule.h"


AMolecule::AMolecule()
{
	CenterOfMassIndicator = CreateDefaultSubobject<USphereComponent>(TEXT("CenterOfMass"));

	SetRootComponent(CenterOfMassIndicator);
	CenterOfMassIndicator->SetHiddenInGame(true);
	CenterOfMassIndicator->SetSphereRadius(10.f);
}

void AMolecule::InitMolecule(FMoleculePrototype& Prototype, int32 Index, UDataTable* AtomDataTable)
{
	UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule() MoleculePrototype Name:%s - Formula:%s - Density:%f - MolarMass:%f NumAtoms:%d"), *Prototype.Name, *Prototype.Formula, Prototype.Density, Prototype.MolarMass, Prototype.Atoms.Num());
	this->MoleculeName = Prototype.Name;
	this->MoleculeFormula = Prototype.Formula;
	this->MoleculeIndex = Index;

	UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule(%s) Spawning and Initializing %d Atoms."),*Prototype.Name, Prototype.Atoms.Num());

	for (int32 i = 0; i < Prototype.Atoms.Num(); i++)
	{
		//Prototype.Atoms[i]
		UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule(%s) Atom[%d] Symbol:%s Position:%s"), *Prototype.Name, i, *Prototype.Atoms[i].Symbol, *Prototype.Atoms[i].Position.ToString());

		FString NumberedName = FString(TEXT("Molecule-"));
		NumberedName += FString::FromInt(Index);
		NumberedName += FString(TEXT("-"));	
		NumberedName += *Prototype.Atoms[i].Symbol;
		NumberedName += FString::FromInt(Atoms.Num());
		
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		SpawnInfo.Name = *NumberedName;
		AAtom* SpawnedAtom = GetWorld()->SpawnActor<AAtom>(GetActorLocation(), GetActorRotation(), SpawnInfo);
		SpawnedAtom->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		SpawnedAtom->SetActorLabel(*NumberedName);
		SpawnedAtom->SetActorRelativeLocation(Prototype.Atoms[i].Position);

		UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule() Attempting to access AtomData Table: %s"), *Prototype.Atoms[i].Symbol);
		FName Symbol = FName(Prototype.Atoms[i].Symbol);
		FAtomData* AtomData = AtomDataTable->FindRow<FAtomData>(Symbol, "");
		UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule() ***ATOM*** m=%f, r=%f"), AtomData->Mass, AtomData->Radius);
		SpawnedAtom->InitAtom(AtomData, Prototype.Atoms[i].Symbol, i);

		Atoms.Add(SpawnedAtom);
	}
}

/*
void AMolecule::InitAtoms()
{
	UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitAtoms() Attaching %d Atoms to %s:%s:CoM."), this->Atoms.Num(),*this->GetActorLabel(), *this->GetName());

	//TArray<AAtom*> SpawnedAtoms;
	
	//for (int32 i = 0; i < this->Atoms.Num(); i++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%d - Attempting to spawn and attach %s to %s:%s at position %s"), i, *this->Atoms  [i]->GetName(), *this->GetActorLabel(), *this->GetName(), *this->Atoms[i]->GetPosition().ToString());
		//FActorSpawnParameters SpawnInfo;
		//SpawnInfo.Owner = this;
		//SpawnInfo.Name = *this->Atoms[i]->GetName();
		//AAtom* SpawnedAtom = GetWorld()->SpawnActor<AAtom>(GetActorLocation(), GetActorRotation(), SpawnInfo);
		//SpawnedAtom->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
		//SpawnedAtom->SetActorRelativeLocation(this->Atoms[i]->GetPosition());
		//SpawnedAtom->InitAtomExactCopy(this->Atoms[i]);
		//SpawnedAtoms.Add(SpawnedAtom);
	}

	//Atoms = SpawnedAtoms;
	//UE_LOG(LogTemp, Warning, TEXT("Completed Spawn and attachment"));
}
*/

// AMolecule::AMolecule(FString Name, FString MolecularFormula, TArray<AAtom*> Atoms, TArray<ABond*> Bonds,
// 	FVector DipoleMoment, FVector Position, FVector Velocity, FVector Orientation, FVector AngularVelocity)
// {
// }

/*
void AMolecule::InitMoleculePrototype(FString NewName, FString NewMolecularFormula, TArray<AAtom*> NewAtoms, TArray<ABond*> NewBonds, FVector NewDipoleMoment)
{
	UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMoleculePrototype() Called."));
	int32 i;

	//this->Rename(*NewName);
	this->Name = NewName;
	this->MolecularFormula = NewMolecularFormula;
	this->DipoleMoment = NewDipoleMoment;

	// This makes new copies of the arrays (not just copying the array address).
	this->Atoms = NewAtoms;
	this->Bonds = NewBonds;

	// Record each atom's array index, to make it easier to look up for copying bonds.
	for (i = 0; i < this->Atoms.Num(); ++i) {
		this->Atoms[i]->SetAtomIndex(i);
	}

	// Calculate molecule's total mass.
	this->TotalMass = 0;
	for (i = 0; i < this->Atoms.Num(); ++i) {
		this->TotalMass += this->Atoms[i]->GetMass();
	}

	// Calculate molecule's centre of mass, and shift the atom coordinates to put the CM at the origin.
	FVector cm(0, 0, 0);
	for (i = 0; i < this->Atoms.Num(); ++i) {
		cm += (this->Atoms[i]->GetMass()) * this->Atoms[i]->GetPosition();
	}
	cm /= this->TotalMass;
	for (i = 0; i < this->Atoms.Num(); ++i) {
		this->Atoms[i]->GetPosition() -= cm;
	}

	//Now we need to attach the atoms to the molecule
	InitAtoms();
	
	// TODO: Set the "Actor" locations for the atoms to put the visual representations
	// at the right places.
	// (Something about SetActorLocation...)
	// NOTE: Might not have to do this for prototypes!  (In which case it would go in the next constsructor, below.)

	// TODO: Draw the bonds, now that the atom locations are set up in the CM coordinates.
	// NOTE: Might not have to do this for prototypes!  (In which case it would go in the next constsructor, below.)
}
*/

/*
void AMolecule::InitMoleculeExactCopy(AMolecule* Source)
{
	UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMoleculeExactCopy() Called."));
	this->InitMoleculeCopy(Source, Source->GetPosition(), Source->GetVelocity(), Source->GetOrientation(), Source->GetAngularVelocity());
}
*/

/*
void AMolecule::InitMoleculeCopy(AMolecule* Source, FVector NewPosition, FVector NewVelocity, FVector NewOrientation, FVector NewAngularVelocity)
{
	int32 i, Index;
	AAtom* NewAtom;
	AAtom* AtomA;
	AAtom* AtomB;
	ABond* NewBond;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Copy properties from the source molecule.
	this->Name = Source->Name;
	//this->Rename(*Source->GetName());
	this->MolecularFormula = Source->MolecularFormula;
	this->DipoleMoment = Source->DipoleMoment;

	// Need to make new (deep) copies of the atoms and bonds, in case we want to
	// handle oscillations etc.
	for (i = 0; i < Source->Atoms.Num(); ++i) {
		// AAtom NewAtom = *(Source->Atoms[i]);
		NewAtom = NewObject<AAtom>();
		NewAtom->InitAtomExactCopy(Source->Atoms[i]);
		this->Atoms.Add(NewAtom);
	}
	// Point new bonds to the corresponding atoms in the new molecule.
	for (i = 0; i < Source->Bonds.Num(); ++i) {
		NewBond = NewObject<ABond>();
		Index = Source->Bonds[i]->GetAtomA()->GetAtomIndex();
		if (Index >= 0) {
			AtomA = this->Atoms[Index];
		}
		else {
			AtomA = nullptr;
		}
		Index = Source->Bonds[i]->GetAtomB()->GetAtomIndex();
		if (Index >= 0) {
			AtomB = this->Atoms[Index];
		}
		else {
			AtomB = nullptr;
		}
		NewBond->InitBondCopy(Source->Bonds[i], AtomA, AtomB);
		this->Bonds.Add(NewBond);
	}

	// Initialize the new molecule.
	this->Position = NewPosition;
	this->Velocity = NewVelocity;
	this->Orientation = NewOrientation;
	this->AngularVelocity = NewAngularVelocity;
}
*/

FString AMolecule::GetMoleculeName()
{
	return this->MoleculeName;
}

FString AMolecule::GetMoleculeFormula()
{
	return this->MoleculeFormula;
}

float AMolecule::GetTotalMass()
{
	return this->TotalMass;
}

FVector AMolecule::GetDipoleMoment()
{
	return this->DipoleMoment;
}

int32 AMolecule::GetNumAtoms()
{
	return Atoms.Num();
}

//FVector AMolecule::GetPosition()
//{
//	return this->Position;
//}

//FString AMolecule::PrintAtom(int32 AtomIndex)
//{
//	return (TEXT("Name: %s - Position: %s"), Atoms[AtomIndex]->GetName(), Atoms[AtomIndex]->GetPosition().ToString());
//}

/*
FVector AMolecule::GetVelocity()
{
	return this->Velocity;
}
*/

//FVector AMolecule::GetOrientation()
//{
//	return this->Orientation;
//}

FVector AMolecule::GetAngularVelocity()
{
	return this->AngularVelocity;
}



void AMolecule::SetInteractingMolecules(TArray<AMolecule*> MoleculeList)
{

}

TArray<AMolecule*> AMolecule::GetInteractingMolecules()
{
	return TArray<AMolecule*>();
}

// Called when the game starts or when spawned
void AMolecule::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMolecule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

