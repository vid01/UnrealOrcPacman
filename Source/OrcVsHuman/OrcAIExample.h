// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OrcAIBase.h"
#include "OrcAIExample.generated.h"


UCLASS()
class ORCVSHUMAN_API AOrcAIExample : public AOrcAIBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orc Pathfinding")
	float repathTimer;

public:	
	// Sets default values for this actor's properties
	AOrcAIExample(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void notifyInvincibleMode(bool enabled) override;

private:
	float currentRepathTimer;
	
};
