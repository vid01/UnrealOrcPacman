// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "FSMComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ORCVSHUMAN_API UFSMComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFSMComponent();

   // Entity starting pos -> used for return when killed
   UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Orc Pathfinding")
   FVector2D startPos;

   UFUNCTION(BlueprintCallable, Category = "FSM")
      void ChangeState(UBaseStateComponent* state);

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

   void SetPlayerMode(bool invincible);
   bool GetPlayerMode() { return playerInvincible; }

   void SetIsDead(bool _isDead);
   bool GetIsDead() { return isDead; }

   FVector2D GetStartPos() { return startPos; }
   void SetStartPos(FVector2D pos) { startPos = pos; }

private:
   UBaseStateComponent* currentState;
   bool playerInvincible;
   bool isDead; // entity has been killed by player
};
