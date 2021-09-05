// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CommonAnimTypes.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "Molecule.h"
#include "GameFramework/SpringArmComponent.h"
#include "Math/Axis.h"
#include "TeleportWall.generated.h"

/**
 * 
 */
UCLASS()
class ATeleportWall : public ATriggerBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ATeleportWall();

	UFUNCTION()
	void EnterTeleporter(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void ExitTeleporter(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
	void InitTeleporter(ATeleportWall* PairingTeleporter, TEnumAsByte<EAxis::Type> Axis);

	void PrintBothArrays();
	
	void PrintTeleporterArray();
	
	UFUNCTION()
	void SetBoxExtent(FVector NewExtent);

	UPROPERTY(EditAnywhere, Category = "Simulation")
	ATeleportWall* PairedTeleporter;

	UPROPERTY(EditAnywhere, Category = "Simulation")
	TEnumAsByte<EAxis::Type> TeleportAxis;
	
	//UPROPERTY(VisibleAnywhere, Category = "Simulation")
	//bool bTeleporting;

	TArray<FString> TeleportingMolecules;

	int32 TeleportCount;
};

