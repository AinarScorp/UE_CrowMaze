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
	void FindCrowPlayer();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	float GetHalfSize();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetHalfSize();
	UFUNCTION(BlueprintCallable)
	void ActivateSpeed(float GameModeSpeed);
	UFUNCTION(BlueprintCallable)
	void OnBeginOverlapSpawnNewTile(AActor* OtherActor);
	
private:
	void DestroyAttachedObstacles();
	
private:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelBarrier|Setup", meta = (AllowPrivateAccess ="true"))
	FVector MoveDirection = FVector(-1.0f,0.f,0.f);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LevelBarrier|Setup", meta = (AllowPrivateAccess ="true"))
	FName PlayerTag = "CrowPlayer";
#pragma region Cached
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "LevelBarrier|VisibleForDebugging", meta = (AllowPrivateAccess ="true"))
	class ACrow* CrowPlayer;
	UPROPERTY()
	class ACrowMazeGameModeBase* CrowMazeGameMode;
#pragma endregion 
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = "LevelBarrier|VisibleForDebugging", meta = (AllowPrivateAccess ="true"))
	float MoveSpeed;
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<class AObstacle>> AttachedObstacles;

	bool bHasOverlappedOnce = false;
	bool bIsCreated = false;
	
	
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