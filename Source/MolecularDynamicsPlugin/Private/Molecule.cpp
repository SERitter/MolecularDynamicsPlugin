// Fill out your copyright notice in the Description page of Project Settings.


#include "Molecule.h"


AMolecule::AMolecule()
{
	MoleculeCoMIndicator = CreateDefaultSubobject<USphereComponent>(TEXT("CenterOfMass"));

	SetRootComponent(MoleculeCoMIndicator);
	MoleculeCoMIndicator->SetHiddenInGame(false);
	MoleculeCoMIndicator->SetSphereRadius(10.f);
	MoleculeCoMIndicator->BodyInstance.SetCollisionProfileName(TEXT("Molecule"));
	MoleculeCoMIndicator->BodyInstance.SetEnableGravity(false);
	MoleculeCoMIndicator->BodyInstance.LinearDamping = 0.f;
	MoleculeCoMIndicator->ShapeColor = FColor(FColor::Green);

	//set up movement component
	//MoleculeMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoleculeMovementComponent"));
	//MoleculeMovementComponent->SetUpdatedComponent(MoleculeCoMIndicator);
	
	//MoleculeMovementComponent->InitialSpeed = 0.f;
	//MoleculeMovementComponent->MaxSpeed = 0.f;
	//MoleculeMovementComponent->bRotationFollowsVelocity = false;
	//MoleculeMovementComponent->bShouldBounce = true;
	//MoleculeMovementComponent->bInitialVelocityInLocalSpace = true;
	//MoleculeMovementComponent->Bounciness = 1.0f;
	//MoleculeMovementComponent->Friction = 0.0f;
	//MoleculeMovementComponent->ProjectileGravityScale = 0.f;
	//MoleculeMovementComponent->Velocity = (FVector(0.f));

	//MoleculeRotationComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("MoleculeRotationComponent"));
	//MoleculeRotationComponent->PivotTranslation = MoleculeCoMIndicator->GetRelativeLocation();
}

void AMolecule::InitMolecule(FMoleculePrototype& Prototype, int32 Index, USimulationData* Simulation)
{
	UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule() MoleculePrototype Name:%s - Formula:%s - Density:%f - MolarMass:%f NumAtoms:%d"), *Prototype.Name, *Prototype.Formula, Prototype.Density, Prototype.MolarMass, Prototype.Atoms.Num());
	this->MoleculeName = Prototype.Name;
	this->MoleculeFormula = Prototype.Formula;
	this->MoleculeIndex = Index;
	this->MoleculeMass = Prototype.MolarMass;
	MoleculeCoMIndicator->BodyInstance.SetMassOverride(this->MoleculeMass);
	SimulationData = Simulation;
	//this->Simulation = Container;

	UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule(%s) Spawning and Initializing %d Atoms."),*Prototype.Name, Prototype.Atoms.Num());
	for(FAtomPrototype AtomPrototype : Prototype.Atoms)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule(%s) Atom Symbol:%s Position:%s"), *Prototype.Name, *AtomPrototype.Symbol, *AtomPrototype.Position.ToString());
	
		UAtom* Atom = NewObject<UAtom>(this);
		Atom->AttachToComponent(MoleculeCoMIndicator, FAttachmentTransformRules::SnapToTargetIncludingScale);
		Atom->RegisterComponent();
		this->AddInstanceComponent(Atom);

		Atom->SetRelativeLocation(AtomPrototype.Position);

		UE_LOG(LogTemp, Warning, TEXT("UAtom::InitAtom() Attempting to access AtomData Table: %s"), *AtomPrototype.Symbol);
		FName LookupSymbol = FName(AtomPrototype.Symbol);
		if(IsValid(SimulationData->GetAtomData()))
		{
			FAtomData* AtomData = SimulationData->GetAtomData()->FindRow<FAtomData>(LookupSymbol, "");
			UE_LOG(LogTemp, Warning, TEXT("UAtom::InitAtom() ***ATOM*** m=%f, r=%f"), AtomData->Mass, AtomData->VDWRadius);
			
			Atom->InitAtom(AtomData, AtomPrototype.Symbol, Atoms.Num(), SimulationData);
			Atoms.Add(Atom);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("UAtom::InitAtom() Unable to access SimulationData->AtomDataTable"));
		}
	}

	for(FBondPrototype BondPrototype : Prototype.Bonds)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule(%s) Bond IndexA:%d:%s IndexB:%d:%s"), *Prototype.Name, BondPrototype.IndexA, *Atoms[BondPrototype.IndexA]->GetSymbol(), BondPrototype.IndexB, *Atoms[BondPrototype.IndexB]->GetSymbol());

		UBond* Bond = NewObject<UBond>(this);
		Bond->AttachToComponent(MoleculeCoMIndicator, FAttachmentTransformRules::SnapToTargetIncludingScale);
		Bond->RegisterComponent();
		this->AddInstanceComponent(Bond);
		Bonds.Add(Bond);

		Bond->InitBond(Atoms[BondPrototype.IndexA], Atoms[BondPrototype.IndexB], BondPrototype.BondType);	
	}
}

