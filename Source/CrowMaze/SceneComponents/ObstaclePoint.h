// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "CrowMaze/Enumerators/ObstaclePositionTypes.h"
#include "ObstaclePoint.generated.h"


UCLASS( ClassGroup=(Custom),Blueprintable,BlueprintType, meta=(BlueprintSpawnableComponent) )
class CROWMAZE_API UObstaclePoint : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObstaclePoint();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere)
	EObstaclePositionTypes ObstaclePositionType = EObstaclePositionTypes::EOPT_CenterMiddle;
};
