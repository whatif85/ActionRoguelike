// Copyright Tom Looman & Stanford University (CS193U)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARLGameplayInterface.h"
#include "ARLItemChest.generated.h"


class UStaticMeshComponent;

UCLASS()
class ACTIONROGUELIKE_API AARLItemChest : public AActor, public IARLGameplayInterface
{
private:
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float TargetPitch;

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

private:
	// The "_Implementation" suffix is added because the base function is a BlueprintNativeEvent
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;
};
