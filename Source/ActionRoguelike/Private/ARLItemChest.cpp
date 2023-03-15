// Copyright Tom Looman & Stanford University (CS193U)

#include "ARLItemChest.h"

#include "Components/StaticMeshComponent.h"


AARLItemChest::AARLItemChest()
{
	AActor::PrimaryActorTick.bCanEverTick = true;

	this->BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	AActor::RootComponent = this->BaseMesh;

	this->LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	this->LidMesh->SetupAttachment(this->BaseMesh);

	this->TargetPitch = 110.0f;
}

void AARLItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARLItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AARLItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	this->LidMesh->SetRelativeRotation(FRotator(this->TargetPitch, 0.0f, 0.0f));
}

