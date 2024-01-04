// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TZCore/Public/Interface/PlayerInteractionInterface.h"
#include "MyCharacter.generated.h"

class IAvatarInteractableInterface;
class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;

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

	//================= Weapon ===============
protected:
	UPROPERTY(EditDefaultsOnly, Category="MyCharacter | Weapon")
	TSubclassOf<AActor> WeaponClass;
	TObjectPtr<AActor> Weapon;

public:
	bool SetWeapon(AActor* NewWeapon);

	//============== EnhancedInput ===================
public:
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TSoftObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TSoftObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TSoftObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TSoftObjectPtr<UInputAction> MoveAction;

protected:
	void Move(const FInputActionInstance& Instance);
	void Look(const FInputActionInstance& Instance);
};
