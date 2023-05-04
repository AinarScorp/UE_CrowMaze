// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

#include "LevelBarrier.h"
#include "CrowMaze/CrowMazeGameModeBase.h"
#include "CrowMaze/PawnClasses/Crow.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetArrayLibrary.h"

// Sets default values
AObstacle::AObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HitCrow = false;
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	HitActors.Empty();
	HitCrow = false;
}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// void AObstacle::RemoveObstacle()
// {
// 	AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld());
// 	if (ACrowMazeGameModeBase* CrowMazeGameMode  = Cast<ACrowMazeGameModeBase>(GameModeBase))
// 	{
// 		CrowMazeGameMode->RemoveObstacleFromList(this);
// 	}
// 	this->Destroy();
// }

void AObstacle::CollideWithThePlayer(AActor* CrowActor)
{
	if (HitActors.Contains(CrowActor) || !Cast<ACrow>(CrowActor))
	{
		return;
	}
	HitActors.Add(CrowActor);
	UGameplayStatics::ApplyDamage(CrowActor, ObstacleHitDamage, nullptr, this, UDamageType::StaticClass());
	HitCrow = true;
	//Destroy();
}

void AObstacle::CreateObstacle_Implementation(ALevelBarrier* LevelBarrier)
{
	if (LevelBarrier == nullptr)
	{
		return;
	}
	//ConnectedLevelBarrier = LevelBarrier;
	LevelBarrier->AttachObstacle(this);
	AttachToActor(LevelBarrier, FAttachmentTransformRules::KeepWorldTransform);
	
	SetActorLocation(LevelBarrier->GetActorLocation());
}



