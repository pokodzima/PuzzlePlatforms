// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		return;
	}
	SetReplicates(true);
	SetReplicateMovement(true);

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!HasAuthority())
	{
		return;
	}


	FVector Location = GetActorLocation();
	const float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Length();
	const float JourneyTravelled = (Location - GlobalStartLocation).Length();

	if (JourneyTravelled >= JourneyLength)
	{
		GlobalStartLocation = GlobalStartLocation + GlobalTargetLocation;
		GlobalTargetLocation = GlobalStartLocation - GlobalTargetLocation;
		GlobalStartLocation = GlobalStartLocation - GlobalTargetLocation;
	}

	const FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
	Location += Speed * DeltaSeconds * Direction;
	SetActorLocation(Location);
}
