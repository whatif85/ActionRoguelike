// Copyright Tom Looman & Stanford University (CS193U)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARLCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UARLInteractionComponent;
class UAnimMontage;

UCLASS()
class ACTIONROGUELIKE_API AARLCharacter : public ACharacter
{
private:
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> BP_MagicProjectile;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim{ nullptr };

	FTimerHandle TimerHandle_PrimaryAttack;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	USpringArmComponent* SpringArmComp{ nullptr };

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	UCameraComponent* CameraComp{ nullptr };

	UPROPERTY(VisibleAnywhere, Category = "Interaction")
	UARLInteractionComponent* InteractionComp{ nullptr };

	
public:
	AARLCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(const float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveForward(const float AxisValue);

	void MoveRight(const float AxisValue);

	void PrimaryAttack();
	void PrimaryAttack_TimeElapsed() const;

	void PrimaryInteract();
};
