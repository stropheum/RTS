// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RtsInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class URtsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_API IRtsInterface
{
	GENERATED_BODY()
	
public:
	void MarqueePressed();
	void MarqueeHeld();
	void MarqueeReleased();
	void SelectUnit();
	void DeselectUnit();
};
