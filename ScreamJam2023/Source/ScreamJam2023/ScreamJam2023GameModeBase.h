// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ScreamJam2023GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SCREAMJAM2023_API AScreamJam2023GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Lose condition */
	UFUNCTION(BlueprintCallable)
	void RegisterNest();
	UFUNCTION(BlueprintCallable)
	void RemoveNestAndCheckVictory();

	/** Events */
	UFUNCTION(BlueprintImplementableEvent)
	void WinCondition();
	UFUNCTION(BlueprintImplementableEvent)
	void LoseCondition();



private:
	/** Variables */
	UPROPERTY(EditAnywhere, Category="Variables", meta=(AllowPrivateAccess="true"))
	class USoundBase* OneMoreToGo;
	UPROPERTY(EditAnywhere, Category="Variables", meta=(AllowPrivateAccess="true"))
	class USoundBase* TwoMoreToGo;
	UPROPERTY(EditAnywhere, Category="Variables", meta=(AllowPrivateAccess="true"))
	class USoundBase* ThreeMoreToGo;

	float NumberOfNestRemaining = 0.f;
	
};
