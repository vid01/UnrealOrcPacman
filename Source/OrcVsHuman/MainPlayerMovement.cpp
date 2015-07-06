// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "MainPlayerMovement.h"
#include "GameInfo.h"


// Sets default values for this component's properties
UMainPlayerMovement::UMainPlayerMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	curve = CreateDefaultSubobject<UCurveVector>(TEXT("TimeLineMovement"));

	speed = 1.0f;
	direction = FVector2D(-1, 0);
	inputDirection = FVector2D(-1, 0);
	currentLocation = FVector2D(9, 16);
}


// Called when the game starts
void UMainPlayerMovement::InitializeComponent()
{
	Super::InitializeComponent();

	progressFunction = FOnTimelineVector();
	progressFunction.BindUFunction(this, "Progress");

	// Where we are
	curve->FloatCurves[0].AddKey(0.0f, 32.0f * currentLocation.X); // X
	curve->FloatCurves[1].AddKey(0.0f, 32.0f * currentLocation.Y); // Y
	// Move To
	curve->FloatCurves[0].AddKey(speed, (32.0f * (currentLocation.X + direction.X))); // X
	curve->FloatCurves[1].AddKey(speed, (32.0f * (currentLocation.Y + direction.Y))); // Y

	currentLocation.X += direction.X;
	currentLocation.Y += direction.Y;

	TimeLine = FTimeline{};
	TimeLine.AddInterpVector(curve, progressFunction, FName{ TEXT("EFFECTFADE") });
	TimeLine.PlayFromStart();
}

void UMainPlayerMovement::Progress(FVector Value)
{
	Value.Z = 10;
	GetOwner()->SetActorLocation(Value);
}

// Called every frame
void UMainPlayerMovement::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (TimeLine.IsPlaying())
	{
		TimeLine.TickTimeline(DeltaTime);
	}
	else
	{
		if (GameInfo::Instance().getCollisionAt(currentLocation.X + inputDirection.X, currentLocation.Y + inputDirection.Y) == false)
		{
			direction.X = inputDirection.X;
			direction.Y = inputDirection.Y;
		}

		if (GameInfo::Instance().getCollisionAt(currentLocation.X + direction.X, currentLocation.Y + direction.Y) == false)
		{
			curve->ResetCurve();

			// Where we are
			curve->FloatCurves[0].AddKey(0.0f, 32.0f * currentLocation.X); // X
			curve->FloatCurves[1].AddKey(0.0f, 32.0f * currentLocation.Y); // Y
			// Move To
			curve->FloatCurves[0].AddKey(speed, (32.0f * (currentLocation.X + direction.X))); // X
			curve->FloatCurves[1].AddKey(speed, (32.0f * (currentLocation.Y + direction.Y))); // Y

			currentLocation.X += direction.X;
			currentLocation.Y += direction.Y;

			TimeLine.PlayFromStart();
		}
	}
}

