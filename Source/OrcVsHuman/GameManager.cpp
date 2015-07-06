// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "GameManager.h"
#include "OrcAIBase.h"
#include "PowerUp.h"

#pragma optimize("", off)

AGameManager* AGameManager::instance = nullptr;

// Sets default values for this actor's properties
AGameManager::AGameManager(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this actor to be ticked every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AGameManager::instance = this;

	Orcs.clear();
	Coins.clear();
	PowerUps.clear();
}

// Called when the game starts
void AGameManager::BeginPlay()
{
	Super::BeginPlay();

	GameState = GS_PlayerVulnerable;
}

// Called every frame
void AGameManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (GameState == GS_PlayerInvincible)
	{
		invincibleTimer -= DeltaTime;
		if (invincibleTimer <= 0)
		{
			GameState = GS_PlayerVulnerable;
			for (int32 orcIndex = 0; orcIndex < Orcs.size(); orcIndex++)
			{
				Orcs[orcIndex]->notifyInvincibleMode(false);
			}
		}
	}

	checkOrcCollisions();
	checkCoinCollisions();
	checkPowerCoinCollisions();
}

void AGameManager::checkOrcCollisions()
{
	AOrcAIBase* orc = NULL;
	for (int32 index = 0; index < Orcs.size(); index++)
	{
		orc = Orcs[index];
		float distance = (orc->GetActorLocation() - MainPlayer->GetActorLocation()).Size();
		if (distance < 10)
		{
			if (GameState == GS_PlayerVulnerable)
			{
				//gameOver();
			}
			else
			{
				orc->notifyKilledByMainPlayer();
			}
			break;
		}
	}
}

void AGameManager::checkCoinCollisions()
{
	AActor* coin = NULL;
	for (int32 index = 0; index < Coins.size(); index++)
	{
		coin = Coins[index];
		float distance = (coin->GetActorLocation() - MainPlayer->GetActorLocation()).Size();
		if (distance < 10)
		{
			coin->Destroy();
			Coins.erase(Coins.begin() + index);
			break;
		}
	}
}

void AGameManager::checkPowerCoinCollisions()
{
	APowerUp* powerUp = NULL;
	for (int32 index = 0; index < PowerUps.size(); index++)
	{
		powerUp = PowerUps[index];
		float distance = (powerUp->GetActorLocation() - MainPlayer->GetActorLocation()).Size();
		if (distance < 10)
		{
			invincibleTimer = powerUp->PowerTime;

			GameState = GS_PlayerInvincible;
			for (int32 orcIndex = 0; orcIndex < Orcs.size(); orcIndex++)
			{
				Orcs[orcIndex]->notifyInvincibleMode(true);
			}

			powerUp->Destroy();
			PowerUps.erase(PowerUps.begin() + index);
			break;
		}
	}
}