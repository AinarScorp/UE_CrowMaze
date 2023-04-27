// Fill out your copyright notice in the Description page of Project Settings.


#include "Crow.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SphereComponent.h"
#include "CrowMaze/ActorComponents/CrowAttributes.h"
#include "Kismet/GameplayStatics.h"

ACrow::ACrow()
{
	PrimaryActorTick.bCanEverTick = true;
	CreateComponents();
}

void ACrow::CreateComponents()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SetRootComponent(SphereComponent);
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	CrowAttributes = CreateDefaultSubobject<UCrowAttributes>(TEXT("Crow Attributes"));
}


void ACrow::BeginPlay()
{
	Super::BeginPlay();
	SetupEnhancedController();
}


float ACrow::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp,Warning, TEXT("CROW GOT HIT"))
	if (CrowAttributes)
	{
		CrowAttributes->ModifyLife(-DamageAmount);
	}
	OnDamageTaken.Broadcast();
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}


void ACrow::SetupEnhancedController() const
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(BirdMappingContext, 0);
		}
	}
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


void ACrow::SteerBird(const FInputActionValue& Value)
{
	const FVector2D InputVector = Value.Get<FVector2D>();
}

void ACrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


