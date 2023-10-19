// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayAudioOnceInVolume.generated.h"

UCLASS()
class SCREAMJAM2023_API APlayAudioOnceInVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayAudioOnceInVolume();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	/** Components */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollider;

	/** Variables */
	UPROPERTY(EditAnywhere, Category="Variables", meta=(AllowPrivateAccess="true"))
	class USoundBase* OverlapAudio;

	UPROPERTY(EditAnywhere, Category="Variables", meta=(AllowPrivateAccess="true"))
	bool bPlayAudioOnce = true;

	bool bPlayAudio = true;

	/** Functions */
	UFUNCTION(BlueprintCallable)
	void PlayAudio();


};
