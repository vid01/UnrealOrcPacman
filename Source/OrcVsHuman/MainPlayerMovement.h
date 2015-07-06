// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include <vector>
#include "MainPlayerMovement.generated.h"


UCLASS( ClassGroup=(User), meta=(BlueprintSpawnableComponent) )
class ORCVSHUMAN_API UMainPlayerMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Movement")
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Movement")
	FVector2D inputDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Movement")
	FVector2D direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Movement")
	FVector2D currentLocation;

public:	
	// Sets default values for this component's properties
	UMainPlayerMovement();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	UFUNCTION()
	void Progress(FVector Value);

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	FTimeline TimeLine;
	UCurveVector* curve;
	FOnTimelineVector progressFunction;
};
