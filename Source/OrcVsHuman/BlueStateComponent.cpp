// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "GameManager.h"
#include "OrcAIBase.h"
#include "FSMComponent.h"
#include "MainPlayerMovement.h"
#include "OrcPathfindingComponent.h"
#include "RunAwayStateComponent.h"
#include "BlueStateComponent.h"


class UBaseStateComponent;

UBlueStateComponent::UBlueStateComponent()
{
   // Set this component to be initialized when the game starts, and to be ticked every frame.
   bWantsInitializeComponent = true;
   PrimaryComponentTick.bCanEverTick = true;

   repathTimer = 2.0f;
}


// Called when the game starts
void UBlueStateComponent::InitializeComponent()
{
   Super::InitializeComponent();

   currentRepathTimer = repathTimer;
}


// Called every frame
void UBlueStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
   Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UBlueStateComponent::enter(UFSMComponent* _fsm)
{
   Super::enter(_fsm);
}


void UBlueStateComponent::execute(float deltaTime)
{
   //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, "BlueStateComponent executed!");

   currentRepathTimer -= deltaTime;
   if (currentRepathTimer <= 0.0f)
   {
      // Blue Orc's target cell
      currentRepathTimer = repathTimer;
      FVector2D orcPos = FVector2D(AGameManager::Instance()->Orcs[0]->GetActorLocation());
      FVector2D playerPos = FVector2D(AGameManager::Instance()->MainPlayer->GetActorLocation());
      //FVector2D playerDir = FVector2D(AGameManager::Instance()->MainPlayer->FindComponentByClass<UMainPlayerMovement>()->inputDirection);
      FVector2D dist = playerPos - orcPos;
      FVector2D _target = dist;
      GetOwner()->FindComponentByClass<UOrcPathfindingComponent>()->UpdatePath(_target);
   }

   // if player is invincible -> run away
   if (fsm->GetPlayerMode())
   {
      fsm->ChangeState(GetOwner()->FindComponentByClass<URunAwayStateComponent>());
   }
}


void UBlueStateComponent::exit()
{
}

