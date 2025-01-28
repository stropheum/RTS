// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSHud.h"

#include "ClassViewerFilter.h"
#include "MarqueeSelectorInterface.h"

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

void ARTSHud::UpdateSelectionGroup(UClass* ClassFilter)
{
	bool IncludeNonCollidingComponent = false;
	bool ActorMustBeFullyEnclosed = false;
	//const FVector2D& FirstPoint, const FVector2D& SecondPoint, TArray<ClassFilter*>& OutActors, bool bIncludeNonCollidingComponents = true, bool bActorMustBeFullyEnclosed = false
	
	TArray<AActor*> NewPendingSelection;
	GetActorsInSelectionRectangle(MouseStartPosition, MouseCurrentPosition, NewPendingSelection, IncludeNonCollidingComponent, ActorMustBeFullyEnclosed);
	
	for (AActor* Actor : PendingSelectedActors)
	{
		if (!Actor->IsA(ClassFilter)) { continue; }
		IMarqueeSelectorInterface* MarqueeSelectorActor = Cast<IMarqueeSelectorInterface>(Actor);
		if (MarqueeSelectorActor == nullptr) { continue; }
		if (!NewPendingSelection.Contains(Actor))
		{
			MarqueeSelectorActor->DeselectUnit();
		}
	}
	PendingSelectedActors = NewPendingSelection;
}
