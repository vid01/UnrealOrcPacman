// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"


UCLASS()
class ORCVSHUMAN_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Board Data")
	float PowerTime;

public:	
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
