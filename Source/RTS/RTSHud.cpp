// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHud.h"

ARTSHud::ARTSHud():
PendingSelectedActors(TArray<AActor*>()), ActiveSelectedActors(TArray<AActor*>()),
MouseStartPosition(), MouseCurrentPosition(), IsSelecting(false)
{}

void ARTSHud::LogPendingSelection(const FString Context)
{
	FString log = Context;
	for (const auto Actor : PendingSelectedActors)
	{
		log += Actor->GetName();
		log += ", ";
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *log);
}

void ARTSHud::LogActiveSelection(const FString Context)
{
	FString log = Context;
	for (const auto Actor : ActiveSelectedActors)
	{
		log += Actor->GetName();
		log += ", ";
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *log);
}

void ARTSHud::RenderSelectionBox(const FLinearColor RectColor)
{
	if (!IsSelecting) { return; }
	FVector2D Difference = MouseCurrentPosition - MouseStartPosition;
	DrawRect(RectColor, MouseStartPosition.X, MouseStartPosition.Y, Difference.X, Difference.Y);
}

void ARTSHud::UpdateSelectionGroup()
{
	for (const AActor* Actor : PendingSelectedActors)
	{
		
	}
}
