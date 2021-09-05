// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportWall.h"

#include "Components/BoxComponent.h"

ATeleportWall::ATeleportWall()
{
	OnActorBeginOverlap.AddDynamic(this, &ATeleportWall::EnterTeleporter);
	OnActorEndOverlap.AddDynamic(this, &ATeleportWall::ExitTeleporter);
}

void ATeleportWall::BeginPlay()
{
	Super::BeginPlay();
}

void ATeleportWall::EnterTeleporter(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::EnterTeleporter() called."));
	//Check if there is an OtherActor, and that the OtherActor is not this Actor.
	if(OtherActor && OtherActor != this)
	{
		//Check if there is a paired teleporter. 
		if(PairedTeleporter)
		{
			//UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::EnterTeleporter() Has Paired Teleporter."));
			AMolecule* Molecule = Cast<AMolecule>(OtherActor);
			//Check if the other actor is AMolecule
			if(Molecule)
			{
				UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::EnterTeleporter() Molecule Exists ID:%s."), *Molecule->GetName());
				FVector TeleporterLocation = PairedTeleporter->GetActorLocation();
				FVector MoleculeLocation = Molecule->GetActorLocation();
				FVector TeleportLocation;
				bool bTeleport = false;
				//Check that the molecule did not just teleport from the paired Actor (PairedTeleporter !bTeleporting)
				//first check if the teleporting array is empty
				PrintBothArrays();
				if(PairedTeleporter->TeleportingMolecules.Num() <= 0)
				{
					UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::EnterTeleporter() PairedTeleport->TeleportingArray of Molecules is Empty - Adding %s to Array of Teleporting Molecules."), *Molecule->GetName());
					bTeleport = true;
				}
				//if the array is not empty, check if the paired teleporter has a matching molecule ID in its teleporting array
				else if(!PairedTeleporter->TeleportingMolecules.Contains(Molecule->GetName()))
				{
					UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::EnterTeleporter() PairedTeleport->TeleportingArray of Molecules is NOT Empty, %s was not found in the Array - Adding %s to Array of Teleporting Molecules."), *Molecule->GetName(), *Molecule->GetName());
					bTeleport = true;
				}				
				//If a teleport should occur, add the current molecule ID to the local Array of Teleporting Molecules and perform the teleportation. 
				if(bTeleport)
				{
					UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::EnterTeleporter() TeleportingMolecule - Adding %s to Array of Teleporting Molecules."), *Molecule->GetName());
					TeleportingMolecules.Add(*Molecule->GetName());

					PrintBothArrays();
					//UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::EnterTeleporter() TeleportingArray:%s"), *TeleportingMolecules.ToString());
					switch (TeleportAxis)
					{
					case EAxis::X:
						UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::EnterTeleporter() Teleporting X."));
						TeleportLocation = FVector(TeleporterLocation.X, MoleculeLocation.Y, MoleculeLocation.Z);
						Molecule->SetActorLocation(TeleportLocation);
						break;
					case EAxis::Y:
						UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::EnterTeleporter() Teleporting Y."));
						TeleportLocation = FVector(MoleculeLocation.X, TeleporterLocation.Y, MoleculeLocation.Z);
						Molecule->SetActorLocation(TeleportLocation);
						break;
					case EAxis::Z:
						UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::EnterTeleporter() Teleporting Z."));
						TeleportLocation = FVector(MoleculeLocation.X, MoleculeLocation.Y, TeleporterLocation.Z);
						Molecule->SetActorLocation(TeleportLocation);
						break;
					}	
				}
			}	
		}
	}
}

void ATeleportWall::ExitTeleporter(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::ExitTeleporter() called."));
	//Check if there is an OtherActor, and that the OtherActor is not this Actor.
	if(OtherActor && OtherActor != this)
	{
		//if(PairedTeleporter && !bTeleporting)
		//Check if there is a paired teleporter. 
		if(PairedTeleporter)
		{
			//UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::ExitTeleporter() Has Paired Teleporter."));
			//PairedTeleporter->bTeleporting = false;
			//Check if the other actor is AMolecule
			AMolecule* Molecule = Cast<AMolecule>(OtherActor);
			if (Molecule)
			{
				bool bTeleported = false;
				UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::ExitTeleporter() Molecule Exists ID:%s."), *Molecule->GetName());
				//Check if this is teleporting that molecule
				//first check if this Teleporting Array is empty()
				PrintBothArrays();
				if (TeleportingMolecules.Num() <= 0)
				{
					UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::ExitTeleporter() TeleportingArray of Molecules is Empty - Removing %s from pairedteleporter Array of Teleporting Molecules."), *Molecule->GetName());
					bTeleported = true;
				}
				else if (!TeleportingMolecules.Contains(Molecule->GetName()))
				{
					UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::ExitTeleporter() TeleportingArray of Molecules is NOT Empty, %s was not found in the Array - Removing %s from PairedTeleporter Array of Teleporting Molecules."), *Molecule->GetName(), *Molecule->GetName());
					bTeleported = true;
				}
				//A Teleport has occurred remove the molecule from the paired teleporters Array
				if(bTeleported)
				{
					UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::ExitTeleporter() Removing Molecule from PairedTeleporter."));
					PairedTeleporter->TeleportingMolecules.Remove(Molecule->GetName());
					PrintBothArrays();
				}
			}
		}
	}
}

void ATeleportWall::InitTeleporter(ATeleportWall* PairingTeleporter, TEnumAsByte<EAxis::Type> Axis)
{
	PairedTeleporter = PairingTeleporter;
	TeleportAxis = Axis;
}

void ATeleportWall::PrintBothArrays()
{
	UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::PrintBothArrays() TeleportingMolecules.Num():%d - PairedTeleporter->TeleportingMolecules.Num():%d."), TeleportingMolecules.Num(), PairedTeleporter->TeleportingMolecules.Num());
	
	UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::PrintBothArrays() ---this->TeleportingMolecules."));
	this->PrintTeleporterArray();
	
	UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::PrintBothArrays() ---PairedTeleporter->TeleportingMolecules."));
	PairedTeleporter->PrintTeleporterArray();
}


void ATeleportWall::PrintTeleporterArray()
{
	for(FString Molecule : TeleportingMolecules)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATeleportWall::PrintTeleporterArray() ------Molecule ID:%s."), *Molecule);
	}
}

void ATeleportWall::SetBoxExtent(FVector NewExtent)
{
	UShapeComponent* Shape = GetCollisionComponent();
	Cast<UBoxComponent>(Shape)->SetBoxExtent(NewExtent);
	Cast<UBoxComponent>(Shape)->SetCollisionProfileName("TeleportWall");
}
