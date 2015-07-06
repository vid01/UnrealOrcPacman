// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "OrcAIBase.h"
#include "FSMComponent.h"
#include "RespawnStateComponent.h"
#include "RunAwayStateComponent.h"
#include "DieStateComponent.h"
#include "RedOrcAI.generated.h"

/**
 * 
 */
UCLASS()
class ORCVSHUMAN_API ARedOrcAI : public AOrcAIBase
{
	GENERATED_BODY()

public:

   /*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orc Pathfinding")
      float repathTimer;*/

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orc FSM")
      UFSMComponent *fsm;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orc FSM")
      URunAwayStateComponent *runawayState;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orc FSM")
      UDieStateComponent *dieState;

   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orc FSM")
      URespawnStateComponent *respawnState;
	
public:
   // Sets default values for this actor's properties
   ARedOrcAI(const FObjectInitializer& ObjectInitializer);

   // Called when the game starts
   virtual void BeginPlay() override;

   // Called every frame
   virtual void Tick(float DeltaSeconds) override;

   virtual void notifyInvincibleMode(bool enabled) override;
   virtual void notifyKilledByMainPlayer();

/*private:
   float currentRepathTimer;*/
};
