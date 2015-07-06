// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "FSMComponent.h"
#include "RedChaseStateComponent.h"
#include "PinkChaseStateComponent.h"
#include "BlueStateComponent.h"
#include "RespawnStateComponent.h"


URespawnStateComponent::URespawnStateComponent()
{
   // Set this component to be initialized when the game starts, and to be ticked every frame.
   bWantsInitializeComponent = true;
   PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void URespawnStateComponent::InitializeComponent()
{
   Super::InitializeComponent();
}


// Called every frame
void URespawnStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
   Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void URespawnStateComponent::enter(UFSMComponent* _fsm)
{
   Super::enter(_fsm);
}


void URespawnStateComponent::execute(float deltaTime)
{
   //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "RespawnStateComponent executed!");

   // set not dead -> switch to chase
   fsm->SetIsDead(false);

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


void URespawnStateComponent::exit()
{
}

