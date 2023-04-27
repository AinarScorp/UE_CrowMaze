// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CrowMazeGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChangedAGAINSignature, int, NewScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpeedChangedSignature, float, NewMoveSpeed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStartedSignature, ACrowMazeGameModeBase*, CrowGameMode);


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
	UFUNCTION(BlueprintCallable)
	void SpawnStartingTiles();
	UFUNCTION(BlueprintCallable)
	void SpawnTile(bool IsStartingTile);
	void SpawnObstacle(class ALevelBarrier* LevelBarrier);
	UFUNCTION(BlueprintNativeEvent)
	void SetHalfSize();
	UFUNCTION(BlueprintCallable)
	void AdjustSpawnLocation(bool InsideTheLoop = true);
	UFUNCTION(BlueprintCallable)
	void IncreaseScore();
	bool ShouldIncreaseSpeed();
	void IncreaseSpeed();
	void ChangeGameSpeed(const float NewSpeed);
	void StartEndlessRunner();
	void TestWithThommy(int NewScoreToTest);

public:
	UPROPERTY(BlueprintAssignable,BlueprintReadWrite)
	FOnScoreChangedAGAINSignature OnScoreAgainChanged;
	UPROPERTY(BlueprintAssignable,BlueprintReadWrite)
	FOnSpeedChangedSignature OnSpeedAgainChanged;
	UPROPERTY(BlueprintAssignable,BlueprintReadWrite)
	FOnGameStartedSignature OnGameStarted;
private:
#pragma region Components
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "GrowGameMode|Components", meta = (AllowPrivateAccess = "true"))
	class UActorPool* TerrainPool;
#pragma endregion

#pragma region Tunning
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning")
	float StartingTileSpeed = 5000;
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning")
	int NumberOfStartingTiles = 10;
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning")
	float SpeedIncrease = 500;
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning")
	int SpeedIncreaseDivisorPerScore = 10;
	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Tunning",meta = (ClampMin = "0", ClampMax = "1", UIMin = "0", UIMax = "1"))
	float ObstacleSpawnChance;
	
#pragma endregion


	UPROPERTY(EditAnywhere, Category = "GrowGameMode|Setup")
	TArray<TSubclassOf<class AObstacle>> ObstacleShapes;
	

#pragma region VisibleForDebugging
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "GrowGameMode|GameStats|VisibleForDebugging", meta = (AllowPrivateAccess ="true"))
	bool GameEndlessIsOn = false;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "GrowGameMode|GameStats|VisibleForDebugging", meta = (AllowPrivateAccess ="true"))
	float TileMoveSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GrowGameMode|GameStats|VisibleForDebugging", meta = (AllowPrivateAccess ="true"))
	float TerrainHalfSize;
	UPROPERTY(VisibleAnywhere, Category = "GrowGameMode|GameStats|VisibleForDebugging")
	FVector TileSpawnLocation;
	UPROPERTY(VisibleAnywhere, Category = "GrowGameMode|GameStats|VisibleForDebugging")
	int32 CurrentScore = 13;
#pragma endregion
};
