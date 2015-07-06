// Fill out your copyright notice in the Description page of Project Settings.

#include "OrcVsHuman.h"
#include "OrcPathfindingComponent.h"
#include "GameInfo.h"
#include "PathFinding.h"

#pragma optimize("", off)

UOrcPathfindingComponent::UOrcPathfindingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	curve = CreateDefaultSubobject<UCurveVector>(TEXT("TimeLineMovement"));

	speed = 1.0f;
	updatePath = false;
}


// Called when the game starts
void UOrcPathfindingComponent::InitializeComponent()
{
	Super::InitializeComponent();

	progressFunction = FOnTimelineVector();
	progressFunction.BindUFunction(this, "Progress");

	TimeLine = FTimeline{};
	TimeLine.AddInterpVector(curve, progressFunction, FName{ TEXT("EFFECTFADE") });
}

void UOrcPathfindingComponent::UpdatePath(const FVector2D& _target)
{
	updatePath = true;
	Target = _target;
}

void UOrcPathfindingComponent::Progress(FVector Value)
{
	Value.Z = 10;
	GetOwner()->SetActorLocation(Value);
}

// Called every frame
void UOrcPathfindingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (TimeLine.IsPlaying())
	{
		TimeLine.TickTimeline(DeltaTime);
	}
	else 
	{
		if (updatePath == true)
		{
			Target.X = (int)(Target.X / TILESIZE_WIDTH) * TILESIZE_WIDTH;
			Target.Y = (int)(Target.Y / TILESIZE_HEIGHT) * TILESIZE_HEIGHT;
			
			FVector2D _position = FVector2D(GetOwner()->GetActorLocation());
			PathFinding::Instance().generatePath(Target, _position, _path);

			pathIndex = 0;
			updatePath = false;
		}	

		if (pathIndex + 1 < _path.size())
		{
			curve->ResetCurve();
			curve->FloatCurves[0].AddKey(0.0f, _path[pathIndex].X); // X
			curve->FloatCurves[1].AddKey(0.0f, _path[pathIndex].Y); // Y
			pathIndex++;
			curve->FloatCurves[0].AddKey(speed, _path[pathIndex].X); // X
			curve->FloatCurves[1].AddKey(speed, _path[pathIndex].Y); // Y
			TimeLine.PlayFromStart();
		}
	}
}

