// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "OrcAIBase.h"
#include "GameManager.h"


// Sets default values for this actor's properties
AOrcAIBase::AOrcAIBase(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	pathfindingComponent = CreateDefaultSubobject<UOrcPathfindingComponent>(TEXT("Orc, Movement Controller"));
   // project crashes if uncommented
	//SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Orc Sprite"));
}

void AOrcAIBase::BeginPlay()
{
	Super::BeginPlay();
	AGameManager::Instance()->Orcs.push_back(this);
}