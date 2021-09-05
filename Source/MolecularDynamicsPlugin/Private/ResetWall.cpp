// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetWall.h"

#include "Components/BoxComponent.h"

AResetWall::AResetWall()
{
	OnActorBeginOverlap.AddDynamic(this, &AResetWall::ResetActor);
}

void AResetWall::BeginPlay()
{
	Super::BeginPlay();
}

void AResetWall::ResetActor(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("AResetWall::ResetActor() called."));
	//Check if there is an OtherActor, and that the OtherActor is not this Actor.
	if (OtherActor && OtherActor != this)
	{
		AMolecule* Molecule = Cast<AMolecule>(OtherActor);
		//Check if the other actor is AMolecule
		if (Molecule)
		{
			Molecule->ResetMolecule();
		}
	}
}

void AResetWall::SetBoxExtent(FVector NewExtent)
{
	UShapeComponent* Shape = GetCollisionComponent();
	Cast<UBoxComponent>(Shape)->SetBoxExtent(NewExtent);
	Cast<UBoxComponent>(Shape)->SetCollisionProfileName("ResetWall");
}
