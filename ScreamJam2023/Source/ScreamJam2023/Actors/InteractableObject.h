// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

UCLASS()
class SCREAMJAM2023_API AInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractableObject();

	/** Functions */
	void Interact();

	/** Events */
	UFUNCTION(BlueprintImplementableEvent)
	void InteractEvent();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	/** Components */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* InteractableObjectMesh;

	/** Variables */
	UPROPERTY(EditAnywhere, Category="Variables", meta=(AllowPrivateAccess="true"))
	class USoundBase* InteractSFX;



};
