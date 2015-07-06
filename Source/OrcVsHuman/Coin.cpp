// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "Coin.h"
#include "GameManager.h"

// Called when the game starts
void ACoin::BeginPlay()
{
	Super::BeginPlay();
	AGameManager::Instance()->Coins.push_back(this);
}

