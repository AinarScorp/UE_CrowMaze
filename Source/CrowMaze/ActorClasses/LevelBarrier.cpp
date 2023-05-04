// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelBarrier.h"

#include "Obstacle.h"
#include "CrowMaze/CrowMazeGameModeBase.h"
#include "CrowMaze/PawnClasses/Crow.h"
#include "Kismet/GameplayStatics.h"

ALevelBarrier::ALevelBarrier()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelBarrier::BeginPlay()
{
	Super::BeginPlay();
	if (bIsCreated)
	{
		return;
	}
	SetHalfSize();
	FindCrowPlayer();
	SubscribeOnGameSpeedChange();
}

void ALevelBarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector TargetLocation = GetActorLocation() + MoveDirection * MoveSpeed * DeltaTime;
	SetActorLocation(TargetLocation);
}


void ALevelBarrier::SpawnActor_Implementation(const FVector& NewLocation, const FRotator& NewRotation)
{
	Super::SpawnActor_Implementation(NewLocation, NewRotation);
	bHasOverlappedOnce = false;

}

void ALevelBarrier::AttachObstacle(TObjectPtr<AObstacle> ObstacleToAttach)
{
	AttachedObstacles.Add(ObstacleToAttach);
}

void ALevelBarrier::SubscribeOnGameSpeedChange()
{
	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
	if (!GameModeBase)
	{
		return;
	}
	CrowMazeGameMode = Cast<ACrowMazeGameModeBase>(GameModeBase);
	if (!CrowMazeGameMode)
	{
		return;
	}
	CrowMazeGameMode->OnSpeedAgainChanged.AddDynamic(this, &ALevelBarrier::ActivateSpeed);

	if (CrowMazeGameMode->GetGameEndlessIsOn())
	{
		ActivateSpeed(CrowMazeGameMode->GetTileMoveSpeed());
	}
}

void ALevelBarrier::FindCrowPlayer()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), PlayerTag, OutActors);
	if (OutActors.Num() <= 0)
	{
		return;
	}
	CrowPlayer = Cast<ACrow>(OutActors[0]);
	if (CrowPlayer == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Crow player has not been found"))
	}
}


void ALevelBarrier::ActivateSpeed(float GameModeSpeed)
{
	MoveSpeed = GameModeSpeed;
}

void ALevelBarrier::OnBeginOverlapSpawnNewTile(AActor* OtherActor)
{
	if (bHasOverlappedOnce || CrowPlayer == nullptr || OtherActor != CrowPlayer || !CrowMazeGameMode)
	{
		return;
	}
	CrowMazeGameMode->SpawnTile(false);
	SetLifeSpan(3.0);
	bHasOverlappedOnce = true;
	if (AttachedObstacles.Num() < 1)
	{
		return;
	}
	DestroyAttachedObstacles();
}

void ALevelBarrier::DestroyAttachedObstacles()
{
	for (TObjectPtr<AObstacle> Obstacle : AttachedObstacles)
	{
		if (Obstacle == nullptr)
		{
			return;
		}
		if (CrowMazeGameMode)
		{
			CrowMazeGameMode->RemoveObstacleFromList(Obstacle);
			if (!Obstacle->GetHitCrow())
			{
				CrowMazeGameMode->RewardPlayersByRemovingObstacle();
			}
		}
		Obstacle->Destroy();
	}
	AttachedObstacles.Empty();
}


// void ALevelBarrier::GetObstaclePoints_Implementation(TArray<USceneComponent*>& ObstaclePoints)
// {
// }


//
// TArray<UObstaclePoint*> ALevelBarrier::GetObstaclePoints2_Implementation()
// {
// 	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 30, FColor::Red, TEXT("THIS SHOULD NEVER HAPPEN"));
//
// 	return {};
// }


#pragma region Commentedout
//
// void ALevelBarrier::SetLifeSpan(float InLifespan)
// {
// 	LifeSpan = InLifespan;
// 	//UE_LOG(LogTemp,Warning,TEXT("I happened"))
// 	//GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &ALevelBarrier::DeactivateMy_Implementation, LifeSpan,false);
// }

// TObjectPtr<AActor> ALevelBarrier::GetActorMy()
// {
// 	return this;
// }

// void ALevelBarrier::SpawnActor_Implementation()
// {
// 	IPoolableActor::SpawnActor_Implementation();
// 	Execute_SetActiveMy(this,true);
// }
//
//
// void ALevelBarrier::SetActiveMy_Implementation(bool InActive)
// {
// 	IPoolableActor::SetActiveMy_Implementation(InActive);
// 	bIsActive = InActive;
// 	//RootComponent->SetHiddenInGame(bIsActive, true);
// 	SetActorHiddenInGame(!bIsActive);
// 	SetActorTickEnabled(InActive);
// }
//
// bool ALevelBarrier::IsActiveMy_Implementation()
// {
// 	return bIsActive;
// }
//
// float ALevelBarrier::GetLifeSpanMy_Implementation()
// {
// 	return LifeSpan;
// }
//
// void ALevelBarrier::DeactivateMy_Implementation()
// {
// 	Execute_SetActiveMy(this, false);
// }
//
#pragma endregion
