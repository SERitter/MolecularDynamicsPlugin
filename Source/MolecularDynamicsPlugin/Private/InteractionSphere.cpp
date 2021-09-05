// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSphere.h"

#include "Kismet/KismetMathLibrary.h"

void AInteractionSphere::BeginPlay()
{
	Super::BeginPlay();
}

AInteractionSphere::AInteractionSphere()
{
	OnActorBeginOverlap.AddDynamic(this, &AInteractionSphere::AddInteraction);
	OnActorEndOverlap.AddDynamic(this, &AInteractionSphere::EndInteraction);
}

void AInteractionSphere::AddInteraction(AActor* OverlappedActor, AActor* OtherActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("AInteractionSphere::AddInteraction() Called"));
	//UE_LOG(LogTemp, Warning, TEXT("AInteractionSphere::AddInteraction() OverlappedActor:%s - OtherActor:%s"),*OverlappedActor->GetActorLabel(), *OtherActor->GetActorLabel());
	//PrintInteractions();
	//Only add OH Bonds
	AInteractionSphere* InteractingActor = Cast<AInteractionSphere>(OtherActor);
	if((this->Symbol == "H" && InteractingActor->Symbol == "O") || (this->Symbol == "O" && InteractingActor->Symbol == "H"))
	{
		Interactions.Add(InteractingActor);
//		PrintInteractions();
	}
}

void AInteractionSphere::EndInteraction(AActor* OverlappedActor, AActor* OtherActor)
{
	//UE_LOG(LogTemp, Warning, TEXT("AInteractionSphere::EndInteraction() Called"));
	//UE_LOG(LogTemp, Warning, TEXT("AInteractionSphere::AddInteraction() OverlappedActor:%s - OtherActor:%s"), *OverlappedActor->GetActorLabel(), *OtherActor->GetActorLabel());
	//PrintInteractions();
	AInteractionSphere* InteractingActor = Cast<AInteractionSphere>(OtherActor);
	if ((this->Symbol == "H" && InteractingActor->Symbol == "O") || (this->Symbol == "O" && InteractingActor->Symbol == "H"))
	{
		Interactions.Remove(InteractingActor);
	//	PrintInteractions();
	}
}

float AInteractionSphere::GetElectrostaticForce(float Charge1, float Charge2, float Distance)
{
	float ElectrostaticEnergy = USimulationConstants::COULOMBS_CONSTANT_SCALED * Charge1 * Charge2 / (Distance * Distance);
	UE_LOG(LogTemp, Warning, TEXT("AInteractionSphere::GetElectrostaticEnergy(%f, %f, %f) K_e:%e ElectrostaticEnergy:%e"), Charge1, Charge2, Distance, USimulationConstants::COULOMBS_CONSTANT_SCALED, ElectrostaticEnergy);
	return ElectrostaticEnergy;
}

float AInteractionSphere::GetElementaryCharge(AInteractionSphere* InteractionSphere)
{
	float ElemCharge = 0.f;
	//if Atom is H
	if(InteractionSphere->Symbol == "H")
	//if(InteractionSphere->Atom->GetSymbol() == "H")
	{
		ElemCharge = 0.417f;
	}
	//if Atom is O
	else if (InteractionSphere->Symbol =="O")
	//else if (InteractionSphere->Atom->GetSymbol() =="O")
	{
		ElemCharge = -0.834f;
	}
	return ElemCharge;
}


float AInteractionSphere::GetInteractionDistance(AInteractionSphere* Interaction)
{
	return ((this->GetActorLocation() - Interaction->GetActorLocation()) / SimulationData->GetSimulation()->GetActorScale()).Size();
}

float AInteractionSphere::GetInteractionEnergy(AInteractionSphere* Interaction)
{
	float LJEpsilon = GetLJEpsilon(Interaction);
	float LJSigma = GetLJSigma(Interaction);
	float Distance = GetInteractionDistance(Interaction);
	float VDWEnergy = GetVDWForce(LJEpsilon, LJSigma, Distance);
	float ElemCharge1 = GetElementaryCharge(this);
	float ElemCharge2 = GetElementaryCharge(Interaction);
	float ElectrostaticEnergy = GetElectrostaticForce(ElemCharge1, ElemCharge2, Distance);
	float InteractionEnergy = VDWEnergy + ElectrostaticEnergy;

	UE_LOG(LogTemp, Warning, TEXT("AInteractionSphere::GetInteractionEnergy() TotalEnergy: %e"), InteractionEnergy);
	
	return InteractionEnergy;
}

