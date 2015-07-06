// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "RedOrcAI.h"
#include "FSMComponent.h"
#include "DieStateComponent.h"
#include "RespawnStateComponent.h"


UDieStateComponent::UDieStateComponent()
{
   // Set this component to be initialized when the game starts, and to be ticked every frame.
   bWantsInitializeComponent = true;
   PrimaryComponentTick.bCanEverTick = true;

   repathTimer = 2.0f;
}

// Called when the game starts
void UDieStateComponent::InitializeComponent()
{
   Super::InitializeComponent();

   currentRepathTimer = repathTimer;
}


// Called every frame
void UDieStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
   Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UDieStateComponent::enter(UFSMComponent* _fsm)
{
   Super::enter(_fsm);
}


void UDieStateComponent::execute(float deltaTime)
{
   //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, "DieStateComponent executed!");

   FVector2D _target = FVector2D(GetOwner()->FindComponentByClass<UFSMComponent>()->GetStartPos());
   FVector2D curPos = FVector2D(GetOwner()->GetActorLocation());
   //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("CurPos: x: %f, y: %f"), curPos.X, curPos.Y));

   currentRepathTimer -= deltaTime;
   if (currentRepathTimer <= 0.0f)
   {
      currentRepathTimer = repathTimer;
      if (curPos != _target)
      {
         // didn't reach startPos - move towards it
         GetOwner()->FindComponentByClass<UOrcPathfindingComponent>()->UpdatePath(_target);
      }
      else
      {
         // reached -> respawn
         fsm->ChangeState(GetOwner()->FindComponentByClass<URespawnStateComponent>());
      }
   }
}

void UDieStateComponent::exit()
{
}
