// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreamJamCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "../Actors/InteractableObject.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "Sound/SoundBase.h"

AScreamJamCharacter::AScreamJamCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	CharacterLightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spot Light Mesh"));
	CharacterLightMesh->SetupAttachment(RootComponent);

	CharacterLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Spot Light"));
	CharacterLight->SetupAttachment(CharacterLightMesh);
}

void AScreamJamCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

void AScreamJamCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScreamJamCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ThisClass::Interact);
		EnhancedInputComponent->BindAction(ToggleLightAction, ETriggerEvent::Triggered, this, &ThisClass::ToggleLight);
	}

}

void AScreamJamCharacter::Move(const FInputActionValue &Value)
{
	if(!bCanReceiveInput) return; 

	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AScreamJamCharacter::Look(const FInputActionValue &Value)
{
	if(!bCanReceiveInput) return; 

	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AScreamJamCharacter::Interact()
{
	if(!bCanReceiveInput) return; 

	if(InteractSFX) UGameplayStatics::SpawnSoundAtLocation(this, InteractSFX, GetActorLocation());

	FVector TraceStart{GetPawnViewLocation()};
	FVector TraceEnd{TraceStart + (GetViewRotation().Vector() * 150.f)};

	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 2.0f);

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	FHitResult Hit;

	if(GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_GameTraceChannel1, QueryParams))
	{
		AInteractableObject* Interactable = Cast<AInteractableObject>(Hit.GetActor());
		if(Interactable)
		{
			Interactable->Interact();
		}
	}

}

void AScreamJamCharacter::ToggleLight()
{
	if(!bCanReceiveInput) return; 
	
	if(LightToggleSFX) UGameplayStatics::SpawnSoundAtLocation(this, LightToggleSFX, GetActorLocation());
	CharacterLight->ToggleVisibility();
}
