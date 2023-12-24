#include "Interface/InteractiveObjectInterface.h"
#include "Interface/PlayerInteractionInterface.h"
#include "Components/CapsuleComponent.h"

UInteractiveObjectInterface::UInteractiveObjectInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void IInteractiveObjectInterface::OnInteractCharacter(IPlayerInteractionInterface* CurrentPawn, IPlayerInteractionInterface* PrevPawn)
{
	if (_OnChangedPlayerDelegate.IsBound())
	{
		_OnChangedPlayerDelegate.Broadcast(this, CurrentPawn, PrevPawn);
	}
}

void IInteractiveObjectInterface::DoInteract(IPlayerInteractionInterface* PlayerInteractionInterface)
{
	
}

void IInteractiveObjectInterface::EndInteract()
{

}

void IInteractiveObjectInterface::SetCollisionComponent(UCapsuleComponent* CollisionComp)
{
	if (CollisionComp == nullptr
		|| InteractiveCapsuleComponent != nullptr)
		return;

	InteractiveCapsuleComponent = CollisionComp;
	if (InteractiveCapsuleComponent.IsValid())
	{
		InteractiveCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &IInteractiveObjectInterface::OnBeginOverlap);
		InteractiveCapsuleComponent->OnComponentEndOverlap.AddDynamic(this, &IInteractiveObjectInterface::OnEndOverlap);
	}
}

bool IInteractiveObjectInterface::ShouldInteract()
{
	return true;
}

void IInteractiveObjectInterface::EnableInteract()
{
	if (_OnEnableInteractDelegate.IsBound())
	{
		_OnEnableInteractDelegate.Broadcast(this);
	}
}

void IInteractiveObjectInterface::DisableInteract()
{
	if (_OnDisableInteractDelegate.IsBound())
	{
		_OnDisableInteractDelegate.Broadcast(this);
	}
}

void IInteractiveObjectInterface::DeactivateInteract()
{
	if (_OnDeactivateInteractDelegate.IsBound())
	{
		_OnDeactivateInteractDelegate.Broadcast(this);
	}
}

void IInteractiveObjectInterface::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Other &&
		Other->GetClass()->ImplementsInterface(UPlayerInteractionInterface::StaticClass()))
	{
		if (IPlayerInteractionInterface* pPlayerInteractionInterface = Cast<IPlayerInteractionInterface>(Other))
		{
			pPlayerInteractionInterface->AddOverlappedInteractiveObject(this);
		}
	}
}

void IInteractiveObjectInterface::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor &&
		OtherActor->GetClass()->ImplementsInterface(UPlayerInteractionInterface::StaticClass()))
	{
		if (IPlayerInteractionInterface* pPlayerInteractionInterface = Cast<IPlayerInteractionInterface>(OtherActor))
		{
			pPlayerInteractionInterface->RemoveOverlappedInteractiveObject(this);
		}
	}
}
