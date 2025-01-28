// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MarqueeSelectorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UMarqueeSelectorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RTS_API IMarqueeSelectorInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IMarqueeSelector")
	void MarqueePressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IMarqueeSelector")
	void MarqueeHeld();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IMarqueeSelector")
	void MarqueeReleased();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IMarqueeSelector")
	void SelectUnit();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "IMarqueeSelector")
	void DeselectUnit();
};
