// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TZWeapon.generated.h"

class ACharacter;
class UInputAction;
struct FInputActionInstance;
 
UCLASS()
class SAMPLEPROJECT_API ATZWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATZWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void BP_AttackAction();

protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	TObjectPtr<ACharacter> OwnerCharacter;

public:
	void InitCharacter(ACharacter* NewOwnerCharacter);

protected:
	void ClearCharacterInput(ACharacter* TargetCharacter);
	void SetupCharacterInput(ACharacter* TargetCharacter);

	//================= Input ===============
protected:
	UPROPERTY(EditDefaultsOnly, Category = "TZWeapon | Input")
	TSoftObjectPtr<UInputAction> AttackInputAction;

public:
	void Attack(const FInputActionInstance& Instance);
};