void AMolecule::AddImpulse(FVector ImpulseVector)
{
	MoleculeCoMIndicator->AddImpulse(ImpulseVector, NAME_None, true);
}

void AMolecule::AddTorque(FVector TorqueVector)
{
	MoleculeCoMIndicator->AddTorque(TorqueVector, NAME_None, true);
}


void AMolecule::EnablePhysics()
{
	UE_LOG(LogTemp, Warning, TEXT("AMolecule::EnablePhysics() Molecule Name:"), *this->GetActorLabel());
	MoleculeCoMIndicator->SetSimulatePhysics(true);
}

void AMolecule::Freeze()
{
	if (MoleculeCoMIndicator->IsSimulatingPhysics())
	{
		AddImpulse(-1 * MoleculeCoMIndicator->GetComponentVelocity());
		MoleculeCoMIndicator->BodyInstance.ClearForces();
		MoleculeCoMIndicator->BodyInstance.ClearTorques(); //FIXME molecules still rotating too much
		MoleculeCoMIndicator->SetSimulatePhysics(false);
	}
}

FVector AMolecule::GetCurrentVelocity()
{
	return MoleculeCoMIndicator->GetComponentVelocity();
}

FVector AMolecule::GetInitialPosition()
{
	return InitialPosition;
}

/*
float AMolecule::GetInitialTemperature()
{
	return InitialTemp;
}
*/

FVector AMolecule::GetInitialTorque()
{
	return InitialTorque;
}

FVector AMolecule::GetInitialVelocity()
{
	return InitialVelocity;
}

FString AMolecule::GetMoleculeFormula()
{
	return this->MoleculeFormula;
}

FString AMolecule::GetMoleculeName()
{
	return this->MoleculeName;
}

float AMolecule::GetMoleculeMass()
{
	return this->MoleculeMass;
}

int32 AMolecule::GetNumAtoms()
{
	return Atoms.Num();
}

float AMolecule::GetSpeed()
{
	FVector CurVel = this->GetCurrentVelocity();
	float CurSpeed = CurVel.Size();
	//UE_LOG(LogTemp, Warning, TEXT("AMolecule::GetSpeed(%s) Velocity:%s - Speed:%f"), *this->GetName(), *CurVel.ToString(), CurSpeed);
	
	return this->GetCurrentVelocity().Size();
}

