// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "RedOrcAI.h"
#include "GameManager.h"

#pragma optimize("", off)

// Sets default values for this actor's properties
ARedOrcAI::ARedOrcAI(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
   //repathTimer = 2.0f;
   fsm = CreateDefaultSubobject<UFSMComponent>(TEXT("Orc, FSM Controller"));
   runawayState = CreateDefaultSubobject<URunAwayStateComponent>(TEXT("Orc, RunAwayState"));
   dieState = CreateDefaultSubobject<UDieStateComponent>(TEXT("Orc, DieState"));
   respawnState = CreateDefaultSubobject<URespawnStateComponent>(TEXT("Orc, RespawnState"));

   //fsm->SetStartPos(FVector2D(AGameManager::Instance()->Orcs[0]->GetActorLocation()));

   // sprite is set to null even if component is attached
   //SpriteComponent = FindComponentByClass<UPaperSpriteComponent>();
}

void ARedOrcAI::BeginPlay()
{
   Super::BeginPlay();

   //currentRepathTimer = repathTimer;
}

// Updates every frame
void ARedOrcAI::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);

   /*currentRepathTimer -= DeltaTime;
   if (currentRepathTimer <= 0.0f)
   {
      currentRepathTimer = repathTimer;
      FVector2D _target = FVector2D(AGameManager::Instance()->MainPlayer->GetActorLocation());
      pathfindingComponent->UpdatePath(_target);
   }*/
}

void ARedOrcAI::notifyInvincibleMode(bool enabled)
{
   fsm->SetPlayerMode(enabled);

   //if (enabled == true)
   //{      
   //   //SpriteComponent->SetSpriteColor(FLinearColor(0, 0, 1));
   //}
   //else
   //{
   //   //SpriteComponent->SetSpriteColor(FLinearColor(1, 1, 1));
   //}
}

void ARedOrcAI::notifyKilledByMainPlayer()
{
   fsm->SetIsDead(true);
}
