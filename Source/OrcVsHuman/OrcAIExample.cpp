// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "OrcAIExample.h"
#include "GameManager.h"

#pragma optimize("", off)

// Sets default values for this actor's properties
AOrcAIExample::AOrcAIExample(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	repathTimer = 2.0f;
}

void AOrcAIExample::BeginPlay()
{
	Super::BeginPlay();

	currentRepathTimer = repathTimer;
}


// Called every frame
void AOrcAIExample::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

	/*currentRepathTimer -= DeltaTime;
	if (currentRepathTimer <= 0.0f)
	{
		currentRepathTimer = repathTimer;
		FVector2D _target = FVector2D(AGameManager::Instance()->MainPlayer->GetActorLocation());
		pathfindingComponent->UpdatePath(_target);
	}*/
}

void AOrcAIExample::notifyInvincibleMode(bool enabled)
{
	/*if (enabled == true)
	{
		SpriteComponent->SetSpriteColor(FLinearColor(0, 0, 1));
	}
	else
	{
		SpriteComponent->SetSpriteColor(FLinearColor(1, 1, 1));
	}*/
}
