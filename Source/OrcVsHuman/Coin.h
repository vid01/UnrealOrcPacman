// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Coin.generated.h"


UCLASS()
class ORCVSHUMAN_API ACoin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Called when the game starts
	virtual void BeginPlay() override;
};
