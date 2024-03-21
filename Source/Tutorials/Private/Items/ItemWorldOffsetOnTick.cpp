// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemWorldOffsetOnTick.h"

// Sets default values
AItemWorldOffsetOnTick::AItemWorldOffsetOnTick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemWorldOffsetOnTick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemWorldOffsetOnTick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UWorld* World = GetWorld();
	float MovementRate = 50.f; // Movement in cm/s
	float RotationRate = 45.f; // Rotation per second
	FVector ItemLocation = GetActorLocation();
	FVector ItemLocationOffset = FVector(MovementRate, 0.f, 0.f) * DeltaTime;
	FRotator ItemRotationOffset = FRotator(0.f, RotationRate, 0.f) * DeltaTime;

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

	AddActorWorldOffset(ItemLocationOffset);
	AddActorWorldRotation(ItemRotationOffset);

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

	// Draw a debug point from the template to follow the debug sphere
	FVector AvgVector = Avg<FVector>(GetActorLocation(), FVector::ZeroVector);
	float MovementScalar = 2.f;		// Item is not located on 0,0,0 , so movement rate must be scaled proportionally

	DrawDebugPoint
	(
		World,
		AvgVector * MovementScalar,
		DebugPointSize,
		FColor::Cyan,
		false,
		DebugPointLifeTime,
		DebugPointDepthPriority
	);

}

