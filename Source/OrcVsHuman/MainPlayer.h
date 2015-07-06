// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "MainPlayerMovement.h"
#include "MainPlayer.generated.h"


UCLASS()
class ORCVSHUMAN_API AMainPlayer : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orc Vs Human")
	UMainPlayerMovement* movement;

public:	
	// Sets default values for this actor's properties
	AMainPlayer(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void LeftInput();
	void RightInput();
	void UpInput();
	void DownInput();

private:
	bool inputChanged;
	FVector inputDirection;
	
};
