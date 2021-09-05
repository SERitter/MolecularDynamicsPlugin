// Fill out your copyright notice in the Description page of Project Settings.


#include "Atom.h"
//#include "InteractionSphere.h"

#include "Simulation.h"

UAtom::UAtom()
{	
	//AtomRepresentation = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AtomRepresentation"));
	//AtomRepresentation->SetupAttachment(this);
	//AtomRepresentation->AttachToComponent(this->GetParentComponents(), FAttachmentTransformRules::SnapToTargetIncludingScale);
	//AtomRepresentation->RegisterComponent();
	//AtomRepresentation->SetCollisionProfileName("Representation");
	//AtomRepresentation->SetRelativeLocation(FVector(0.f));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("StaticMesh'/MolecularDynamicsPlugin/StaticMeshes/SM_Sphere.SM_Sphere'"));
	Asset = MeshAsset.Object;

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/MolecularDynamicsPlugin/Materials/M_Atom.M_Atom'"));

	if (Material.Object != NULL)
	{
		MaterialBase = (UMaterialInterface*)Material.Object;
	}
	MaterialDynamic = UMaterialInstanceDynamic::Create(MaterialBase, NULL);
}

FColor UAtom::GetColor()
{
	return Color;
}

FString UAtom::GetSymbol()
{
	return Symbol;
}

void UAtom::InitAtom(FAtomData* AtomData, FString AtomSymbol, int32 Index, USimulationData* Simulation)
{
	AtomArrayIndex = Index;
	AtomName = AtomData->ElementName;
	AtomicNumber = AtomData->AtomicNumber;
	Color = FColor().FromHex(AtomData->Color);
	Mass = AtomData->Mass;
	Symbol = AtomSymbol;
	VDWRadius = AtomData->VDWRadius;
	MaterialDynamic->SetVectorParameterValue("Color", Color);
	SimulationData = Simulation;

	AtomRepresentation = NewObject<UStaticMeshComponent>(this);
	AtomRepresentation->SetupAttachment(this);
	AtomRepresentation->RegisterComponent();
	AtomRepresentation->SetMaterial(0, MaterialDynamic);
	AtomRepresentation->SetCollisionProfileName("Representation");
	AtomRepresentation->SetStaticMesh(Asset);
	AtomRepresentation->BodyInstance.SetMassOverride(Mass);
	AtomRepresentation->BodyInstance.LinearDamping = 0.f;

	//Originally set to 1/4 vdw radius, but that allows for spearation of 68pm between O and H, Which is a nearly infinite repulsion force.
	//Switched to a distance that will  to prevent infinite forces from being called. 
	this->SetSphereRadius(VDWRadius * 0.5f);
	this->BodyInstance.SetCollisionProfileName("Atom");
	this->BodyInstance.SetMassOverride(Mass);
	this->BodyInstance.SetEnableGravity(false);
	this->BodyInstance.LinearDamping = 0.f;

	FActorSpawnParameters SpawnInfo;	
	InteractionSphere = GetWorld()->SpawnActor<AInteractionSphere>(GetComponentLocation(), GetComponentRotation(), SpawnInfo);
	InteractionSphere->AttachToComponent(this, FAttachmentTransformRules::SnapToTargetIncludingScale);
	InteractionSphere->GetCollisionComponent()->ShapeColor = FColor(FColor::Blue);
	InteractionSphere->InitInteractionSphere(Symbol, SimulationData, this);
	//InteractionSphere->InitInteractionSphere(this, SimulationData);

	UShapeComponent* Shape = InteractionSphere->GetCollisionComponent();
	Cast<USphereComponent>(Shape)->SetSphereRadius(VDWRadius * 2);
	Cast<USphereComponent>(Shape)->SetCollisionProfileName("AtomOverlap");
}

void UAtom::SetHideCollisionSpheres()
{
	this->SetVisibility(false);
	this->SetHiddenInGame(true);
}

void UAtom::SetHideInteractionSpheres()
{
	UE_LOG(LogTemp, Warning, TEXT("UAtom::SetHideInteractionSpheres Called."))
	InteractionSphere->GetCollisionComponent()->SetVisibility(false);
	InteractionSphere->GetCollisionComponent()->SetHiddenInGame(true);
	InteractionSphere->SetActorHiddenInGame(true);
}

void UAtom::SetShowCollisionSpheres()
{
	this->SetVisibility(true);
	this->SetHiddenInGame(false);
}

void UAtom::SetShowInteractionSpheres()
{
	UE_LOG(LogTemp, Warning, TEXT("UAtom::SetShowInteractionSpheres Called."))
	InteractionSphere->GetCollisionComponent()->SetVisibility(true);
	InteractionSphere->GetCollisionComponent()->SetHiddenInGame(false);
	InteractionSphere->SetActorHiddenInGame(false);
}

void UAtom::SetRenderBallStick()
{
	UE_LOG(LogTemp, Warning, TEXT("UAtom::SetRenderBallStick() Called"));
	AtomRepresentation->SetRelativeScale3D(FVector(this->VDWRadius / 4));
	AtomRepresentation->SetVisibility(true);
}

void UAtom::SetRenderHidden()
{
	UE_LOG(LogTemp, Warning, TEXT("UAtom::SetRenderHidden() Called"));
	AtomRepresentation->SetVisibility(false);
}

void UAtom::SetRenderLinear()
{
	UE_LOG(LogTemp, Warning, TEXT("UAtom::SetRenderLinear() Called"));
	AtomRepresentation->SetRelativeScale3D(FVector(10.f));
	AtomRepresentation->SetVisibility(true);
}

void UAtom::SetRenderSpaceFilling()
{
	UE_LOG(LogTemp, Warning, TEXT("UAtom::SetRenderSpaceFilling() Called"));
	AtomRepresentation->SetRelativeScale3D(FVector(this->VDWRadius));
	AtomRepresentation->SetVisibility(true);
}

void UAtom::UpdateIntermolecularForces()
{
	InteractionSphere->UpdateForces();
}
