// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolableActorAbstact.h"
#include "CrowMaze/Enumerators/ObstaclePositionTypes.h"
#include "Obstacle.generated.h"

UCLASS()
class CROWMAZE_API AObstacle : public APoolableActorAbstact
{
	GENERATED_BODY()
	
public:	
	AObstacle();

protected:
	virtual void BeginPlay() override;

public:
#pragma region Getters And Setters
	bool GetHitCrow() const{return HitCrow;}
#pragma endregion 
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CreateObstacle(class ALevelBarrier* LevelBarrier);
	UFUNCTION(BlueprintCallable)
	void CollideWithThePlayer(AActor* CrowPawn);
private:
	bool HitCrow;
	UPROPERTY(EditDefaultsOnly)
	float ObstacleHitDamage = 1;
	UPROPERTY()
	TArray<AActor*> HitActors;
	
};
