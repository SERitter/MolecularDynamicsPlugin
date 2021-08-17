// Fill out your copyright notice in the Description page of Project Settings.


#include "Molecule.h"


AMolecule::AMolecule()
{
	MoleculeCoMIndicator = CreateDefaultSubobject<USphereComponent>(TEXT("CenterOfMass"));

	SetRootComponent(MoleculeCoMIndicator);
	MoleculeCoMIndicator->SetHiddenInGame(false);
	MoleculeCoMIndicator->SetSphereRadius(100.f);
	MoleculeCoMIndicator->BodyInstance.SetCollisionProfileName(TEXT("Molecule"));
	MoleculeCoMIndicator->BodyInstance.SetEnableGravity(false);
	MoleculeCoMIndicator->BodyInstance.LinearDamping = 0.f;
	
	//set up movement component
	MoleculeMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoleculeMovementComponent"));
	MoleculeMovementComponent->SetUpdatedComponent(MoleculeCoMIndicator);
	
	MoleculeMovementComponent->InitialSpeed = 0.f;
	MoleculeMovementComponent->MaxSpeed = 0.f;
	MoleculeMovementComponent->bRotationFollowsVelocity = false;
	MoleculeMovementComponent->bShouldBounce = true;
	MoleculeMovementComponent->Bounciness = 1.0f;
	MoleculeMovementComponent->Friction = 0.0f;
	MoleculeMovementComponent->ProjectileGravityScale = 0.f;
	MoleculeMovementComponent->Velocity = (FVector(0.f));
}

void AMolecule::InitMolecule(FMoleculePrototype& Prototype, int32 Index, UDataTable* AtomDataTable)
{
	UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule() MoleculePrototype Name:%s - Formula:%s - Density:%f - MolarMass:%f NumAtoms:%d"), *Prototype.Name, *Prototype.Formula, Prototype.Density, Prototype.MolarMass, Prototype.Atoms.Num());
	this->MoleculeName = Prototype.Name;
	this->MoleculeFormula = Prototype.Formula;
	this->MoleculeIndex = Index;
	this->MoleculeMass = Prototype.MolarMass;
	MoleculeCoMIndicator->BodyInstance.SetMassOverride(this->MoleculeMass);

	UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule(%s) Spawning and Initializing %d Atoms."),*Prototype.Name, Prototype.Atoms.Num());
	for(FAtomPrototype AtomPrototype : Prototype.Atoms)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule(%s) Atom Symbol:%s Position:%s"), *Prototype.Name, *AtomPrototype.Symbol, *AtomPrototype.Position.ToString());
	
		UAtom* Atom = NewObject<UAtom>(this);
		Atom->AttachToComponent(MoleculeCoMIndicator, FAttachmentTransformRules::SnapToTargetIncludingScale);
		Atom->RegisterComponent();
		this->AddInstanceComponent(Atom);

		Atom->SetRelativeLocation(AtomPrototype.Position);

		UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule() Attempting to access AtomData Table: %s"), *AtomPrototype.Symbol);
		FName Symbol = FName(AtomPrototype.Symbol);
		FAtomData* AtomData = AtomDataTable->FindRow<FAtomData>(Symbol, "");
		UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule() ***ATOM*** m=%f, r=%f"), AtomData->Mass, AtomData->VDWRadius);
		Atom->InitAtom(AtomData, AtomPrototype.Symbol, Atoms.Num());

		Atoms.Add(Atom);
	}

	/*
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
		UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitMolecule() ***ATOM*** m=%f, r=%f"), AtomData->Mass, AtomData->VDWRadius);
		SpawnedAtom->InitAtom(AtomData, Prototype.Atoms[i].Symbol, i, Prototype.Atoms[i].Position);

		Atoms.Add(SpawnedAtom);
	}
	*/
	
	//InitCollisionSpheres();
}

void AMolecule::InitCollisionSpheres()
{
	UE_LOG(LogTemp, Warning, TEXT("AMolecule::InitCollisionSpheres() Called"));
	CollisionSpheres.Empty();
	for(UAtom* Atom : Atoms)
	{
		USphereComponent* CollisionSphere = NewObject<USphereComponent>(this);
		CollisionSphere->AttachToComponent(MoleculeCoMIndicator, FAttachmentTransformRules::SnapToTargetIncludingScale);
		CollisionSphere->RegisterComponent();
		CollisionSphere->SetHiddenInGame(false);
		//CollisionSphere->SetSphereRadius(Atom->GetVDWRadius() / 4);
		//CollisionSphere->SetRelativeLocation(Atom->GetAtomPosition());
		//CollisionSphere->BodyInstance.SetMassOverride(Atom->GetMass());
		CollisionSphere->BodyInstance.SetEnableGravity(false);
		CollisionSphere->BodyInstance.SetCollisionProfileName("Atom");
		this->AddInstanceComponent(CollisionSphere);

		CollisionSpheres.Add(CollisionSphere);
		
		/*
		 * 
		USphereComponent* CollisionSphere = NewObject<USphereComponent>(MoleculeCoMIndicator, USphereComponent::StaticClass());
		CollisionSphere->AttachToComponent(MoleculeCoMIndicator, FAttachmentTransformRules::SnapToTargetIncludingScale);
		CollisionSphere->SetHiddenInGame(false);
		CollisionSphere->SetSphereRadius(Atom->GetVDWRadius() / 4);
		
		this->RerunConstructionScripts();
		CollisionSpheres.Add(CollisionSphere);		
		 */
	}
}

void AMolecule::EnablePhysics()
{
	UE_LOG(LogTemp, Warning, TEXT("AMolecule::EnablePhysics() Molecule Name:"), *this->GetActorLabel());
	MoleculeCoMIndicator->SetSimulatePhysics(true);
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


void AMolecule::SetRenderBallStick()
{
	/*
	for(AAtom* Atom : Atoms)
	{
		Atom->SetRenderBallStick();
	}
	*/
}

void AMolecule::SetRenderSpaceFilling()
{
	/*
	for (AAtom* Atom : Atoms)
	{
		Atom->SetRenderSpaceFilling();
	}
	*/
}

void AMolecule::SetVelocity(FVector NewVelocity)
{
	MoleculeMovementComponent->Velocity = NewVelocity;
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

