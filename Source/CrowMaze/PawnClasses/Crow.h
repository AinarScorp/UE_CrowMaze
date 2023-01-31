// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Crow.generated.h"
UENUM()
enum class ERotationFloat :uint8
{
	Pitch,Yaw,Roll
};

UCLASS()
class CROWMAZE_API ACrow : public APawn
{
	GENERATED_BODY()

public:
	ACrow();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UInputMappingContext* BirdMappingContext;
	UPROPERTY(EditAnywhere)
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere)
	class UInputAction* SteerAction;
	
	
	void SteerBird(const FInputActionValue& Value);
	void LookBird(const FInputActionValue& Value);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	//cached
	// UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	// USceneComponent* RootScene;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USphereComponent> SphereComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	//Variables
	//YAW
	UPROPERTY(BlueprintReadOnly,meta = (AllowPrivateAccess = "true")) float DesiredYaw = 0;
	UPROPERTY(EditAnywhere) float PitchScale = 10;
	UPROPERTY(EditAnywhere) float YawMax{180};
	UPROPERTY(EditAnywhere) float YawMin{-180};
	//PITCH
	UPROPERTY(BlueprintReadOnly,meta = (AllowPrivateAccess = "true")) float DesiredPitch= 0;
	UPROPERTY(EditAnywhere) float YawScale = 2;
	UPROPERTY(EditAnywhere) float PitchMax{45};
	UPROPERTY(EditAnywhere) float PitchMin{-45};
	//ROLL
	UPROPERTY(BlueprintReadOnly,meta = (AllowPrivateAccess = "true")) float DesiredRoll= 0;
	UPROPERTY(EditAnywhere) float RollScale = 10;
	UPROPERTY(EditAnywhere) float RollMax{30};
	UPROPERTY(EditAnywhere) float RollMin{-30};

	
	UPROPERTY(EditAnywhere) float ForwardMovementScale = 1;
	UPROPERTY(EditAnywhere) float ConsumptionScale = 100;
	
	//functions
	void CreateComponents();
	void SetupEnhancedController() const;
	float ConsumeRotationValue(float& ValueToConsume, float DeltaTime, float Scale = 1);
	void RotateBirdToDesiredRotation(float DeltaTime);
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void AddToDesiredRotationFloat(ERotationFloat RotationFloat, float ValueToAdd, bool Reset = false);
	
	

};
