// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SimulationCell.generated.h"

UCLASS()
class ASimulationCell : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASimulationCell();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
		float GetVolume();

	UFUNCTION()
		float GetWidth();

	UFUNCTION()
		void InitVolume(float CellWidth);

	//LineThickness is a protected member, we will have to add a different representation to adjust this value.
	//UFUNCTION()
	//void SetLineThickness(float LineThickness);

	UFUNCTION()
		void SetShapeColor(FColor LineColor);

	UFUNCTION()
		void SetWidth(float CellWidth);

	/**
	 * sets the dimensions based upon a desired volume
	 * @param Volume: The desired volume in Cubic Unreal Units. 1 UU = 1 pM
	 */
	UFUNCTION()
		void SetVolume(float Volume);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Simulation)
		UBoxComponent* SimulationVolume;

};
