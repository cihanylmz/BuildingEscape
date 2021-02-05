// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "GameFrameWork/PlayerController.h"
#include "OpenDoor.h"
#include "GameFrameWork/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{

	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw += InitialYaw;
	Super::BeginPlay();
	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has open door component, but no pressure plate."), *(GetOwner()->GetName()));
	}
	ActorThatEnters = GetWorld()->GetFirstPlayerController()->GetPawn();
	//*ActorThatEnters = GetWorld()->GetFirstLocalPlayerFromController().
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatEnters))
	{
		OpenDoor(DeltaTime);
		TimeOfOpen = GetWorld()->GetTimeSeconds();
	}
	else {
		if (GetWorld()->GetTimeSeconds() - TimeOfOpen > DoorClosingDelay)
		{
			CloseDoor(DeltaTime);
		}
	}
	
		
	
}

void UOpenDoor::OpenDoor(float DeltaTime) {
	
	FRotator OpenDoor = GetOwner()->GetActorRotation();
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, 2);
	//UE_LOG(LogTemp, Warning, TEXT("%s %f"), *(GetOwner()->GetName()),finish);
	GetOwner()->SetActorRotation(OpenDoor);
}

void UOpenDoor::CloseDoor(float DeltaTime) {

	FRotator OpenDoor = GetOwner()->GetActorRotation();
	CurrentYaw = GetOwner()->GetActorRotation().Yaw;
	OpenDoor.Yaw = FMath::FInterpTo(CurrentYaw, InitialYaw, DeltaTime, 4);
	//UE_LOG(LogTemp, Warning, TEXT("%s %f"), *(GetOwner()->GetName()),finish);
	GetOwner()->SetActorRotation(OpenDoor);
}



