// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "PowerUp.h"
#include "GameManager.h"


// Called when the game starts
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	AGameManager::Instance()->PowerUps.push_back(this);
}

