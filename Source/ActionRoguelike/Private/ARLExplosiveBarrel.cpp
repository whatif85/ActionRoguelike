// Copyright Tom Looman & Stanford University (CS193U)

#include "ARLExplosiveBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"


AARLExplosiveBarrel::AARLExplosiveBarrel()
{
	this->MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	this->MeshComp->SetSimulatePhysics(true);
	this->MeshComp->SetNotifyRigidBodyCollision(false); // avoid physics affect explosion events when touching other objects (such as the floor)
	// Enabling Simulate physics automatically changes the Profile to PhysicsActor in Blueprint, in C++ we need to change this manually.
	this->MeshComp->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);
	RootComponent = this->MeshComp;

	this->ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComponent");
	this->ForceComp->SetupAttachment(this->MeshComp);

	// Leaving this on applies small constant force via component 'tick' (Optional)
	this->ForceComp->SetAutoActivate(false);

	this->ForceComp->Radius = 750.0f;
	this->ForceComp->ImpulseStrength = 2500.0f; // Alternative: 200000.0 if bImpulseVelChange = false
	// Optional, ignores 'Mass' of other objects (if false, the impulse strength will be much higher to push most objects depending on Mass)
	this->ForceComp->bImpulseVelChange = true;

	// Optional, default constructor of component already adds 4 object types to affect, excluding WorldDynamic
	this->ForceComp->AddCollisionChannelToAffect(ECollisionChannel::ECC_WorldDynamic);

	// Binding either in constructor or in PostInitializeComponents() below
	//this->MeshComp->OnComponentHit.AddDynamic(this, &AARLExplosiveBarrel::OnActorHit);
}


void AARLExplosiveBarrel::PostInitializeComponents()
{
	// Don't forget to call parent function
	Super::PostInitializeComponents();

	MeshComp->OnComponentHit.AddDynamic(this, &AARLExplosiveBarrel::OnActorHit);
}


void AARLExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();

	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, TEXT("OnActorHit in Explosive Barrel"));

	// %s = string
	// %f = float
	// logs: "OtherActor: MyActor_1, at gametime: 124.4" 
	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Green, FString::Printf(TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds));
	//UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	const FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.0f, true);

	// Detailed info on logging in ue4
	// https://nerivec.github.io/old-ue4-wiki/pages/logs-printing-messages-to-yourself-during-runtime.html

}
