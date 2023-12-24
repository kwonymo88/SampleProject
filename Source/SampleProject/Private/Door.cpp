// Fill out your copyright notice in the Description page of Project Settings.
#include "Door.h"
#include "Components/CapsuleComponent.h"
#include "Interface/PlayerInteractionInterface.h"

FName ADoor::CapsuleComponentName(TEXT("CollisionForInteraction"));

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	if (CollisionForInteraction = CreateDefaultSubobject<UCapsuleComponent>(ADoor::CapsuleComponentName))
	{
		CollisionForInteraction->SetupAttachment(GetRootComponent());
		
		SetCollisionComponent(CollisionForInteraction);
	}
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor::DoInteract(IPlayerInteractionInterface* PlayerInteractionInterface)
{
	InteractingCharacterInterface = PlayerInteractionInterface;
}

void ADoor::EndInteract()
{
	InteractingCharacterInterface = nullptr;
}

bool ADoor::ShouldInteract()
{
	if (InteractingCharacterInterface.IsValid())
	{
		return false;
	}

	return true;
}
