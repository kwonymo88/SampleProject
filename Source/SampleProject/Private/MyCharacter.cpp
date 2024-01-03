// Fill out your copyright notice in the Description page of Project Settings.
#include "MyCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (!DefaultMappingContext.IsNull())
			{
				EnhancedInputSubsystem->AddMappingContext(DefaultMappingContext.LoadSynchronous(), 0);
			}
		}
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComp->BindAction(JumpAction.LoadSynchronous(), ETriggerEvent
		::Triggered, this, &AMyCharacter::Jump);
		EnhancedInputComp->BindAction(JumpAction.LoadSynchronous(), ETriggerEvent
			::Completed, this, &AMyCharacter::StopJumping);
		EnhancedInputComp->BindAction(LookAction.LoadSynchronous(), ETriggerEvent
			::Triggered, this, &AMyCharacter::Look);
		EnhancedInputComp->BindAction(MoveAction.LoadSynchronous(), ETriggerEvent
			::Triggered, this, &AMyCharacter::Move);
	}
}

void AMyCharacter::OnUpdatePriorityInteractiveObject()
{

}

void AMyCharacter::Move(const FInputActionInstance& Instance)
{
	if (Controller)
	{
		FVector2D MovementVector = Instance.GetValue().Get<FVector2D>();
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector FowardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(FowardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMyCharacter::Look(const FInputActionInstance& Instance)
{
	FVector2D LookVector = Instance.GetValue().Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

