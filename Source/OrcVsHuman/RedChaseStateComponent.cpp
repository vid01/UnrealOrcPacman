// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "FSMComponent.h"
#include "RunAwayStateComponent.h"
#include "RedChaseStateComponent.h"
#include "GameManager.h"
#include "OrcPathfindingComponent.h"

class UBaseStateComponent;

URedChaseStateComponent::URedChaseStateComponent()
{
   // Set this component to be initialized when the game starts, and to be ticked every frame.
   bWantsInitializeComponent = true;
   PrimaryComponentTick.bCanEverTick = true;

   repathTimer = 2.0f;
}


// Called when the game starts
void URedChaseStateComponent::InitializeComponent()
{
   Super::InitializeComponent();

   currentRepathTimer = repathTimer;
}


// Called every frame
void URedChaseStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
   Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void URedChaseStateComponent::enter(UFSMComponent* _fsm)
{
   Super::enter(_fsm);
}


void URedChaseStateComponent::execute(float deltaTime)
{
   //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "RedChaseStateComponent executed!");

   currentRepathTimer -= deltaTime;
   if (currentRepathTimer <= 0.0f)
   {
      // Red Orc's target cell is Player's current location
      currentRepathTimer = repathTimer;
      FVector2D _target = FVector2D(AGameManager::Instance()->MainPlayer->GetActorLocation());
      GetOwner()->FindComponentByClass<UOrcPathfindingComponent>()->UpdatePath(_target);
   }

   // if player is invincible -> run away
   if (fsm->GetPlayerMode())
   {
      fsm->ChangeState(GetOwner()->FindComponentByClass<URunAwayStateComponent>());
   }
}


void URedChaseStateComponent::exit()
{
}
