// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemComponent.h"

// Sets default values
AItemComponent::AItemComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set a component to this actor
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;	// Set ItemMesh as a new root component
}

float AItemComponent::TransformedSin()
{
	return MovementAmplitude * FMath::Sin(RunningTime * TimeConstant);
}

float AItemComponent::TransformedCos()
{
	return MovementAmplitude * FMath::Cos(RunningTime * TimeConstant);
}

// Called when the game starts or when spawned
void AItemComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

}

