// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "BaseStateComponent.h"


// Sets default values for this component's properties
UBaseStateComponent::UBaseStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBaseStateComponent::InitializeComponent()
{
	Super::InitializeComponent();	
}


// Called every frame
void UBaseStateComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}


void UBaseStateComponent::enter(UFSMComponent* _fsm)
{
   fsm = _fsm;
}


void UBaseStateComponent::execute(float deltaTime)
{
}


void UBaseStateComponent::exit()
{
}

