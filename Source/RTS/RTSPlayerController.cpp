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
	int32 ScreenWidth = 0, ScreenHeight = 0;
	GetViewportSize(ScreenWidth, ScreenHeight);
	SetMouseLocation(ScreenWidth / 2.0f, ScreenHeight / 2.0f);
	CommandHandler = Cast<UCommandHandler>(AddComponentByClass(UCommandHandler::StaticClass(), false, FTransform::Identity, true));
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	checkf(EnhancedInputComponent, TEXT("EnhancedInputComponent != NULL"));
}

void ARTSPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	const APlayerController* PlayerController = Cast<APlayerController>(GetOwner());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' PlayerController == NULL"), *GetNameSafe(this));
		return;
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	if (!EnhancedInputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' EnhancedInputComponent == NULL"), *GetNameSafe(this));
		return;
	}
	
	EnhancedInputComponent->BindAction(IssueActiveCommandAction, ETriggerEvent::Triggered, CommandHandler, &UCommandHandler::HandleIssueActiveCommand);
	EnhancedInputComponent->BindAction(IssueMoveCommandAction, ETriggerEvent::Triggered, CommandHandler, &UCommandHandler::HandleIssueMoveCommand);
}
