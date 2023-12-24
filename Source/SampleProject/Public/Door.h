// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TZCore\Public/Interface/InteractiveObjectInterface.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UCapsuleComponent;

UCLASS()
class SAMPLEPROJECT_API ADoor : public AActor, public IInteractiveObjectInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ============== IInteractiveObjectInterface ================
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Door, meta = (AllowPrivateAccess = "True"))
	TObjectPtr<UCapsuleComponent>	CollisionForInteraction;

	TWeakInterfacePtr<IPlayerInteractionInterface>	InteractingCharacterInterface;

	static FName CapsuleComponentName;

public:
	virtual void DoInteract(IPlayerInteractionInterface* PlayerInteractionInterface) override;
	virtual void EndInteract() override;
	virtual bool ShouldInteract() override;
};
