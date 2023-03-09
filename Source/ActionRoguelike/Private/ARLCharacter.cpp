// Copyright Tom Looman & Stanford University (CS193U)

#include "ARLCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "DrawDebugHelpers.h"


AARLCharacter::AARLCharacter()
{
	AActor::PrimaryActorTick.bCanEverTick = true;
	APawn::AutoPossessPlayer = EAutoReceiveInput::Player0;

	this->SpringArmComponent = UObject::CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	this->SpringArmComponent->USceneComponent::SetupAttachment(AActor::RootComponent); // Capsule component
	this->SpringArmComponent->bUsePawnControlRotation = true;

	this->CameraComponent = UObject::CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	this->CameraComponent->USceneComponent::SetupAttachment(this->SpringArmComponent);

	ACharacter::GetCharacterMovement()->bOrientRotationToMovement = true;
	APawn::bUseControllerRotationYaw = false;
}

void AARLCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AARLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// -- Rotation Visualization -- //
	constexpr float DrawScale = 100.0f;
	constexpr float Thickness = 2.0f;

	FVector LineStart = GetActorLocation();

	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.0f;

	// Set line end in direction of the actor's forward
	const FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.0f);

	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);

	const FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);

	// Draw 'Controller' Rotation ('PlayerController' that 'possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
}

void AARLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AARLCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AARLCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", EInputEvent::IE_Pressed, this, &AARLCharacter::PrimaryAttack);
}

void AARLCharacter::MoveForward(float AxisValue)
{
	// Where the actor is looking at
	FRotator ControlRot = APawn::GetControlRotation();
	ControlRot.Roll = 0.0f;
	ControlRot.Pitch = 0.0f;

	// Move the character where it's facing at
	// APawn::AddMovementInput(AActor::GetActorForwardVector(), AxisValue);

	// Turn the character where the camera is looking at
	APawn::AddMovementInput(ControlRot.Vector(), AxisValue);
}

void AARLCharacter::MoveRight(float AxisValue)
{
	// Where the actor is looking at
	FRotator ControlRot = APawn::GetControlRotation();
	ControlRot.Roll = 0.0f;
	ControlRot.Pitch = 0.0f;

	const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

	// Turn the character 90 degrees left or right to its forward vector
	//APawn::AddMovementInput(AActor::GetActorRightVector(), AxisValue);

	// Turn the character 90 degrees left or right to where the camera is looking at
	APawn::AddMovementInput(RightVector, AxisValue);
}


void AARLCharacter::PrimaryAttack()
{
	// Get Socket name from skeletal mesh
	FVector RightHandLocation = ACharacter::GetMesh()->USceneComponent::GetSocketLocation("Muzzle_01");

	FTransform SpawnTransformMatrix = FTransform(APawn::GetControlRotation(), RightHandLocation);

	FActorSpawnParameters SpawnParams;
	// Specify spawn rules
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawn Actor
	AActor::GetWorld()->UWorld::SpawnActor<AActor>(this->ProjectileClass, SpawnTransformMatrix, SpawnParams);
}