void AMolecule::ResetMolecule()
{
	if(IsValid(SimulationData->GetSimulation()))
	{
		FVector SimulationLocation = SimulationData->GetSimulation()->GetActorLocation();
		float SimulationCellWidth = SimulationData->GetCellWidth();
		FVector SimulationCellOffset = FVector(0.f, 0.f, (SimulationCellWidth / 2));
		FVector NewLocation = InitialPosition + SimulationLocation + SimulationCellOffset;
		this->SetActorLocation(NewLocation);
		UE_LOG(LogTemp, Warning, TEXT("AMolecule::ResetMolecule(%s) Initial Location:%s - SimulationCell Location:%s - SimulationData.SimulationCellWidth:%f - SimulationCellOffset:%s - New Location:%s"), *this->GetName(), *this->InitialPosition.ToString(), *SimulationLocation.ToString(),SimulationCellWidth, *SimulationCellOffset.ToString(), *NewLocation.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AMolecule::ResetMolecule() Unable to access SimulationData->Simulation"))
	}
}

/*
FVector AMolecule::GetCurrentTorque()
{
	return MoleculeCoMIndicator->Get
}
*/

void AMolecule::SetAngularVelocity(FVector NewAngularVelocity)
{
	//FRotator AngRotation = FRotator(NewAngularVelocity.Y, NewAngularVelocity.X, NewAngularVelocity.Z);
	//UE_LOG(LogTemp, Warning, TEXT("AMolecule::SetAngularVelocity(%s) AngularRotation:%s"), *NewAngularVelocity.ToString(), *AngRotation.ToString());
	
	//MoleculeRotationComponent->RotationRate = AngRotation;
	InitialTorque = NewAngularVelocity;
}

void AMolecule::SetInitialPosition(FVector Position)
{
	InitialPosition = Position;
}

void AMolecule::SetInitialVelocity(FVector NewVelocity)
{
	UE_LOG(LogTemp, Warning, TEXT("AMolecule::SetInitialVelocity(%s)"), *NewVelocity.ToString());
	InitialVelocity = NewVelocity;
}

/*
void AMolecule::SetInitialTemperature(float InitialTemperature)
{
	InitialTemp = InitialTemperature;
}
*/

void AMolecule::SetHideCollisionSpheres()
{
	for(UAtom* Atom : Atoms)
	{
		Atom->SetHideCollisionSpheres();
	}
}

void AMolecule::SetHideCoM()
{
	MoleculeCoMIndicator->SetHiddenInGame(true);
	MoleculeCoMIndicator->SetVisibility(false);
}

void AMolecule::SetHideInteractionSpheres()
{
	for (UAtom* Atom : Atoms)
	{
		Atom->SetHideInteractionSpheres();
	}
}

void AMolecule::SetHideSpline()
{
	for (UBond* Bond : Bonds)
	{
		Bond->SetHideSpline();
	}
}

void AMolecule::SetShowCollisionSpheres()
{
	for (UAtom* Atom : Atoms)
	{
		Atom->SetShowCollisionSpheres();
	}
}

void AMolecule::SetShowInteractionSpheres()
{
	for (UAtom* Atom : Atoms)
	{
		Atom->SetShowInteractionSpheres();
	}
}

void AMolecule::SetShowCoM()
{
	MoleculeCoMIndicator->SetHiddenInGame(false);
	MoleculeCoMIndicator->SetVisibility(true);
}

void AMolecule::SetShowSpline()
{
	for (UBond* Bond : Bonds)
	{
		Bond->SetShowSpline();
	}
}

void AMolecule::SetRenderBallStick()
{
	for(UAtom* Atom : Atoms)
	{
		Atom->SetRenderBallStick();
	}
	for(UBond* Bond :Bonds)
	{
		Bond->SetRenderBallStick();
	}
}

void AMolecule::SetRenderHidden()
{
	for (UAtom* Atom : Atoms)
	{
		Atom->SetRenderHidden();
	}
	for (UBond* Bond : Bonds)
	{
		Bond->SetRenderHidden();
	}
}

void AMolecule::SetRenderLinear()
{
	for (UAtom* Atom : Atoms)
	{
		Atom->SetRenderLinear();
	}
	for (UBond* Bond : Bonds)
	{
		Bond->SetRenderLinear();
	}
}

void AMolecule::SetRenderSpaceFilling()
{
	for (UAtom* Atom : Atoms)
	{
		Atom->SetRenderSpaceFilling();
	}
	for (UBond* Bond : Bonds)
	{
		Bond->SetRenderSpaceFilling();
	}
}

void AMolecule::SetVelocity(FVector NewVelocity)
{
	UE_LOG(LogTemp, Warning, TEXT("AMolecule::SetVelocity(%s)"),*NewVelocity.ToString());
	MoleculeCoMIndicator->SetPhysicsLinearVelocity(NewVelocity);
}

void AMolecule::UpdateIntermolecularForces()
{
	for(UAtom* Atom : Atoms)
	{
		Atom->UpdateIntermolecularForces();
	}
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

