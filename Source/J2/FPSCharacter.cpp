// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include <Engine/Classes/Components/CapsuleComponent.h>
#include "GameFramework/CharacterMovementComponent.h"

#include "FPSProjectile.h"

#include "Components/CapsuleComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AFPSCharacter::AFPSCharacter() : 
	WalkSpeed(300.f),
	RunSpeed(1000.f)

{

	PrimaryActorTick.bCanEverTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0 + BaseEyeHeight));
	FPSCameraComponent->bUsePawnControlRotation = true;

	FPSMesh= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FPSMesh->SetOnlyOwnerSee(true);
	FPSMesh->SetupAttachment(FPSCameraComponent);
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	FPSMesh->AddRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	FPSMesh->AddRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	

	GunMesh= CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	GunMesh->SetOnlyOwnerSee(true);
	GunMesh-> bCastDynamicShadow = false;
	GunMesh->CastShadow = false;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLocation->SetupAttachment(GunMesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	GetMesh()->SetOwnerNoSee(true);


}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	GunMesh->AttachToComponent(FPSMesh,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		TEXT("GripPoint"));

	World = GetWorld();
	AnimInstance = FPSMesh->GetAnimInstance();
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);
	
	InputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::StopJump);

	InputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);
	
	InputComponent->BindAction("Dash", IE_Pressed, this, &AFPSCharacter::Running);
	InputComponent->BindAction("Dash", IE_Released, this, &AFPSCharacter::StopRunning);
}

void AFPSCharacter::MoveForward(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

void AFPSCharacter::MoveRight(float AxisValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::StopJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	if (World != NULL)
	{
		SpawnRotation = GetControlRotation();

		SpawnLocation = ((MuzzleLocation != nullptr) ?
			MuzzleLocation->GetComponentLocation() : 
			GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		World->SpawnActor<AFPSProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
	
	/*if (ProjectileClass)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

			if (Projectile)
			{
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}*/
}

void AFPSCharacter::Running()
{
	if (GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.0f)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	}
}

void AFPSCharacter::StopRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}