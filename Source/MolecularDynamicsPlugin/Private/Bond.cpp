// Fill out your copyright notice in the Description page of Project Settings.


#include "Bond.h"

// Sets default values for this component's properties
UBond::UBond()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SplineMeshComponent = CreateDefaultSubobject<USplineMeshComponent>("BondMesh");
	SplineMeshComponent->SetupAttachment(this);
	SplineMeshComponent->RegisterComponent();

	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/MolecularDynamicsPlugin/Materials/M_Bond.M_Bond'"));

	if (Material.Object != NULL)
	{
		MaterialBase = (UMaterialInterface*)Material.Object;
	}
	MaterialDynamic = UMaterialInstanceDynamic::Create(MaterialBase, NULL);
	this->SetMaterial(0, MaterialDynamic);
}

void UBond::InitBond(UAtom* AtomAIn, UAtom* AtomBIn, EBondType& BondTypeIn)
{
	UE_LOG(LogTemp, Warning, TEXT("UBond::InitBond() Called."));
	AtomA = AtomAIn;
	AtomB = AtomBIn;
	BondType = BondTypeIn;

	InitSpline();
	InitBondType();
	InitBondRep();
}

void UBond::InitBondRep()
{
	SplineMeshComponent->SetStaticMesh(BondMesh);
	SplineMeshComponent->SetMobility(EComponentMobility::Movable);
	SplineMeshComponent->SetForwardAxis(ESplineMeshAxis::Z);
	FVector StartPoint = this->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::Type::Local);
	FVector StartTangent = this->GetTangentAtSplinePoint(0, ESplineCoordinateSpace::Type::Local);
	FVector EndPoint = this->GetLocationAtSplinePoint(1, ESplineCoordinateSpace::Type::Local);
	FVector EndTangent = this->GetTangentAtSplinePoint(1, ESplineCoordinateSpace::Type::Local);
	SplineMeshComponent->SetStartAndEnd(StartPoint, StartTangent, EndPoint, EndTangent);
	SplineMeshComponent->SetMaterial(0, MaterialDynamic);
	Color = FColor().FromHex("808080");
	ColorA = AtomA->GetColor();
	ColorB = AtomB->GetColor();
	
}

void UBond::InitBondType()
{
	UE_LOG(LogTemp, Warning, TEXT("UBond::InitBondMesh() Called."));
	FString BondMeshPath;
	FString BondMaterialPath;
	
	switch (BondType)
	{
	case EBondType::SINGLE:
		UE_LOG(LogTemp, Warning, TEXT("UBond::InitBondMesh() SINGLE BOND."));
		BondMeshPath = TEXT("StaticMesh'/MolecularDynamicsPlugin/StaticMeshes/SM_SingleBond.SM_SingleBond'");
		//BondMaterialPath = TEXT("Material'/MolecularDynamicsPlugin/Materials/M_Bond.M_Bond'");
		break;
	case EBondType::DOUBLE:
		UE_LOG(LogTemp, Warning, TEXT("UBond::InitBondMesh() DOUBLE BOND."));
		BondMeshPath = TEXT("StaticMesh'/MolecularDynamicsPlugin/StaticMeshes/SM_DoubleBond.SM_DoubleBond'");
		//BondMaterialPath = TEXT("Material'/MolecularDynamicsPlugin/Materials/M_Bond.M_Bond'");
		break;
	case EBondType::TRIPLE:
		UE_LOG(LogTemp, Warning, TEXT("UBond::InitBondMesh() TRIPLE BOND."));
		BondMeshPath = TEXT("StaticMesh'/MolecularDynamicsPlugin/StaticMeshes/SM_TripleBond.SM_TripleBond'");
		//BondMaterialPath = TEXT("Material'/MolecularDynamicsPlugin/Materials/M_Bond.M_Bond'");
		break;
	case EBondType::HYDROGEN:
		UE_LOG(LogTemp, Warning, TEXT("UBond::InitBondMesh() HYDROGEN BOND."));
		BondMeshPath = TEXT("StaticMesh'/MolecularDynamicsPlugin/StaticMeshes/SM_SingleBond.SM_SingleBond'");
		//BondMaterialPath = TEXT("Material'/MolecularDynamicsPlugin/Materials/M_Bond.M_Bond'");
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("UBond::InitBondMesh() No acceptable BONDTYPE provided."));
		BondMeshPath = TEXT("StaticMesh'/MolecularDynamicsPlugin/StaticMeshes/SM_SingleBond.SM_SingleBond'");
		//BondMaterialPath = TEXT("Material'/MolecularDynamicsPlugin/Materials/M_Bond.M_Bond'");
		break;
	}

	BondMesh = LoadObject<UStaticMesh>(nullptr, *BondMeshPath);
	//MaterialBase = LoadObject<UMaterial>(nullptr, *BondMaterialPath);
	//MaterialDynamic = UMaterialInstanceDynamic::Create(MaterialBase, NULL);
}

void UBond::InitSpline()
{
	bDrawDebug = true;
	this->ClearSplinePoints();
	this->AddSplineLocalPoint(AtomA->GetRelativeLocation());
	this->AddSplineLocalPoint(AtomB->GetRelativeLocation());
}

void UBond::SetHideSpline()
{
	bDrawDebug = false;
	this->SetHiddenInGame(true);
	this->SetVisibility(false);
}

void UBond::SetShowSpline()
{
	bDrawDebug = true;
	this->SetHiddenInGame(false);
	this->SetVisibility(true);
}

void UBond::SetRenderBallStick()
{
	UE_LOG(LogTemp, Warning, TEXT("UBond::SetRenderBallStick() Called"));
	SplineMeshComponent->SetVisibility(true);
	MaterialDynamic->SetVectorParameterValue("ColorA", Color);
	MaterialDynamic->SetVectorParameterValue("ColorB", Color);
}

void UBond::SetRenderHidden()
{
	UE_LOG(LogTemp, Warning, TEXT("UBond::SetRenderHidden() Called"));
	SplineMeshComponent->SetVisibility(false);
}

void UBond::SetRenderLinear()
{
	UE_LOG(LogTemp, Warning, TEXT("UBond::SetRenderLinear() Called"));
	SplineMeshComponent->SetVisibility(true);
	MaterialDynamic->SetVectorParameterValue("ColorA", ColorA);
	MaterialDynamic->SetVectorParameterValue("ColorB", ColorB);
}

void UBond::SetRenderSpaceFilling()
{
	UE_LOG(LogTemp, Warning, TEXT("UBond::SetRenderSpaceFilling() Called"));
	SplineMeshComponent->SetVisibility(false);
}


// Called when the game starts
void UBond::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBond::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

