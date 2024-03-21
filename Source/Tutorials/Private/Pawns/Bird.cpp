// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h" // Needed for UCapsuleComponent to work
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Set a capsule collision and set it as a root component
	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collision"));

	// Access the size variables of the CapsuleCollision component in C++
	CapsuleCollision->SetCapsuleHalfHeight(220.f);
	CapsuleCollision->SetCapsuleRadius(125.f);

	// RootComponent = CapsuleCollision;	// 1st method to set a capsule collision as a root component
	SetRootComponent(CapsuleCollision);		// 2nd method to set a capsule collision as a root component


	// Set a skeletal mesh
	BirdSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Bird Skeletal Mesh"));
	// Attach a skeletal mesh to the root
	BirdSkeletalMesh->SetupAttachment
	(
		GetRootComponent() // Could be RootComponent or CapsuleCollision as well
	);


	// Set a spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 120.f; // Distance between ViewCamera and the endpoint of the Spring Arm
	SpringArm->SocketOffset = FVector(0.f, 0.f, 40.f); // Set Spring Arm location offset
	
	// Set a spring arm rotation to Y = -10
	FTransform newSpringArmTransform = SpringArm->GetRelativeTransform(); // Get current transform for new transform
	float rotationInDegrees = -10.f;									  // Set new rotation for Y and store in variable
	float rotationInRadians = FMath::DegreesToRadians(rotationInDegrees); // Convert new rotation to radians
	FRotator newSpringArmRotation = FRotator(rotationInDegrees, 0.f, 0.f);// Set new rotation for x,y,z
	newSpringArmTransform.SetRotation(newSpringArmRotation.Quaternion()); // Apply new rotation to new transform
	SpringArm->SetRelativeTransform(newSpringArmTransform);				  // Apply new transform to spring arm


	// Set a camera
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("View Camera"));
	ViewCamera->SetupAttachment(SpringArm);


	// Possess the pawn
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	
	// Set up Enhanced Input for the pawn
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem \
			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			int MappingContextPriority = 1;
			Subsystem->AddMappingContext(BirdMappingContext, MappingContextPriority);
		}
	}
}

//void ABird::MoveForward(float Value)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Move Forward: %f"), Value);
//}

// Set up Move function to work on player input
void ABird::Move(const FInputActionValue& Value)
{
	// const bool CurrentValue = Value.Get<bool>();					/* previously, for learning purposes */ 
	const float DirectionValue = Value.Get<float>();
	// if (CurrentValue){											/* previously, for learning purposes */
	if (Controller && (DirectionValue != 0.f))
	{
		// UE_LOG(LogTemp, Warning, TEXT("IA_Move triggered"));	}	/* previously, for learning purposes */
		FVector ForwardVector = GetActorForwardVector();
		AddMovementInput(ForwardVector, DirectionValue);
	}
}

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Deprecated input system
	/* PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABird::MoveForward); */

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
		// Use CastChecked instead of Cast, so the game will crash if input won't work correctly
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
	}
}

