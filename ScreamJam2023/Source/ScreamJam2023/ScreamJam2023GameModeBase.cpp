// Copyright Epic Games, Inc. All Rights Reserved.


#include "ScreamJam2023GameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "Sound/SoundBase.h"

void AScreamJam2023GameModeBase::RegisterNest()
{
    NumberOfNestRemaining++;
}

void AScreamJam2023GameModeBase::RemoveNestAndCheckVictory()
{
    NumberOfNestRemaining--;
    if(NumberOfNestRemaining == 3)
    {
        if(ThreeMoreToGo) UGameplayStatics::SpawnSoundAtLocation(this, ThreeMoreToGo, FVector::Zero());
    }
    if(NumberOfNestRemaining == 2)
    {
        if(TwoMoreToGo) UGameplayStatics::SpawnSoundAtLocation(this, TwoMoreToGo, FVector::Zero());
    }
    if(NumberOfNestRemaining == 1)
    {
        if(OneMoreToGo) UGameplayStatics::SpawnSoundAtLocation(this, OneMoreToGo, FVector::Zero());
    }

    if(NumberOfNestRemaining <= 0) WinCondition();
}
