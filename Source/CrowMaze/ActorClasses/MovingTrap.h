// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trap.h"
#include "MovingTrap.generated.h"

/**
 * 
 */
UCLASS()
class CROWMAZE_API AMovingTrap : public ATrap
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void ProvokeTrap() override;

private:
	FVector OriginalLocation;
	UPROPERTY(EditAnywhere) FVector DestinationOffset;
	UPROPERTY(EditAnywhere) float MoveTime = 4;
	
	
};
