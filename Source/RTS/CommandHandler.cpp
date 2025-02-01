// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandHandler.h"

#include "EnhancedInputComponent.h"
#include "InputAction.h"


// Sets default values for this component's properties
UCommandHandler::UCommandHandler()
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

