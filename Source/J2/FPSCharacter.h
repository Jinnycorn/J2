// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Engine/Classes/Camera/CameraComponent.h>
#include "FPSProjectile.h"
#include "FPSCharacter.generated.h"

UCLASS()
class J2_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void MoveForward(float AxisValue);

	UFUNCTION()
	void MoveRight(float AxisValue);


	UFUNCTION()
	void StartJump();
	
	UFUNCTION()
	void StopJump();

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void Running();

	UFUNCTION()
	void StopRunning();


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Movement",meta=(AllowPrivateAccess="true"))
	float WalkSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RunSpeed;


	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AFPSProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class UAnimMontage* FireAnimation;

	class UAnimInstance* AnimInstance;

	class UWorld* World;

	FRotator SpawnRotation;
	FVector SpawnLocation;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* FPSCameraComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* FPSMesh;

	//UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	//USkeletalMeshComponent* HandsMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USceneComponent* MuzzleLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	FVector GunOffset;

	


	

};
