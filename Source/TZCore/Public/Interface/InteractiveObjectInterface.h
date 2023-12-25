// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UObject/WeakInterfacePtr.h"
#include "InteractiveObjectInterface.generated.h"

class IPlayerInteractionInterface;
class IInteractiveObjectInterface;
class UCapsuleComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEnableInteractDelegate, IInteractiveObjectInterface*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDisableInteractDelegate, IInteractiveObjectInterface*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeactivateInteractDelegate, IInteractiveObjectInterface*);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChangedPlayerDelegate, IInteractiveObjectInterface*, IPlayerInteractionInterface* /*CurrentPlayer*/, IPlayerInteractionInterface* /*PrevPlayer*/);

UINTERFACE()
class UInteractiveObjectInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class TZCORE_API IInteractiveObjectInterface : public IInterface
{
	GENERATED_IINTERFACE_BODY()

protected:
	TWeakObjectPtr<UCapsuleComponent> InteractiveCapsuleComponent;

protected:
	FOnEnableInteractDelegate _OnEnableInteractDelegate;
	FOnDisableInteractDelegate _OnDisableInteractDelegate;
	FOnDeactivateInteractDelegate _OnDeactivateInteractDelegate;
	FOnChangedPlayerDelegate _OnChangedPlayerDelegate;

public:
	FOnEnableInteractDelegate& GetOnEnableInteractDelegate() { return _OnEnableInteractDelegate; }
	FOnDisableInteractDelegate& GetOnDisableInteractDelegate() { return _OnDisableInteractDelegate; }
	FOnDeactivateInteractDelegate& GetOnDeactivateInteractDelegate() { return _OnDeactivateInteractDelegate; }
	FOnChangedPlayerDelegate& GetOnChangedPlayerDelegate() { return _OnChangedPlayerDelegate; }

public:
	virtual void DoInteract(IPlayerInteractionInterface* PlayerInteractionInterface);
	virtual void EndInteract();
	virtual void OnInteracting(const bool Interacting) {}
	virtual bool ShouldInteract();
	
protected:
	virtual void SetCollisionComponent(UCapsuleComponent* CollisionComp);
	virtual void OnInteractCharacter(IPlayerInteractionInterface* CurrentPawn, IPlayerInteractionInterface* PrevPawn);

	virtual void EnableInteract();
	virtual void DisableInteract();
	virtual void DeactivateInteract();

protected:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
