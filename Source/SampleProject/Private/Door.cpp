// Fill out your copyright notice in the Description page of Project Settings.
#include "Door.h"
#include "Components/CapsuleComponent.h"
#include "Interface/PlayerInteractionInterface.h"

FName ADoor::CapsuleComponentName(TEXT("CollisionForInteraction"));

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (CollisionForInteraction = CreateDefaultSubobject<UCapsuleComponent>(ADoor::CapsuleComponentName))
	{
		CollisionForInteraction->SetupAttachment(GetRootComponent());
		SetRootComponent(CollisionForInteraction);


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
	if (!ShouldInteract())
		return;

	if (InteractingCharacterInterface == PlayerInteractionInterface)
		return;

	bool bSucceedAction = false;
	if (DoorState == EDoorState::Open)
	{
		bSucceedAction = CloseDoor();
	}
	else if (DoorState == EDoorState::Close)
	{
		bSucceedAction = OpenDoor();
	}

	if (bSucceedAction)
	{
		IPlayerInteractionInterface* PrevPlayerInteractionInterface = InteractingCharacterInterface.IsValid() ? InteractingCharacterInterface.Get() : nullptr;
		InteractingCharacterInterface = PlayerInteractionInterface;

		OnInteractCharacter(PlayerInteractionInterface, PrevPlayerInteractionInterface);
	}
}

bool ADoor::OpenDoor()
{
	SetDoorState(EDoorState::Opening);
	BeginOpening();

	return true;
}

bool ADoor::CloseDoor()
{
	SetDoorState(EDoorState::Closing);
	BeginClosing();

	return true;
}

void ADoor::EndOpening()
{
	SetDoorState(EDoorState::Close);
}

void ADoor::EndClosing()
{
	SetDoorState(EDoorState::Open);
}

void ADoor::SetDoorState(const EDoorState NewDoorState)
{
	if (DoorState == NewDoorState)
		return;

	DoorState = NewDoorState;

	if (OnChangedDoorState.IsBound())
	{
		OnChangedDoorState.Broadcast(DoorState);
	}
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

	if (!ShouldActionDoorState())
	{
		return false;
	}

	return true;
}

bool ADoor::ShouldActionDoorState()
{
	if (DoorState == EDoorState::Open
		|| DoorState == EDoorState::Close)
	{
		return true;
	}

	return false;
}