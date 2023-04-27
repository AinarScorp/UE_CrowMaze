// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolableActorAbstact.h"
#include "LevelBarrier.generated.h"


UCLASS()
class CROWMAZE_API ALevelBarrier : public APoolableActorAbstact
{
	GENERATED_BODY()
	
public:	
	ALevelBarrier();

protected:
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;
	
	virtual void SpawnActor_Implementation(const FVector& NewLocation, const FRotator& NewRotation) override;
	UFUNCTION(BlueprintImplementableEvent)
	TArray<class UObstaclePoint*> GetObstaclePoints();
	
	void AttachObstacle(TObjectPtr<class AObstacle> ObstacleToAttach);

	UFUNCTION(BlueprintCallable)
	void ActivateSpeed(float GameModeSpeed);
private:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "LevelBarrier|VisibleForDebugging", meta = (AllowPrivateAccess ="true"))
	float MoveSpeed;
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<class AObstacle>> AttachedObstacles;

	
	
};



#pragma region CommnetedOut
//virtual void SetLifeSpan(float InLifespan) override;

//Interface
// virtual void SpawnActor_Implementation() override;
// virtual void SetActiveMy_Implementation(bool InActive) override;
// virtual bool IsActiveMy_Implementation() override;
// virtual float GetLifeSpanMy_Implementation() override;
// virtual void DeactivateMy_Implementation() override;
//
// UPROPERTY(BlueprintReadWrite, Category = "Object Pool")
// float LifeSpan;
// UPROPERTY(BlueprintReadWrite, Category = "Object Pool")
// FTimerHandle LifeSpanTimer;
// UPROPERTY(BlueprintReadWrite, Category = "Object Pool")
// bool bIsActive;
#pragma endregion 