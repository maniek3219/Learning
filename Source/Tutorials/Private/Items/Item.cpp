// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Tutorials/DebugHelpersMacros.h"
#include "Tutorials/Tutorials.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BP_Item executed"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Blue, FString("C++ executed"));
	}

	UWorld* World = GetWorld();
	FVector OriginalItemLocation = GetActorLocation();
	FRotator OriginalItemRotation = GetActorRotation();
	FVector NewItemLocation = FVector(0.f, 0.f, 200.f);
	FRotator NewItemRotation = FRotator(0.f, 45.f, 0.f);

	// Set a new BP_Item location
	SetActorLocation(NewItemLocation);
	SetActorRotation(NewItemRotation, ETeleportType::None);

	// Moves the actor back to its original location and rotation
	SetActorLocation(OriginalItemLocation);
	SetActorRotation(OriginalItemRotation, ETeleportType::None);

	FVector ItemLocation = GetActorLocation(); // Variable to get a new BP_Item location

	// DrawDebugSphere variables
	float DebugSphereRadius = 25.f;
	int32 DebugSphereSegments = 24;
	float DebugSphereLifeTime = -1.f;
	uint8 DebugSphereDepthPriority = 2U;
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

	if (World)
	{
		// Draw a debug sphere
		DrawDebugSphere
		(
			World,
			ItemLocation,
			DebugSphereRadius,
			DebugSphereSegments,
			FColor::Red,
			true,
			DebugSphereLifeTime,
			DebugSphereDepthPriority,
			DebugSphereThickness
		);
	}

	if (World)
	{
		// Draw a debug line
		DrawDebugLine
		(
			World,
			ItemLocation,
			DebugLineEnd,
			FColor::Green,
			true,
			DebugLineLifeTime,
			DebugLineDepthPriority,
			DebugLineThickness
		);
	}

	if (World)
	{
		// Draw a debug point
		DrawDebugPoint
		(
			World,
			DebugLineEnd,
			DebugPointSize,
			FColor::Magenta,
			true,
			DebugPointLifeTime,
			DebugPointDepthPriority
		);
	}

	DRAW_SPHERE_CHALLENGE(ItemLocation, FColor::Silver);

}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("DeltaTime: %F"), DeltaTime);

	// Print messages on screen
	if (GEngine)
	{
		FString Name = GetName();
		FString PrintName = FString::Printf(TEXT("Function name: %s"), *Name);
		FString Message = FString::Printf(TEXT("DeltaTime: %f"), DeltaTime);

		GEngine->AddOnScreenDebugMessage(2, 60.f, FColor::Cyan, Message);
		GEngine->AddOnScreenDebugMessage(3, 60.f, FColor::Red, PrintName);

		UE_LOG(LogTemp, Warning, TEXT("Function name: %s"), *Name);
	}

	// Print an average of two values in Output Log from template
	int32 AvgIntIs = Avg<int32>(1, 3);
	UE_LOG(LogTemp, Warning, TEXT("Average of integers in line 136 is: %d"), AvgIntIs);

	float AvgFloatIs = Avg<float>(3.5f, 4.5f);
	UE_LOG(LogTemp, Warning, TEXT("Average of floats in line 139 is: %f"), AvgFloatIs);


}

