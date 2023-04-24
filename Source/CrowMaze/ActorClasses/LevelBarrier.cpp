// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelBarrier.h"

#include "Obstacle.h"
#include "CrowMaze/SceneComponents/ObstaclePoint.h"

ALevelBarrier::ALevelBarrier()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALevelBarrier::BeginPlay()
{
	Super::BeginPlay();
}

void ALevelBarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALevelBarrier::SpawnActor_Implementation(const FVector& NewLocation, const FRotator& NewRotation)
{
	Super::SpawnActor_Implementation(NewLocation, NewRotation);
	if (AttachedObstacles.Num()<1)
	{
		return;
	}
	for (TObjectPtr<AObstacle> Obstacle : AttachedObstacles)
	{
		if (Obstacle != nullptr)
		{
			Obstacle->Destroy();
		}
	}
	AttachedObstacles.Empty();
}

void ALevelBarrier::AttachObstacle(TObjectPtr<AObstacle> ObstacleToAttach)
{
	AttachedObstacles.Add(ObstacleToAttach);
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
