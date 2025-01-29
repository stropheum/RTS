// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SelectableUnitInterface.generated.h"

UINTERFACE()
class USelectableUnitInterface : public UInterface
{
	GENERATED_BODY()
};

class RTS_API ISelectableUnitInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ISelectableUnit")
	void MarqueePressed();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ISelectableUnit")
	void MarqueeHeld();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ISelectableUnit")
	void MarqueeReleased();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ISelectableUnit")
	void SelectUnit();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ISelectableUnit")
	void DeselectUnit();
};
