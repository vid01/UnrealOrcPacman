// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "BaseStateComponent.generated.h"

class UFSMComponent;

UCLASS()
class ORCVSHUMAN_API UBaseStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseStateComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;	

   virtual void enter(UFSMComponent* _fsm);
   virtual void execute(float deltaTime);
   virtual void exit();

protected:
   UFSMComponent* fsm;

};
