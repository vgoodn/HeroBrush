// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupComponent.h"

UPickupComponent::UPickupComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;
}

void UPickupComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	OnComponentBeginOverlap.AddDynamic(this, &UPickupComponent::OnSphereBeginOverlap);
}

void UPickupComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	AHeroBrushCharacter* Character = Cast<AHeroBrushCharacter>(OtherActor);
	if (Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
	}
}