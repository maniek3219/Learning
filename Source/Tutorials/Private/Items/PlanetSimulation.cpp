// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PlanetSimulation.h"

// Sets default values
APlanetSimulation::APlanetSimulation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlanetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Planet Mesh"));

}

// Called when the game starts or when spawned
void APlanetSimulation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlanetSimulation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float RotationRate = 45.f;
	FRotator PlanetRotationOffset = FRotator(0.f, RotationRate, 0.f) * DeltaTime;

	AddActorWorldRotation(PlanetRotationOffset);

}