FVector AInteractionSphere::GetInteractionForce(AInteractionSphere* Interaction)
{
	/*
	float EnergyTotal = GetInteractionEnergy(Interaction);

	float DistanceX = ((this->GetActorLocation().X - Interaction->GetActorLocation().X) / SimulationData.Simulation->GetActorScale().Size());
	float DistanceY = ((this->GetActorLocation().Y - Interaction->GetActorLocation().Y) / SimulationData.Simulation->GetActorScale().Size());
	float DistanceZ = ((this->GetActorLocation().Z - Interaction->GetActorLocation().Z) / SimulationData.Simulation->GetActorScale().Size());
	float ForceX = -1 * (EnergyTotal / DistanceX);
	float ForceY = -1 * (EnergyTotal / DistanceY);
	float ForceZ = -1 * (EnergyTotal / DistanceZ);

	*/
	//FVector PositionDifference = this->GetActorLocation() - Interaction->GetActorLocation();
	//Scale positiondistance
	//PositionDifference = PositionDifference / SimulationData.Simulation->GetActorScale().Size();

	/*
	float ForceMag = GetInteractionEnergy(Interaction);
	ForceMag = FMath::Min(ForceMag, USimulationConstants::MAX_INTERACTION_FORCE);
	FVector InteractionDirection = UKismetMathLibrary::GetDirectionUnitVector(this->GetActorLocation(), Interaction->GetActorLocation());
	InteractionDirection = InteractionDirection * -1.0f;
	FVector InteractionForce = InteractionDirection * ForceMag;
	*/

	float Distance = GetInteractionDistance(Interaction);
	//UE_LOG(LogTemp, Warning, TEXT("AInteractionSphere::GetInteractionForce() called, this:%s - Interaction:%s - InteractionDistance:%f"), *this->GetName(), *Interaction->GetName(), Distance);
	float ForceMag = SimulationData->GetInteractionForceTable()->Lookup(Distance);
	ForceMag = ForceMag * 0.01f;
	
	FVector InteractionDirection = UKismetMathLibrary::GetDirectionUnitVector(Interaction->GetActorLocation(), this->GetActorLocation() );
	FVector InteractionForce = InteractionDirection * ForceMag;
	
	return InteractionForce;
}

float AInteractionSphere::GetLJEpsilon(AInteractionSphere* Interaction)
{
	float LJEpsilon = 0.f;
	//check if HH
	if(this->Symbol == "H" && Interaction->Symbol == "H")
	//if(this->Atom->GetSymbol() == "H" && Interaction->Atom->GetSymbol() == "H")
	{
		LJEpsilon = 0.0460f;
	}
	//check if OO
	else if (this->Symbol == "O" && Interaction->Symbol == "O")
	//else if (this->Atom->GetSymbol() == "O" && Interaction->Atom->GetSymbol() == "O")
	{
		LJEpsilon = 0.1521f;
	}
	//Check if HO or OH
	else if((this->Symbol == "H" && Interaction->Symbol == "O") || (this->Symbol == "O" && Interaction->Symbol == "H"))
	//else if((this->Atom->GetSymbol() == "H" && Interaction->Atom->GetSymbol() == "O") || (this->Atom->GetSymbol() == "O" && Interaction->Atom->GetSymbol() == "H"))
	{
		LJEpsilon = 0.0836f;
	}
	//Scale LJEpsilon
	LJEpsilon = LJEpsilon * USimulationConstants::KJ_TO_UEJ * (1 / USimulationConstants::AVOGADRO);
	return LJEpsilon;
}

