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
}

void AARLItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARLItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

