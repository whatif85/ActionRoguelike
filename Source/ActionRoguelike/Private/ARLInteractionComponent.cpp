// Copyright Tom Looman & Stanford University (CS193U)

#include "ARLInteractionComponent.h"

#include "ARLGameplayInterface.h"


UARLInteractionComponent::UARLInteractionComponent()
{
	UActorComponent::PrimaryComponentTick.bCanEverTick = true;

}

void UARLInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UARLInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UARLInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);

	AActor* MyOwner = UActorComponent::GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;

	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	// Limit interaction line to 1 meter
	FVector EndPoint = EyeLocation + (EyeRotation.Vector() * 100);
	
	//FHitResult Hit;

	// Find anything that is WorldDynamic (By Object Type)
	//bool bBlockingHit = UActorComponent::GetWorld()->UWorld::LineTraceSingleByObjectType(Hit, EyeLocation, EndPoint, ObjectQueryParams);

	TArray<FHitResult> Hits;

	float CollisionRadius = 30.0f;

	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(CollisionRadius);
	
	// FQuat::Identity = No rotation applied
	bool bBlockingHit = UActorComponent::GetWorld()->UWorld::SweepMultiByObjectType(Hits, EyeLocation, EndPoint, FQuat::Identity, ObjectQueryParams, CollisionShape);

	FColor LineColorCheck = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			// IMPORTANT: Implements requires the interface's UCLASS, not the interface itself!
			if (HitActor->Implements<UARLGameplayInterface>() == true)
			{
				// Safe cast does not require to check if nullptr
				APawn* MyPawn = Cast<APawn>(MyOwner);

				IARLGameplayInterface::Execute_Interact(HitActor, MyPawn);
			}
		}

		DrawDebugSphere(UActorComponent::GetWorld(), Hit.ImpactPoint, CollisionRadius, 32, LineColorCheck, false, 2.0f);
	}	
	
	DrawDebugLine(UActorComponent::GetWorld(), EyeLocation, EndPoint, LineColorCheck, false, 2.0f, 0, 2.0f);
}
