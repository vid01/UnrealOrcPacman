// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "OrcPathfindingComponent.h"
#include "PaperSpriteComponent.h"
#include "OrcAIBase.generated.h"


UCLASS()
class ORCVSHUMAN_API AOrcAIBase : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orc Pathfinding")
	UOrcPathfindingComponent* pathfindingComponent; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orc Pathfinding")
	UPaperSpriteComponent* SpriteComponent;

public:
	// Sets default values for this actor's properties
	AOrcAIBase(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	// Notification method for you to work with
	virtual void notifyInvincibleMode(bool enabled) {};

	// Notification that you are dead!
	virtual void notifyKilledByMainPlayer() {};
	
};
