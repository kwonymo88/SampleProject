// Fill out your copyright notice in the Description page of Project Settings.

#include "TZWeapon.h"
#include "GameFramework/Character.h"
#include "EnhancedInputComponent.h"

// Sets default values
ATZWeapon::ATZWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATZWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATZWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATZWeapon::InitCharacter(ACharacter* NewOwnerCharacter)
{
	if (OwnerCharacter != NewOwnerCharacter)
	{
		ClearCharacterInput(OwnerCharacter);
		OwnerCharacter = NewOwnerCharacter;
		SetupCharacterInput(OwnerCharacter);
	}
}

void ATZWeapon::ClearCharacterInput(ACharacter* TargetCharacter)
{
	if (TargetCharacter)
	{
		if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(TargetCharacter))
		{
			EnhancedInputComp->ClearBindingsForObject(this);
		}
	}
}

void ATZWeapon::SetupCharacterInput(ACharacter* TargetCharacter)
{
	if (TargetCharacter)
	{
		if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(TargetCharacter->InputComponent))
		{
			EnhancedInputComp->BindAction(AttackInputAction.LoadSynchronous(), ETriggerEvent
				::Triggered, this, &ATZWeapon::Attack);
		}
	}
}

void ATZWeapon::Attack(const FInputActionInstance& Instance)
{
	BP_AttackAction();
}

