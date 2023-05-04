// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CrowMazeGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChangedAGAINSignature, int, NewScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpeedChangedSignature, float, NewMoveSpeed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStartedSignature, ACrowMazeGameModeBase*, CrowGameMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGamePausedSignature, ACrowMazeGameModeBase*, CrowGameMode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOver);


/**
 * 
 */
UCLASS()
class CROWMAZE_API ACrowMazeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	ACrowMazeGameModeBase();

protected:
	virtual void BeginPlay() override;
	
public:
#pragma region Getters & Setters
	bool GetGameEndlessIsOn() const {return GameEndlessIsOn;}
	float GetTileMoveSpeed() const { return TileMoveSpeed;}
#pragma  endregion
	
	UFUNCTION(BlueprintCallable)
	void SpawnTile(bool IsStartingTile);
	UFUNCTION(BlueprintNativeEvent)
	void TriggerGameOver();
	void RemoveObstacleFromList(class AObstacle* Obstacle);
	void RewardPlayersByRemovingObstacle();
	UFUNCTION(BlueprintCallable)
	void StartEndlessRunner();
	UFUNCTION(BlueprintCallable)
	void PauseEndlessRunner();
private:
	void FindMiddlePointLocation(); //Use this to find position to start spawning tiles
	void SpawnStartingTiles();
	void ConnectSecondController();
	void SpawnObstacle(class ALevelBarrier* LevelBarrier);
	void SetHalfSize();
	void AdjustSpawnLocation(bool InsideTheLoop = true);
	void IncreaseScore();
	bool ShouldIncreaseSpeed() const;
	void IncreaseSpeed();
	void ChangeGameSpeed(const float NewSpeed);
	//TODO: Ask how to make annonymous functions with Dynamic delegates
	UFUNCTION()
	void FunctionToSubscribeToStartRunner(ACrowMazeGameModeBase* CrowMazeGameMode);


public:
#pragma region Delegates/ Events
	UPROPERTY(BlueprintAssignable,BlueprintReadWrite)
	FOnScoreChangedAGAINSignature OnScoreAgainChanged;
	UPROPERTY(BlueprintAssignable,BlueprintReadWrite)
	FOnSpeedChangedSignature OnSpeedAgainChanged;
	UPROPERTY(BlueprintAssignable,BlueprintReadWrite)
	FOnGameStartedSignature OnGameStarted;
	UPROPERTY(BlueprintAssignable,BlueprintReadWrite)
	FOnGamePausedSignature OnGamePaused;
	UPROPERTY(BlueprintAssignable, BlueprintReadOnly)
	FOnGameOver OnGameOver;
#pragma endregion
	
private:

#pragma region Components
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "GrowGameMode|Components", meta = (AllowPrivateAccess = "true"))
	class UActorPool* TerrainPool;
#pragma endregion

#pragma region Setup
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GrowGameMode|Setup", meta = (AllowPrivateAccess ="true"))
	FName MiddlePointTag = "CentralPoint";
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Setup")
	TArray<TSubclassOf<class AObstacle>> ObstacleShapes;
#pragma endregion

#pragma region Tunning
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning")
	float MaxTileSpeed = 20000;
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning")
	float StartingTileSpeed = 5000;
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning")
	int NumberOfStartingTiles = 10;
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning")
	float SpeedIncrease = 500;
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning")
	int SpeedIncreaseDivisorPerScoreIncrease = 0;
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning")
	int SpeedIncreaseDivisorPerScore = 10;
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning",meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))
	float ObstacleSpawnChance;
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning",meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))
	float DestroyObstacleRewardDefaultChance = 0.5;
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning",meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))
	float RewardChanceIncreaseUponFailure = 0.1;
#pragma endregion

#pragma region VisibleForDebugging
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "GrowGameMode|GameStats|VisibleForDebugging", meta = (AllowPrivateAccess ="true"))
	bool GameEndlessIsOn = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "GrowGameMode|GameStats|VisibleForDebugging", meta = (AllowPrivateAccess ="true"))
	float TileMoveSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GrowGameMode|GameStats|VisibleForDebugging", meta = (AllowPrivateAccess ="true"))
	float TerrainHalfSize;
	UPROPERTY(VisibleAnywhere, Category = "GrowGameMode|GameStats|VisibleForDebugging")
	FVector TileSpawnLocation;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "GrowGameMode|GameStats|VisibleForDebugging", meta = (AllowPrivateAccess ="true"))
	int32 CurrentScore = 0;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "GrowGameMode|GameStats|VisibleForDebugging", meta = (AllowPrivateAccess ="true"))
	TArray<class AObstacle*> ListOfSpawnedObstacles;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "GrowGameMode|GameStats|VisibleForDebugging", meta = (AllowPrivateAccess ="true"))
	float DestroyObstacleRewardChance = 0.5;

#pragma endregion
	
	float TileMoveSpeedBeforePause;
	bool GameIsPaused;
};
