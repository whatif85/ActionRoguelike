// Copyright Tom Looman & Stanford University (CS193U)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARLMagicProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROGUELIKE_API AARLMagicProjectile : public AActor
{
private:
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp{ nullptr };

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComp{ nullptr };

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* EffectComp{ nullptr };

	
public:	
	AARLMagicProjectile();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
