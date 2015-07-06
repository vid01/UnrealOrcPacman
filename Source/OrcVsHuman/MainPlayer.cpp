// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "MainPlayer.h"
#include "GameManager.h"
#include "MainPlayerMovement.h"

// Sets default values for this actor's properties
AMainPlayer::AMainPlayer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
 	// Set this actor to be ticked every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	movement = CreateDefaultSubobject<UMainPlayerMovement>(TEXT("Movement Controller"));
}

// Called when the game starts
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	AGameManager::Instance()->MainPlayer = this;

	InputComponent->BindAction("Left", IE_Pressed, this, &AMainPlayer::LeftInput);
	InputComponent->BindAction("Right", IE_Pressed, this, &AMainPlayer::RightInput);
	InputComponent->BindAction("Up", IE_Pressed, this, &AMainPlayer::UpInput);
	InputComponent->BindAction("Down", IE_Pressed, this, &AMainPlayer::DownInput);

}

// Called every frame
void AMainPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AMainPlayer::LeftInput()
{
	inputChanged = true;
	movement->inputDirection.X = -1;
	movement->inputDirection.Y = 0;
}

void AMainPlayer::RightInput()
{
	inputChanged = true;
	movement->inputDirection.X = 1;
	movement->inputDirection.Y = 0;
}

void AMainPlayer::UpInput()
{
	inputChanged = true;
	movement->inputDirection.X = 0;
	movement->inputDirection.Y = -1;
}

void AMainPlayer::DownInput()
{
	inputChanged = true;
	movement->inputDirection.X = 0;
	movement->inputDirection.Y = 1;
}