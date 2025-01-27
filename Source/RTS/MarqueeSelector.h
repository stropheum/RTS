// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MarqueeSelector.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMarqueeSelector : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_API IMarqueeSelector
{
	GENERATED_BODY()
	
public:
	void MarqueePressed();
	void MarqueeHeld();
	void MarqueeReleased();
	void SelectUnit();
	void DeselectUnit();
};
