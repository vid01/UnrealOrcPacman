// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "GameManager.h"
#include "GameInfo.h"
#include "FSMComponent.h"
#include "MainPlayerMovement.h"
#include "OrcPathfindingComponent.h"
#include "RunAwayStateComponent.h"
#include "PinkChaseStateComponent.h"


class UBaseStateComponent;

UPinkChaseStateComponent::UPinkChaseStateComponent()
{
   // Set this component to be initialized when the game starts, and to be ticked every frame.
   bWantsInitializeComponent = true;
   PrimaryComponentTick.bCanEverTick = true;

   repathTimer = 2.0f;
}


// Called when the game starts
void UPinkChaseStateComponent::InitializeComponent()
{
   Super::InitializeComponent();

   currentRepathTimer = repathTimer;
}


// Called every frame
void UPinkChaseStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
   Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UPinkChaseStateComponent::enter(UFSMComponent* _fsm)
{
   Super::enter(_fsm);
}


void UPinkChaseStateComponent::execute(float deltaTime)
{
   //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Magenta, "PinkChaseStateComponent executed!");

   currentRepathTimer -= deltaTime;
   if (currentRepathTimer <= 0.0f)
   {
      // Pink Orc's target cell is Player's current location + next cell in movement direction
      currentRepathTimer = repathTimer;
      FVector2D playerPos = FVector2D(AGameManager::Instance()->MainPlayer->GetActorLocation());
      FVector2D playerDir = FVector2D(AGameManager::Instance()->MainPlayer->FindComponentByClass<UMainPlayerMovement>()->inputDirection);
      FVector2D _target = playerPos + playerDir * GameInfo::Instance().getTileSize();
      GetOwner()->FindComponentByClass<UOrcPathfindingComponent>()->UpdatePath(_target);
   }

   // if player is invincible -> run away
   if (fsm->GetPlayerMode())
   {
      fsm->ChangeState(GetOwner()->FindComponentByClass<URunAwayStateComponent>());
   }
}


void UPinkChaseStateComponent::exit()
{
}