float AInteractionSphere::GetLJSigma(AInteractionSphere* Interaction)
{
	float LJSigma = 0.f;
	//check if HH
	if (this->Symbol == "H" && Interaction->Symbol == "H")
	//if (this->Atom->GetSymbol() == "H" && Interaction->Atom->GetSymbol() == "H")
	{
		//LJSigma = 0.4000f; //In nm
		//LJSigma = 400.0f; //In pm pm from Nm
		LJSigma = 40.00f; //In pm from Angstroms	
	}
	//check if OO
	else if (this->Symbol == "O" && Interaction->Symbol == "O")
	//else if (this->Atom->GetSymbol() == "O" && Interaction->Atom->GetSymbol() == "O")
	{
		//LJSigma = 3.1507; //In nm
		//LJSigma = 3150.7; //In pm from Nm
		LJSigma = 315.07; //In pm from Angstroms
	}
	//Check if HO or OH
	else if ((this->Symbol == "H" && Interaction->Symbol == "O") || (this->Symbol == "O" && Interaction->Symbol == "H"))
	//else if ((this->Atom->GetSymbol() == "H" && Interaction->Atom->GetSymbol() == "O") || (this->Atom->GetSymbol() == "O" && Interaction->Atom->GetSymbol() == "H"))
	{
		//LJSigma = 1.7753; //In nm
		//LJSigma = 1775.3; //In pm pm from Nm
		LJSigma = 177.53; //In pm from Angstroms
	}
	return LJSigma;
}

float AInteractionSphere::GetVDWForce(float LJEpsilon, float LJSigma, float Distance)
{
	//Jun VDW
	//float VDWEnergy = (FMath::Pow((LJSigma / Distance), 12.f) - (2 * FMath::Pow((LJSigma / Distance), 6.f))) * LJEpsilon;
	//Rob VDW 
	//float VDWEnergy = 4 * LJEpsilon * (FMath::Pow((LJSigma/Distance),12) - FMath::Pow((LJSigma / Distance),6));
	//Rob VDW V2
	float SR = LJSigma / Distance;
	float SR6 = SR * SR * SR * SR * SR * SR;
	float VDWEnergy = (LJEpsilon * 6.0f * (2.0f * SR6 * SR6 - SR6)/ Distance);
	
	UE_LOG(LogTemp, Warning, TEXT("AInteractionSphere::GetVDWEnergy(%f, %f, %f) VDWEnergy: %e"), LJEpsilon, LJSigma, Distance, VDWEnergy);
	
	return VDWEnergy;
}

void AInteractionSphere::InitInteractionSphere(FString AtomSymbol, USimulationData* Simulation, USphereComponent* CollisionSphere)
//void AInteractionSphere::InitInteractionSphere(UAtom* ParentAtom, FSimulationData& Simulation)
{
	Symbol = AtomSymbol;
	PhysicsComponent = CollisionSphere;
	//Atom = ParentAtom;
	this->SimulationData = Simulation;
}

void AInteractionSphere::PrintInteractions()
{
	//UE_LOG(LogTemp, Warning, TEXT("AInteractionSphere::PrintInteractions() called."));
	if(Interactions.Num() > 0)
	{
		for(AInteractionSphere* Interaction : Interactions)
		{
			UE_LOG(LogTemp, Warning, TEXT("AInteractionSphere::PrintInteractions() %s-%s Interaction With: %s - Distance: %f"), *Symbol, *Interaction->Symbol, *Interaction->GetActorLabel(), GetInteractionDistance(Interaction));
			//UE_LOG(LogTemp, Warning, TEXT("AInteractionSphere::PrintInteractions() %s-%s Interaction With: %s - Distance: %f"), *Atom->GetSymbol(), *Interaction->Atom->GetSymbol(), *Interaction->GetActorLabel(), GetInteractionDistance(Interaction));
			
		}
	}
}

void AInteractionSphere::UpdateForces()
{
	if(Interactions.Num() > 0 && PhysicsComponent->IsSimulatingPhysics())
	{
		FVector TotalForces = FVector(0.f);
		
		//Get the sum of forces on this atom
		for(AInteractionSphere* Interaction : Interactions)
		{
			// only include OH interactions.
			if ((this->Symbol == "H" && Interaction->Symbol == "O") || (this->Symbol == "O" && Interaction->Symbol == "H"))
				TotalForces += GetInteractionForce(Interaction);
		}
		
		//Apply the force to the atom
		// Scale the force down before applying
		//TotalForces = TotalForces * 0.1;
		
		//UE_LOG(LogTemp, Warning, TEXT("AInteractionSphere::UpdateForces() Total Force:%s"), *TotalForces.ToString());
		//UE_LOG(LogTemp, Warning, TEXT("AInteractionSphere::UpdateForces(%s) Total Force:X=%e Y=%e Z=%e"), *this->GetName(), TotalForces.X, TotalForces.Y, TotalForces.Z);
		

		PhysicsComponent->AddForce(TotalForces);
	}
}

