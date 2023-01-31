// Fill out your copyright notice in the Description page of Project Settings.


#include "Crow.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/SphereComponent.h"
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
	//RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMeshComponent->SetupAttachment(RootComponent);
}


void ACrow::BeginPlay()
{
	Super::BeginPlay();
	SetupEnhancedController();
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
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACrow::LookBird);
		EnhancedInputComponent->BindAction(SteerAction, ETriggerEvent::Triggered, this, &ACrow::SteerBird);
	}
}
void ACrow::LookBird(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ACrow::SteerBird(const FInputActionValue& Value)
{
	const FVector2D InputVector = Value.Get<FVector2D>();
	AddToDesiredRotationFloat(ERotationFloat::Pitch, InputVector.Y * PitchScale);
	AddToDesiredRotationFloat(ERotationFloat::Yaw, InputVector.X * YawScale);
	AddToDesiredRotationFloat(ERotationFloat::Roll,InputVector.X * RollScale);
}

void ACrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//AddMovementInput(GetActorForwardVector(), ForwardMovementScale);
	RotateBirdToDesiredRotation(DeltaTime);
}


float ACrow::ConsumeRotationValue(float& ValueToConsume, const float DeltaTime, const float Scale)
{
	if (ValueToConsume == 0)
	{
		return ValueToConsume;
	}
	//float ValueToReturn = ValueToConsume;
	ValueToConsume = FMath::FInterpConstantTo(ValueToConsume, 0, DeltaTime, Scale);
	return ValueToConsume;
}

void ACrow::RotateBirdToDesiredRotation(float DeltaTime)
{
	const FRotator AddedRotation{
		ConsumeRotationValue(DesiredPitch, DeltaTime, ConsumptionScale),
		ConsumeRotationValue(DesiredYaw, DeltaTime, ConsumptionScale)+ GetActorRotation().Yaw,
		ConsumeRotationValue(DesiredRoll, DeltaTime, ConsumptionScale)
	};

	const FRotator DesiredRotation = FMath::RInterpConstantTo(GetActorRotation(), AddedRotation, DeltaTime, 100); //THINK ABOUT IT
	SetActorRotation(DesiredRotation);
}

void ACrow::AddToDesiredRotationFloat(ERotationFloat RotationFloat, float ValueToAdd, bool Reset)
{
	switch (RotationFloat)
	{
	case ERotationFloat::Pitch:
		if (Reset)
		{
			DesiredPitch = 0;
		}
		
		DesiredPitch = FMath::Clamp(DesiredPitch+ValueToAdd,PitchMin,PitchMax);
		break;

	case ERotationFloat::Yaw:
		if (Reset)
		{
			DesiredYaw = 0;
		}
		DesiredYaw = FMath::Clamp(DesiredYaw+ValueToAdd,YawMin,YawMax);
		break;
	case ERotationFloat::Roll:
		if (Reset)
		{
			DesiredRoll = 0;
		}
		DesiredRoll = FMath::Clamp(DesiredRoll+ValueToAdd,RollMin,RollMax);
		break;
	default: ;
	}
}

