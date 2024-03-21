// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemSinCosMovement.h"

// Sets default values
AItemSinCosMovement::AItemSinCosMovement()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float AItemSinCosMovement::TransformedSin()
{
	return MovementAmplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItemSinCosMovement::TransformedCos()
{
	return MovementAmplitude * FMath::Cos(RunningTime * TimeConstant);
}

// Called when the game starts or when spawned
void AItemSinCosMovement::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemSinCosMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	FVector ItemLocation = GetActorLocation();

	// Sinewave movement variables
	RunningTime += DeltaTime;
	// MovementAmplitude = 0.25f; // Don't assign a value in .cpp if EditAnywhere, or the value set
	// TimeConstant = 5.f;		  // in an instance will not apply
	float DeltaX = TransformedSin();
	float DeltaY = TransformedCos();

	// DrawDebugSphere variables
	float DebugSphereRadius = 25.f;
	int32 DebugSphereSegments = 24;
	float DebugSphereLifeTime = -1.f;
	uint8 DebugSphereDepthPriority = 0U;
	float DebugSphereThickness = 1.2f;

	// DrawDebugLine variables
	float DebugLineLifeTime = -1.f;
	uint8 DebugLineDepthPriority = 0U;
	float DebugLineThickness = 1.2f;
	FVector DebugLineForward = GetActorForwardVector();
	FVector DebugLineEnd = ItemLocation + DebugLineForward * 100.f;

	// DrawDebugPoint variables
	float DebugPointSize = 20.f;
	float DebugPointLifeTime = -1.f;
	uint8 DebugPointDepthPriority = 0U;


	// Setting a circular movement
	AddActorWorldOffset(FVector(DeltaX, DeltaY, 0.f));

	// Draw a debug sphere on tick. Notice "bPersistentLines"
	DrawDebugSphere
	(
		World,
		ItemLocation,
		DebugSphereRadius,
		DebugSphereSegments,
		FColor::Red,
		false, // Sphere is not going to be located in a single location, it's going to be moved on every single tick
		DebugSphereLifeTime,
		DebugSphereDepthPriority,
		DebugSphereThickness
	);

	// Draw a debug line
	DrawDebugLine
	(
		World,
		ItemLocation,
		DebugLineEnd,
		FColor::Green,
		false,
		DebugLineLifeTime,
		DebugLineDepthPriority,
		DebugLineThickness
	);

	// Draw a debug point
	DrawDebugPoint
	(
		World,
		DebugLineEnd,
		DebugPointSize,
		FColor::Magenta,
		false,
		DebugPointLifeTime,
		DebugPointDepthPriority
	);


}
