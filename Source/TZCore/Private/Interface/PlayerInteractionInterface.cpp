#include "Interface/PlayerInteractionInterface.h"
#include "Interface/InteractiveObjectInterface.h"

UPlayerInteractionInterface::UPlayerInteractionInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void IPlayerInteractionInterface::DeterminePriorityInteractiveObject()
{
	if (OverlappedInteractiveObject.IsEmpty())
	{
		SetPriorityInteractiveObject(nullptr);
	}
	else
	{
		//필요시 우선순위 조건 추가
		for (const auto& InteractiveObject : OverlappedInteractiveObject)
		{
			if (InteractiveObject.IsValid())
			{
				SetPriorityInteractiveObject(InteractiveObject.Get());
				break;
			}
		}
	}
}

void IPlayerInteractionInterface::SetPriorityInteractiveObject(IInteractiveObjectInterface* NewPriorityInteractiveObject)
{
	if (PriorityInteractiveObject != NewPriorityInteractiveObject)
	{
		if (PriorityInteractiveObject.IsValid())
		{
			PriorityInteractiveObject->EndInteract();
		}
		PriorityInteractiveObject = NewPriorityInteractiveObject;
		OnUpdatePriorityInteractiveObject();
	}
}

void IPlayerInteractionInterface::OnUpdatePriorityInteractiveObject()
{

}

void IPlayerInteractionInterface::TryInteract()
{
	if (PriorityInteractiveObject.IsValid()
		&& PriorityInteractiveObject->ShouldInteract())
	{
		PriorityInteractiveObject->DoInteract(this);
	}
}

void IPlayerInteractionInterface::AddOverlappedInteractiveObject(IInteractiveObjectInterface* NewOverlappedInteractiveObject)
{
	OverlappedInteractiveObject.AddUnique(NewOverlappedInteractiveObject);
	DeterminePriorityInteractiveObject();
}

void IPlayerInteractionInterface::RemoveOverlappedInteractiveObject(IInteractiveObjectInterface* RemoveOverlappedInteractiveObject)
{
	OverlappedInteractiveObject.Remove(RemoveOverlappedInteractiveObject);
	if (PriorityInteractiveObject == RemoveOverlappedInteractiveObject)
	{
		DeterminePriorityInteractiveObject();
	}
}
