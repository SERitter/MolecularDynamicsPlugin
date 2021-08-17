// Fill out your copyright notice in the Description page of Project Settings.


#include "Atom.h"

#include "Simulation.h"

UAtom::UAtom()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/MolecularDynamicsPlugin/StaticMeshes/SM_Sphere.SM_Sphere'"));
	UStaticMesh* Asset = MeshAsset.Object;
	this->SetStaticMesh(Asset);

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/MolecularDynamicsPlugin/Materials/M_Atom.M_Atom'"));

	if (Material.Object != NULL)
	{
		MaterialBase = (UMaterialInterface*)Material.Object;
	}
	MaterialDynamic = UMaterialInstanceDynamic::Create(MaterialBase, NULL);
	this->SetMaterial(0, MaterialDynamic);

	//this->BodyInstance.SetCollisionProfileName("Indicator");
}

void UAtom::InitAtom(FAtomData* AtomData, FString AtomSymbol, int32 Index)
{
	AtomArrayIndex = Index;
	AtomName = AtomData->ElementName;
	AtomicNumber = AtomData->AtomicNumber;
	Color = FColor().FromHex(AtomData->Color);
	Mass = AtomData->Mass;
	Symbol = AtomSymbol;
	VDWRadius = AtomData->VDWRadius;
	MaterialDynamic->SetVectorParameterValue("Color", Color);
	
	this->BodyInstance.SetMassOverride(Mass);

	
	//SetRenderBallStick();
	SetRenderSpaceFilling();
}

void UAtom::SetRenderBallStick()
{
	this->SetRelativeScale3D(FVector(this->VDWRadius / 4));
}

void UAtom::SetRenderSpaceFilling()
{
	this->SetRelativeScale3D(FVector(this->VDWRadius));
}
