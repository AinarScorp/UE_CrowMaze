// Fill out your copyright notice in the Description page of Project Settings.


#include "Crow.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SphereComponent.h"
#include "CrowMaze/CrowMazeGameModeBase.h"
#include "CrowMaze/ActorComponents/CrowAttributes.h"
#include "Kismet/GameplayStatics.h"

ACrow::ACrow()
{
	PrimaryActorTick.bCanEverTick = true;
	CreateComponents();
	bIsAlive = true;
}


void ACrow::CreateComponents()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SetRootComponent(SphereComponent);
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	CrowAttributes = CreateDefaultSubobject<UCrowAttributes>(TEXT("Crow Attributes"));
}
void ACrow::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACrow::SteerBird);
	}
}

void ACrow::SetupEnhancedController() const
{
	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(BirdMappingContext, 0);
		}
	}
}
void ACrow::BeginPlay()
{
	Super::BeginPlay();
	SetupEnhancedController();
}
void ACrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ACrow::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	if (CrowAttributes)
	{
		if (CrowAttributes->GetCurrentLife() <= 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Already dead"))

			return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		}
		CrowAttributes->ModifyLife(-DamageAmount);
		if (CrowAttributes->GetCurrentLife() == 0)
		{
			ExecuteDeath();
		}
	}
	OnDamageTaken.Broadcast();
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}


void ACrow::SteerBird(const FInputActionValue& Value)
{
	const FVector2D InputVector = Value.Get<FVector2D>();
	const FVector MovementDirection{0, InputVector.X, InputVector.Y};
	AddMovementInput(MovementDirection);
}



void ACrow::ExecuteDeath()
{
	bIsAlive = false;
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		ACrow::DisableInput(PlayerController);
	}
	ACrowMazeGameModeBase* CrowMazeGameMode = nullptr;
	if (AGameModeBase* GameModeBase = UGameplayStatics::GetGameMode(GetWorld()))
	{
		CrowMazeGameMode = Cast<ACrowMazeGameModeBase>(GameModeBase);
	}
	if (CrowMazeGameMode == nullptr)
	{
		return;
	}
	CrowMazeGameMode->TriggerGameOver();
}
bool ACrow::IsGrounded()
{
	const FVector TargetLocation;
	const TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	
	return UKismetSystemLibrary::LineTraceSingle(
		GetWorld(), GetActorLocation(), TargetLocation,
		ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore,EDrawDebugTrace::None,
		HitResult,true
		);
}
