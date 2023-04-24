// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "LevelBarrier.h"
#include "CrowMaze/PawnClasses/Crow.h"
#include "CrowMaze/SceneComponents/ObstaclePoint.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::CollideWithThePlayer(AActor* CrowActor)
{
	if (bHasHitPlayerOnce || !Cast<ACrow>(CrowActor))
	{
		return;
	}
	bHasHitPlayerOnce =true;
	UGameplayStatics::ApplyDamage(CrowActor, ObstacleHitDamage, nullptr, this, UDamageType::StaticClass());
	Destroy();
}

void AObstacle::CreateObstacle_Implementation(ALevelBarrier* LevelBarrier)
{
	if (LevelBarrier == nullptr)
	{
		return;
	}
	LevelBarrier->AttachObstacle(this);
	AttachToActor(LevelBarrier, FAttachmentTransformRules::KeepWorldTransform);
	TArray<UObstaclePoint*> ObstaclePoints = LevelBarrier->GetObstaclePoints();

	SetActorLocation(LevelBarrier->GetActorLocation());

	// const int RandomIndex = FMath::RandRange(0, AcceptableObstaclePositions2.Num()-1);
	// const EObstaclePositionTypes RandomPositionType = AcceptableObstaclePositions2[RandomIndex];
	//
	// for (const UObstaclePoint* ObstaclePoint : ObstaclePoints)
	// {
	// 	if (ObstaclePoint->ObstaclePositionType == RandomPositionType)
	// 	{
	// 		SetActorLocation(ObstaclePoint->GetComponentLocation());
	// 		break;
	// 	}
	// }

	
}



