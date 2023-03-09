// Copyright Tom Looman & Stanford University (CS193U)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARLItemChest.generated.h"


class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API AARLItemChest : public AActor
{
private:
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh{ nullptr };

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LidMesh{ nullptr };

	
public:	
	AARLItemChest();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
