// Fill out your copyright notice in the Description page of Project Settings.


#include "Atom.h"

// Sets default values
AAtom::AAtom()
{
	UE_LOG(LogTemp, Warning, TEXT("AAtom::AAtom() Called."));
	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//RootComponent = Root;

	AtomRepresentation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AtomRepresentation"));
	SetRootComponent(AtomRepresentation);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/MolecularDynamicsPlugin/StaticMeshes/SM_Sphere.SM_Sphere'"));
	UStaticMesh* Asset = MeshAsset.Object;
	AtomRepresentation->SetStaticMesh(Asset);

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/MolecularDynamicsPlugin/Materials/M_Atom.M_Atom'"));
	
	if (Material.Object != NULL)
	{
		AtomMaterial = (UMaterialInterface*)Material.Object;
	}
	DynamicMaterial = UMaterialInstanceDynamic::Create(AtomMaterial, NULL);
	AtomRepresentation->SetMaterial(0, DynamicMaterial);
}

void AAtom::InitAtom(FAtomData* AtomData, FString AtomSymbol, int32 Index)
{
	UE_LOG(LogTemp, Warning, TEXT("AAtom::InitAtom() Called."));
	this->Name = AtomData->ElementName;
	this->Symbol = AtomSymbol;
	this->HexColor = AtomData->Color;
	this->Mass = AtomData->Mass;
	this->CovalentRadius = AtomData->Radius;
	this->AtomicNumber = AtomData->AtomicNumber;
	this->AtomArrayIndex = Index;
	UE_LOG(LogTemp, Warning, TEXT("AAtom::InitAtom() HexColor:%s."), *HexColor);
	this->Color = FColor().FromHex(HexColor);

	AtomRepresentation->SetRelativeScale3D(FVector(2 * this->CovalentRadius));

	DynamicMaterial->SetVectorParameterValue("Color", this->Color);

	//if (MaterialBase)
//		DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialBase, this);
	//static ConstructorHelpers::FObjectFinder<UMaterialInterface>MaterialAsset(TEXT("Material'/MolecularDynamicsPlugin/Materials/M_Atom.M_Atom'"));
	//UMaterialInterface* Material = MaterialAsset.Object;
	//AtomRepresentation->SetMaterial(0, DynamicMaterial);
}

/*
 * 
void AAtom::InitAtomPrototype(FString NewName, FString NewSymbol, FString NewType, FLinearColor NewColor, float NewMass, int32 NewCharge, float NewCovalentRadius, float NewVanDerWaalsRadius, float NewVanDerWaalsMagnitude)
{
	this->Name = NewName;
	this->Symbol = NewSymbol;
	this->Type = NewType;
	this->Color = NewColor;
	this->Mass = NewMass;
	this->Charge = NewCharge;
	this->CovalentRadius = NewCovalentRadius;
	this->VanDerWaalsRadius = NewVanDerWaalsRadius;
	this->VanDerWaalsMagnitude = NewVanDerWaalsMagnitude;
}
 */

/*
 * 
void AAtom::InitAtomCopy(AAtom* Source, FVector NewPosition)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Name = Source->Name;
	this->Symbol = Source->Symbol;
	this->Type = Source->Type;
	this->Color = Source->Color;
	this->Mass = Source->Mass;
	this->Charge = Source->Charge;
	this->CovalentRadius = Source->CovalentRadius;
	this->VanDerWaalsRadius = Source->VanDerWaalsRadius;
	this->VanDerWaalsMagnitude = Source->VanDerWaalsMagnitude;
	this->AtomArrayIndex = Source->AtomArrayIndex;

	this->Position = NewPosition;

	// Initialize representation(s) here.
}
 */

/*
 * 
void AAtom::InitAtomExactCopy(AAtom* Source) {
	this->InitAtomCopy(Source, Source->GetPosition());
}
 */

//FVector AAtom::GetPosition()
//{
//	return Position;
//}

// Called when the game starts or when spawned
void AAtom::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
auto AAtom::Tick(float DeltaTime) -> void
{
	Super::Tick(DeltaTime);
}

FString AAtom::GetName()
{
	return this->Name;
}

float AAtom::GetMass() {
	return this->Mass;
}

float AAtom::GetCharge()
{
	return this->Charge;
}

float AAtom::GetCovalentRadius()
{
	return this->CovalentRadius;
}

float AAtom::GetVanDerWaalsRadius()
{
	return this->VanDerWaalsRadius;
}

float AAtom::GetVanDerWaalsMagnitude()
{
	return this->VanDerWaalsMagnitude;
}

void AAtom::SetAtomIndex(int32 Index)
{
	AtomArrayIndex = Index;
}

void AAtom::SetMesh(UStaticMeshComponent* Mesh)
{
	AtomRepresentation = Mesh;
}

void AAtom::SetMaterial(UMaterial* Material)
{
	AtomMaterial = Material;
}

UStaticMeshComponent* AAtom::GetMesh()
{
	return AtomRepresentation;
}

UMaterialInterface* AAtom::GetMaterial()
{
	return AtomMaterial;
}

int32 AAtom::GetAtomIndex()
{
	return AtomArrayIndex;
}
