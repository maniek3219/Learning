// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemSinCosMovement.generated.h"

UCLASS()
class TUTORIALS_API AItemSinCosMovement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemSinCosMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Sinewave movement variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
		float MovementAmplitude = 0.25f;										// 1st variable initialization method

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
		float TimeConstant = 5.f;

	UFUNCTION(BlueprintPure) // Will appear as a green node in Blueprint
		float TransformedSin();

	UFUNCTION(BlueprintPure) // Will appear as a green node in Blueprint
		float TransformedCos();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime;

};
