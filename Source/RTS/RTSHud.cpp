#include "RTSHud.h"
#include "SelectableUnitInterface.h"

ARTSHud::ARTSHud():
PendingSelectedActors(TArray<AActor*>()), ActiveSelectedActors(TArray<AActor*>()),
MouseStartPosition(), MouseCurrentPosition(), IsSelecting(false)
{}

FString ARTSHud::PassiveSelectionToString()
{
	FString PendingLog = "PENDING:\n";
	for (const auto Actor : PendingSelectedActors)
	{
		PendingLog += Actor->GetName() + "\n";
	}
	return PendingLog;
}

FString ARTSHud::ActiveSelectionToString()
{
	FString ActiveLog = "Active:\n";
	for (const auto Actor : ActiveSelectedActors)
	{
		ActiveLog += Actor->GetName() + "\n";
	}
	return ActiveLog;
}

void ARTSHud::HandleMarqueeSelectionPressed()
{
	IsSelecting = true;
}

void ARTSHud::HandleMarqueeSelectionReleased()
{
	IsSelecting = false;
	// Wipe active selection
	for (AActor* Actor : ActiveSelectedActors)
	{
		if (Actor->Implements<USelectableUnitInterface>() && !PendingSelectedActors.Contains(Actor))
		{
			ISelectableUnitInterface::Execute_SetSelectionState(Actor, ESelectionState::NotSelected);
		}
	}
	
	ActiveSelectedActors = PendingSelectedActors; // Migrate pending selection to Active
	
	// Select new active Selection
	for (AActor* Actor : ActiveSelectedActors)
	{
		if (Actor->Implements<USelectableUnitInterface>())
		{
			ISelectableUnitInterface::Execute_SetSelectionState(Actor, ESelectionState::Selected);
		}
		
	}
}

void ARTSHud::RenderSelectionBox(const FLinearColor RectColor)
{
	if (!IsSelecting) { return; }
	const FVector2D Difference = MouseCurrentPosition - MouseStartPosition;
	DrawRect(RectColor, MouseStartPosition.X, MouseStartPosition.Y, Difference.X, Difference.Y);
}

void ARTSHud::UpdateSelectionGroup(UClass* ClassFilter)
{
	constexpr bool IncludeNonCollidingComponent = false;
	constexpr bool ActorMustBeFullyEnclosed = false;
	
	TArray<AActor*> NewPendingSelection;
	GetActorsInSelectionRectangle(MouseStartPosition, MouseCurrentPosition, NewPendingSelection, IncludeNonCollidingComponent, ActorMustBeFullyEnclosed);

	TArray<AActor*> FilteredSelection;
	for (AActor* Actor : NewPendingSelection)
	{
		if (Actor->IsA(ClassFilter) && Actor->Implements<USelectableUnitInterface>())
		{
			ISelectableUnitInterface::Execute_SetSelectionState(Actor, ESelectionState::Pending);
			FilteredSelection.Add(Actor);
		}
	}
	
	for (AActor* Actor : PendingSelectedActors)
	{
		if (!FilteredSelection.Contains(Actor))
		{
			if (Actor->Implements<USelectableUnitInterface>() && !ActiveSelectedActors.Contains(Actor))
			{
				ISelectableUnitInterface::Execute_SetSelectionState(Actor, ESelectionState::NotSelected);
			}
		}
	}

	PendingSelectedActors = FilteredSelection;
}
