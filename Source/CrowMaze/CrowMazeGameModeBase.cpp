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
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),MiddlePointTag,OutActors);
	if (OutActors.Num() <= 0)
	{
		return;
	}
	//const FVector PlayerStartLocation = UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetActorLocation();
	TileSpawnLocation = OutActors[0]->GetActorLocation();
	SpawnStartingTiles();
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
	/*TODO: Here you can increase spawn chance if the previous tile didn't create the obstacle, so eventually something will spawn
		TODO: and you can have spawn chance lower in the beginning 
	*/
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

}

bool ACrowMazeGameModeBase::ShouldIncreaseSpeed()
{
	if (TileMoveSpeed >=MaxTileSpeed)
	{
		return false;
	}
	return CurrentScore % SpeedIncreaseDivisorPerScore == 0;
}

void ACrowMazeGameModeBase::IncreaseSpeed()
{
	if (ShouldIncreaseSpeed())
	{
		ChangeGameSpeed(TileMoveSpeed+SpeedIncrease);
		SpeedIncreaseDivisorPerScore+= SpeedIncreaseDivisorPerScoreIncrease;
	}
}

void ACrowMazeGameModeBase::ChangeGameSpeed(const float NewSpeed)
{
	TileMoveSpeed = NewSpeed;
	if (TileMoveSpeed >MaxTileSpeed)
	{
		TileMoveSpeed = MaxTileSpeed;
	}
	OnSpeedAgainChanged.Broadcast(TileMoveSpeed);
}

void ACrowMazeGameModeBase::StartEndlessRunner()
{
	GameEndlessIsOn = true;
	ChangeGameSpeed(StartingTileSpeed);
	OnGameStarted.Broadcast(this);

}

void ACrowMazeGameModeBase::TriggerGameOver_Implementation()
{
	
	ChangeGameSpeed(0);
	UE_LOG(LogTemp, Warning, TEXT("Game is over with The score of: %i"), CurrentScore)
	OnGameOver.Broadcast();
}

void ACrowMazeGameModeBase::TestWithThommy(int NewScoreToTest)
{
}


void ACrowMazeGameModeBase::SetHalfSize_Implementation()
{
	APoolableActorAbstact* PoolableActor=TerrainPool->GetPooledActor();
	if (PoolableActor)
	{
		if (ALevelBarrier* LevelBarrier = Cast<ALevelBarrier>(PoolableActor))
		{
		    TerrainHalfSize = LevelBarrier->GetHalfSize();
		}
		
	}
}

