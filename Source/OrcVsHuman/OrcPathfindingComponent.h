// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include <vector>
#include "OrcPathfindingComponent.generated.h"


UCLASS( ClassGroup=(User), meta=(BlueprintSpawnableComponent) )
class ORCVSHUMAN_API UOrcPathfindingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Orc Movement")
	float speed;

public:	
	// Sets default values for this component's properties
	UOrcPathfindingComponent();

	void UpdatePath(const FVector2D& location);

	// Called when the game starts
	virtual void InitializeComponent() override;

	UFUNCTION()
	void Progress(FVector Value);

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	FTimeline TimeLine;
	UCurveVector* curve;
	FOnTimelineVector progressFunction;
	std::vector<FVector2D> _path;
	int pathIndex;	

	bool updatePath;
	FVector2D Target;
};
