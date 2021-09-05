// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "Molecule.h"
#include "ResetWall.generated.h"

/**
 *
 */
UCLASS()
class AResetWall : public ATriggerBox
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	AResetWall();

	UFUNCTION()
		void ResetActor(class AActor* OverlappedActor, class AActor* OtherActor);

	UFUNCTION()
		void SetBoxExtent(FVector NewExtent);

};

