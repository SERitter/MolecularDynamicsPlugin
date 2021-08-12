// Fill out your copyright notice in the Description page of Project Settings.


#include "Bond.h"

// Sets default values
ABond::ABond()
{
}

void ABond::InitBond(FString NewName, FString NewType, float NewEquilibriumLength, float NewSpringConstant, FLinearColor NewColor, AAtom* NewAtomA, AAtom* NewAtomB)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = NewName;
	Type = NewType;
	EquilibriumLength = NewEquilibriumLength;
	SpringConstant = NewSpringConstant;
	Color = NewColor;
	AtomA = NewAtomA;
	AtomB = NewAtomB;

	// Initialize representation(s) here...
}

void ABond::InitBondPrototype(FString NewName, FString NewType, float NewEquilibriumLength, float NewSpringConstant, FLinearColor NewColor)
{
	Name = NewName;
	Type = NewType;
	EquilibriumLength = NewEquilibriumLength;
	SpringConstant = NewSpringConstant;
	Color = NewColor;
}

void ABond::InitBondCopy(ABond* Source, AAtom* NewAtomA, AAtom* NewAtomB)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Name = Source->Name;
	Type = Source->Type;
	EquilibriumLength = Source->EquilibriumLength;
	SpringConstant = Source->SpringConstant;
	Color = Source->Color;
	AtomA = NewAtomA;
	AtomB = NewAtomB;

	// Initialize representation(s) here...
}

// Called when the game starts or when spawned
void ABond::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABond::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString ABond::GetBondName()
{
	return Name;
}

FString ABond::GetBondType()
{
	return Type;
}

float ABond::GetBondEnergy()
{
	return 0.0f;
}

float ABond::GetBondLength()
{
	return 0.0f;
}

AAtom* ABond::GetAtomA()
{
	return AtomA;
}

AAtom* ABond::GetAtomB()
{
	return AtomB;
}

void ABond::SetAtomA(AAtom* Atom)
{
	AtomA = Atom;
}

void ABond::SetAtomB(AAtom* Atom)
{
	AtomB = Atom;
}

void ABond::UpdateBondEnergy()
{
}

void ABond::UpdateBondLength()
{
}

