// Copyright Epic Games, Inc. All Rights Reserved.

#include "RTSPlayerController.h"

#include "CommandHandler.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ARTSPlayerController::ARTSPlayerController():
	ShortPressThreshold(0), bMoveToMouseCursor(0),
	CommandHandler(nullptr),
	CachedDestination(FVector::ZeroVector), bIsTouch(false), FollowTime(0.0f)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ARTSPlayerController::BeginPlay()
{
	Super::BeginPlay();
	CommandHandler = Cast<UCommandHandler>(AddComponentByClass(UCommandHandler::StaticClass(), false, FTransform::Identity, true));
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("EnhancedInputComponent != NULL"));
}

void ARTSPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	// if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	// {
	// 	Subsystem->AddMappingContext(DefaultMappingContext, 0);
	// }
	//
	// // Set up action bindings
	// if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	// {
	// 	EnhancedInputComponent->BindAction(IssueSelectedCommandAction, ETriggerEvent::Triggered, this, &ThisClass::HandleIssueSelectedCommmand);
	// 	// Setup mouse input events
	// 	EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ARTSPlayerController::OnInputStarted);
	// 	EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this,
	// 	                                   &ARTSPlayerController::OnSetDestinationTriggered);
	// 	EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this,
	// 	                                   &ARTSPlayerController::OnSetDestinationReleased);
	// 	EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this,
	// 	                                   &ARTSPlayerController::OnSetDestinationReleased);
	//
	// 	// Setup touch input events
	// 	EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &ARTSPlayerController::OnInputStarted);
	// 	EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this,
	// 	                                   &ARTSPlayerController::OnTouchTriggered);
	// 	EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this,
	// 	                                   &ARTSPlayerController::OnTouchReleased);
	// 	EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this,
	// 	                                   &ARTSPlayerController::OnTouchReleased);
	// }
	// else
	// {
	// 	UE_LOG(LogTemplateCharacter, Error,
	// 	       TEXT(
	// 		       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
	// 	       ), *GetNameSafe(this));
	// }
}

// void ARTSPlayerController::OnInputStarted()
// {
// 	StopMovement();
// }

// Triggered every frame when the input is held down
// void ARTSPlayerController::OnSetDestinationTriggered()
// {
// 	// We flag that the input is being pressed
// 	FollowTime += GetWorld()->GetDeltaSeconds();
//
// 	// We look for the location in the world where the player has pressed the input
// 	FHitResult Hit;
// 	bool bHitSuccessful = false;
// 	if (bIsTouch)
// 	{
// 		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
// 	}
// 	else
// 	{
// 		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
// 	}
//
// 	// If we hit a surface, cache the location
// 	if (bHitSuccessful)
// 	{
// 		CachedDestination = Hit.Location;
// 	}
//
// 	// Move towards mouse pointer or touch
// 	APawn* ControlledPawn = GetPawn();
// 	if (ControlledPawn != nullptr)
// 	{
// 		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
// 		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
// 	}
// }

// void ARTSPlayerController::OnSetDestinationReleased()
// {
// 	// If it was a short press
// 	if (FollowTime <= ShortPressThreshold)
// 	{
// 		// We move there and spawn some particles
// 		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
// 		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f),
// 		                                               true, true, ENCPoolMethod::None, true);
// 	}
//
// 	FollowTime = 0.f;
// }

// // Triggered every frame when the input is held down
// void ARTSPlayerController::OnTouchTriggered()
// {
// 	bIsTouch = true;
// 	OnSetDestinationTriggered();
// }
//
// void ARTSPlayerController::OnTouchReleased()
// {
// 	bIsTouch = false;
// 	OnSetDestinationReleased();
// }
