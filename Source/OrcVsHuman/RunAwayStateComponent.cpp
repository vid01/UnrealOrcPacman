// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "FSMComponent.h"
#include "GameInfo.h"
#include "GameManager.h"
#include "OrcPathfindingComponent.h"
#include "RedChaseStateComponent.h"
#include "RunAwayStateComponent.h"
#include "PinkChaseStateComponent.h"
#include "BlueStateComponent.h"
#include "DieStateComponent.h"

class UBaseStateComponent;

URunAwayStateComponent::URunAwayStateComponent()
{
   // Set this component to be initialized when the game starts, and to be ticked every frame.
   bWantsInitializeComponent = true;
   PrimaryComponentTick.bCanEverTick = true;

   repathTimer = 2.0f;
}

// Called when the game starts
void URunAwayStateComponent::InitializeComponent()
{
   Super::InitializeComponent();

   currentRepathTimer = repathTimer;
}


// Called every frame
void URunAwayStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
   Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void URunAwayStateComponent::enter(UFSMComponent* _fsm)
{
   Super::enter(_fsm);
}


void URunAwayStateComponent::execute(float deltaTime)
{
   //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "RunAwayStateComponent executed!");

   if (fsm->GetIsDead())
   {
      fsm->ChangeState(GetOwner()->FindComponentByClass<UDieStateComponent>());
   }
   if (fsm->GetPlayerMode())
   {
      // switch to Chase state attached
      TArray<UActorComponent*> comps;
      GetOwner()->GetComponents(comps);

      // loop components on owner
      for (int i = 0; i < comps.Num(); ++i)
      {
         URedChaseStateComponent* redComp = Cast<URedChaseStateComponent>(comps[i]);
         if (redComp)
         {
            // URedChaseStateComponent attached on owner
            fsm->ChangeState(GetOwner()->FindComponentByClass<URedChaseStateComponent>());
         }

         UPinkChaseStateComponent* pinkComp = Cast<UPinkChaseStateComponent>(comps[i]);
         if (pinkComp)
         {
            // UPinkChaseStateComponent attached on owner
            fsm->ChangeState(GetOwner()->FindComponentByClass<UPinkChaseStateComponent>());
         }

         UBlueStateComponent* blueComp = Cast<UBlueStateComponent>(comps[i]);
         if (blueComp)
         {
            // UBlueStateComponent attached on owner
            fsm->ChangeState(GetOwner()->FindComponentByClass<UBlueStateComponent>());
         }
      }
   }

   currentRepathTimer -= deltaTime;
   if (currentRepathTimer <= 0.0f)
   {
      currentRepathTimer = repathTimer;
      // run to predefined cell (in BP)
      FVector2D _target = hideoutSpot;
      GetOwner()->FindComponentByClass<UOrcPathfindingComponent>()->UpdatePath(_target);
   }
}


void URunAwayStateComponent::exit()
{
}
