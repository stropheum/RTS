// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandHandler.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"


// Sets default values for this component's properties
UCommandHandler::UCommandHandler():
DefaultMappingContext(nullptr),
IssueActiveCommandAction(nullptr),
IssueMoveCommandAction(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UCommandHandler::BeginPlay()
{
	Super::BeginPlay();
	BindInputActions();
}


void UCommandHandler::BindInputActions()
{
	// Add Input Mapping Context
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

	EnhancedInputComponent->BindAction(IssueActiveCommandAction, ETriggerEvent::Triggered, this, &ThisClass::HandleIssueActiveCommand);
	EnhancedInputComponent->BindAction(IssueMoveCommandAction, ETriggerEvent::Triggered, this, &ThisClass::HandleIssueMoveCommand);

	// const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	// if (!LocalPlayer)
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("'%s' LocalPlayer == NULL"), *GetNameSafe(this));
	// 	return;
	// }
	//
	// UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	// if (!InputSubsystem)
	// {
	// 	InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
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

void UCommandHandler::HandleIssueActiveCommand()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("HandleIssueActiveCommand"));
}

void UCommandHandler::HandleIssueMoveCommand()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("HandleIssueMoveCommand"));
}

// Called every frame
void UCommandHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

