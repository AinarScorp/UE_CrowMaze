// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingTrap.h"

void AMovingTrap::BeginPlay()
{
	Super::BeginPlay();
	OriginalLocation = GetActorLocation();
}

void AMovingTrap::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector TargetLocation = OriginalLocation + DestinationOffset;

	
	const FVector CurrentLocation = GetActorLocation();
	float Speed = DestinationOffset.Length() /MoveTime;

	FVector NewLocation = FMath::VInterpConstantTo(CurrentLocation,TargetLocation, DeltaSeconds,Speed);
	SetActorLocation(NewLocation);
	bool MovedCloseEnough =FVector::Distance(NewLocation, CurrentLocation) < 0.1f;
	if (MovedCloseEnough )
	{
		SetActorTickEnabled(false);
			UE_LOG(LogTemp,Warning,TEXT("Tick off"));

	}
}

void AMovingTrap::ProvokeTrap()
{
	Super::ProvokeTrap();
	UE_LOG(LogTemp,Warning,TEXT("Tick on"));

	SetActorTickEnabled(true);
}
