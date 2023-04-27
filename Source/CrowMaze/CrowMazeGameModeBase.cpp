// Copyright Epic Games, Inc. All Rights Reserved.


#include "CrowMazeGameModeBase.h"

#include "ActorClasses/LevelBarrier.h"
#include "ActorClasses/Obstacle.h"
#include "ActorClasses/PoolableActorAbstact.h"
#include "ActorComponents/ActorPool.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"
#include "Kismet/KismetMathLibrary.h"

ACrowMazeGameModeBase::ACrowMazeGameModeBase()
{
	TerrainPool = CreateDefaultSubobject<UActorPool>(TEXT("TerrainPool"));
}

void ACrowMazeGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	OnScoreAgainChanged.AddDynamic(this, &ACrowMazeGameModeBase::TestWithThommy);
	const FVector PlayerStartLocation = UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation();
	TileSpawnLocation = PlayerStartLocation;
	SpawnStartingTiles();
	IncreaseScore();
	IncreaseScore();
	IncreaseScore();
}

void ACrowMazeGameModeBase::SpawnStartingTiles()
{
	if (NumberOfStartingTiles <= 0)
	{
		return;
	}
	SetHalfSize();
	for (int i = 0; i < NumberOfStartingTiles; ++i)
	{
		SpawnTile(true);
		AdjustSpawnLocation();
	}
	AdjustSpawnLocation(false);
	StartEndlessRunner();
	
}

void ACrowMazeGameModeBase::SpawnTile(bool IsStartingTile)
{
	if (!TerrainPool)
	{
		return;
	}
	TObjectPtr<APoolableActorAbstact> PoolableActor = TerrainPool->GetPooledActor();
	PoolableActor->SpawnActor(TileSpawnLocation, PoolableActor->GetActorRotation());
	if (IsStartingTile)
	{
		return;
	}
	IncreaseScore();
	IncreaseSpeed();
	if (UKismetMathLibrary::RandomBoolWithWeight(ObstacleSpawnChance))
	{
		SpawnObstacle(Cast<ALevelBarrier>(PoolableActor));
	}
}

void ACrowMazeGameModeBase::SpawnObstacle(ALevelBarrier* LevelBarrier)
{
	UWorld* World = GetWorld();
	if (ObstacleShapes.Num() <=0 || World == nullptr|| LevelBarrier == nullptr)
	{
		return;
	}

	const int32 RandomIndex = FMath::RandRange(0,ObstacleShapes.Num()-1);
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Owner =LevelBarrier;
	AObstacle* Obstacle = World->SpawnActor<AObstacle>(ObstacleShapes[RandomIndex], FVector(), FRotator(),ActorSpawnParameters);
	Obstacle->CreateObstacle(LevelBarrier);
}

void ACrowMazeGameModeBase::AdjustSpawnLocation(bool InsideTheLoop)
{
	if (InsideTheLoop)
	{
		TileSpawnLocation.X += TerrainHalfSize;
	}
	else
	{
		TileSpawnLocation.X -= TerrainHalfSize/2;
	}
}

void ACrowMazeGameModeBase::IncreaseScore()
{
	CurrentScore++;
	OnScoreAgainChanged.Broadcast(CurrentScore);
	//UE_LOG(LogTemp, Error, TEXT("Current score changed to %i"), CurrentScore)

}

bool ACrowMazeGameModeBase::ShouldIncreaseSpeed()
{
	return CurrentScore % SpeedIncreaseDivisorPerScore == 0;
}

void ACrowMazeGameModeBase::IncreaseSpeed()
{
	if (ShouldIncreaseSpeed())
	{
		ChangeGameSpeed(TileMoveSpeed+SpeedIncrease);
	}
}

void ACrowMazeGameModeBase::ChangeGameSpeed(const float NewSpeed)
{
	TileMoveSpeed = NewSpeed;
	OnSpeedAgainChanged.Broadcast(TileMoveSpeed);
	UE_LOG(LogTemp, Error, TEXT("New passed score is %f"), TileMoveSpeed)
}

void ACrowMazeGameModeBase::StartEndlessRunner()
{
	GameEndlessIsOn = true;
	ChangeGameSpeed(StartingTileSpeed);
	OnGameStarted.Broadcast(this);
	UE_LOG(LogTemp, Error, TEXT("I StartEndlessRunner from C++"))

}

void ACrowMazeGameModeBase::TestWithThommy(int NewScoreToTest)
{
	//UE_LOG(LogTemp, Error, TEXT("New passed score is %i"), NewScoreToTest)
}


void ACrowMazeGameModeBase::SetHalfSize_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("I Called SetHalfSize from C++"))
}

