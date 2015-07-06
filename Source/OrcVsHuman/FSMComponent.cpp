// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "FSMComponent.h"
#include "BaseStateComponent.h"


// Sets default values for this component's properties
UFSMComponent::UFSMComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

   currentState = nullptr;
}


// Called when the game starts
void UFSMComponent::InitializeComponent()
{
	Super::InitializeComponent();
}


// Called every frame
void UFSMComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

   // Need to update our current State
   if (currentState != nullptr)
   {
      currentState->execute(DeltaTime);
   }
}


void UFSMComponent::ChangeState(UBaseStateComponent* state)
{
   if (currentState != nullptr)
   {
      currentState->exit();
   }

   currentState = state;
   currentState->enter(this);
}

void UFSMComponent::SetPlayerMode(bool invincible)
{
   playerInvincible = invincible;
}

void UFSMComponent::SetIsDead(bool _isDead)
{
   isDead = _isDead;
}
