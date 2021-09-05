// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//#include "Atom.h"
#include "SimulationData.h"
#include "SimulationConstants.h"
#include "Components/SphereComponent.h"
#include "Engine/TriggerSphere.h"
#include "InteractionSphere.generated.h"

/**
 * 
 */
UCLASS()
class AInteractionSphere : public ATriggerSphere
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AInteractionSphere();

	UFUNCTION()
	void AddInteraction(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	void EndInteraction(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
	float GetElectrostaticForce(float Charge1, float Charge2, float Distance);

	UFUNCTION()
	float GetElementaryCharge(AInteractionSphere* InteractionSphere);
	
	UFUNCTION()
	float GetInteractionDistance(AInteractionSphere* Interaction);

	UFUNCTION()
	float GetInteractionEnergy(AInteractionSphere* Interaction);

	UFUNCTION()
	FVector GetInteractionForce(AInteractionSphere* Interaction);

	//FIXME - This needs to be rewritten to read Epsilon values from AtomData
	// Reads In KJ/Mol
	// outputs in UEJ
	UFUNCTION()
	float GetLJEpsilon(AInteractionSphere* Interaction);
	
	//FIXME - This needs to be rewritten to read Sigma values from AtomData
	//Referenced in nm converted to pm though
	//outputs in pm
	UFUNCTION()
	float GetLJSigma(AInteractionSphere* Interaction);

	UFUNCTION()
	float GetVDWForce(float LJEpsilon, float LJSigma, float Distance);

	UFUNCTION()
	void InitInteractionSphere(FString AtomSymbol, USimulationData* Simulation, USphereComponent* CollisionSphere);
	//void InitInteractionSphere(UAtom* ParentAtom, FSimulationData& Simulation);

	UFUNCTION()
	void PrintInteractions();

	UFUNCTION()
	void UpdateForces();

public:
	//UAtom* Atom;

	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	FString Symbol;
	
	UPROPERTY(VisibleAnywhere, Category = "Simulation")
	TArray<AInteractionSphere*> Interactions;

	USimulationData* SimulationData;

	USphereComponent* PhysicsComponent;

};
