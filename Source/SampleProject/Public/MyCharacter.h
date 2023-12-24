// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TZCore/Public/Interface/PlayerInteractionInterface.h"
#include "MyCharacter.generated.h"

class IAvatarInteractableInterface;

UCLASS()
class SAMPLEPROJECT_API AMyCharacter : public ACharacter, public IPlayerInteractionInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//================ Interact =======================
public:
	void SetInteractedInterface(IAvatarInteractableInterface* pInteractedInterface) {}

protected:
	virtual void OnUpdatePriorityInteractiveObject() override;
};
