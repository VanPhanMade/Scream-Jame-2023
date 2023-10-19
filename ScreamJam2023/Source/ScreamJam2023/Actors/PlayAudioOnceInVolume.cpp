// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayAudioOnceInVolume.h"
#include "Kismet/GameplayStatics.h"

#include "Components/BoxComponent.h"

#include "Sound/SoundBase.h"

APlayAudioOnceInVolume::APlayAudioOnceInVolume()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	BoxCollider->SetupAttachment(RootComponent);
}

void APlayAudioOnceInVolume::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayAudioOnceInVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayAudioOnceInVolume::PlayAudio()
{
	if(!bPlayAudio) return;

	if(OverlapAudio) UGameplayStatics::SpawnSoundAtLocation(this, OverlapAudio, GetActorLocation());
	if(bPlayAudioOnce) bPlayAudio = false;
}
