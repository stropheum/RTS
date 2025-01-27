// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHud.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RTS_API ARTSHud : public AHUD
{
	GENERATED_BODY()
	
public:
	ARTSHud();
	
	float FooSum(float a, float b);

protected:
	UFUNCTION(BlueprintCallable, Category = "RTS HUD")
	void LogPendingSelection(FString Context);

	UFUNCTION(BlueprintCallable, Category = "RTS HUD")
	void LogActiveSelection(FString Context);

	UFUNCTION(BlueprintCallable, Category = "RTS HUD")
	void RenderSelectionBox(FLinearColor RectColor);
	
	UFUNCTION(BlueprintCallable, Category = "RTS HUD")
	void UpdateSelectionGroup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS HUD")
	TArray<AActor*> PendingSelectedActors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS HUD")
	TArray<AActor*> ActiveSelectedActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS HUD")
	FVector2D MouseStartPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS HUD")
	FVector2D MouseCurrentPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS HUD")
	bool IsSelecting;
};
