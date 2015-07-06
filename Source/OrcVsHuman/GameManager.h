// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include <vector>
#include "GameManager.generated.h"

class AOrcAIBase;
class APowerUp;

enum EGameState
{
	GS_PlayerVulnerable,
	GS_PlayerInvincible,
};

UCLASS()
class ORCVSHUMAN_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Game Manager")
	AActor* MainPlayer;

	std::vector<AOrcAIBase*> Orcs;
	std::vector<AActor*> Coins;
	std::vector<APowerUp*> PowerUps;

	EGameState GameState;

public:	
	static AGameManager* Instance() { return instance; };

	// Sets default values for this actor's properties
	AGameManager(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:
	void checkOrcCollisions();
	void checkCoinCollisions();
	void checkPowerCoinCollisions();

private:
	static AGameManager* instance;
	float invincibleTimer;
	
};
