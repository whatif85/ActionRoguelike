// Copyright Tom Looman & Stanford University (CS193U)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARLCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ACTIONROGUELIKE_API AARLCharacter : public ACharacter
{
private:
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass; // Blueprint class

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent{ nullptr };

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent{ nullptr };


public:
	AARLCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void MoveForward(float AxisValue);

	void MoveRight(float AxisValue);

	void PrimaryAttack();
};
