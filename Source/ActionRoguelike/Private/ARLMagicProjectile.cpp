// Copyright Tom Looman & Stanford University (CS193U)

#include "ARLMagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"


AARLMagicProjectile::AARLMagicProjectile()
{
	AActor::PrimaryActorTick.bCanEverTick = true;

	this->SphereComp = UObject::CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	// Example to set collision without profile
	//this->SphereComp->UPrimitiveComponent::SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	//this->SphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//this->SphereComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	// Use collision profile defined in Collision from Project Settings
	this->SphereComp->UPrimitiveComponent::SetCollisionProfileName("Projectile");
	AActor::RootComponent = this->SphereComp;

	this->EffectComp = UObject::CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComponent"));
	this->EffectComp->USceneComponent::SetupAttachment(this->SphereComp);

	this->ProjectileMovementComp = UObject::CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	this->ProjectileMovementComp->InitialSpeed = 1000.0f;
	this->ProjectileMovementComp->bRotationFollowsVelocity = true;
	this->ProjectileMovementComp->bInitialVelocityInLocalSpace = true;
	this->ProjectileMovementComp->ProjectileGravityScale = 0.0f;
}

void AARLMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARLMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

