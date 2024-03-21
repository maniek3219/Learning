// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemWorldOffsetOnTick.generated.h"

UCLASS()
class TUTORIALS_API AItemWorldOffsetOnTick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemWorldOffsetOnTick();

	template<typename T>
	T Avg(T First, T Second);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

template<typename T>
inline T AItemWorldOffsetOnTick::Avg(T First, T Second)
{
	return (First + Second) / 2;
}
