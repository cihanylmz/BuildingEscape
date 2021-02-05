// Fill out your copyright notice in the Description page of Project Settings.


#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"
#define OUT
// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	// ...
	Handle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Handle) {

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Actor: %s doesnt have Physics Handle Component."), *GetOwner()->GetName());
	}

	GrabInput = GetOwner()->FindComponentByClass<UInputComponent>();
	ReleaseInput = GetOwner()->FindComponentByClass<UInputComponent>();
	GrabInput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	ReleaseInput->BindAction("Release", IE_Pressed, this, &UGrabber::Release);
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grabbed"));
	
}
void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Released"));
	
}
// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLoc, OUT PlayerViewpointRot);
	FVector LineTraceEnd = PlayerViewpointLoc + PlayerViewpointRot.Vector()*Reach;
	FHitResult Grab;
	FCollisionQueryParams Param(FName(TEXT("")), false, GetOwner());

	bool IsHit = GetWorld()->LineTraceSingleByObjectType(
		OUT Grab,
		PlayerViewpointLoc,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		Param
	);

	AActor* GrabbedObject = Grab.GetActor();

	if(IsHit)
	UE_LOG(LogTemp, Warning, TEXT("Grab %s"), *(GrabbedObject->GetName()));
	//if (IsHit)
	//Handle->GrabComponentAtLocation(Grab.GetActor(), Param.OwnerTag, GrabbedObject->GetActorLocation());
	/*DrawDebugLine(
		GetWorld(),
		PlayerViewpointLoc,
		LineTraceEnd,
		FColor{ 0,0,1,1 },
		0,
		0,
		0,
		5.f

	);*/


}

