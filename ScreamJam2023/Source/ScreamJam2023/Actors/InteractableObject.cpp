// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableObject.h"
#include "Kismet/GameplayStatics.h"

#include "Components/WidgetComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Sound/SoundBase.h"


AInteractableObject::AInteractableObject()
{
	PrimaryActorTick.bCanEverTick = true;

	InteractableObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	InteractableObjectMesh->SetupAttachment(RootComponent);
	
}

void AInteractableObject::Interact()
{
	if(InteractSFX) UGameplayStatics::SpawnSoundAtLocation(this, InteractSFX, GetActorLocation());
	InteractEvent();
}

void AInteractableObject::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
