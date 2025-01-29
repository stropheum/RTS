// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHud.generated.h"

class FClassViewerFilter;
/**
 * 
 */
UCLASS(Blueprintable)
class RTS_API ARTSHud : public AHUD
{
	GENERATED_BODY()
	
public:
	ARTSHud();
	
	UFUNCTION(BlueprintCallable, Category = "RTS HUD")
	FString PassiveSelectionToString();

	UFUNCTION(BlueprintCallable, Category = "RTS HUD")
	FString ActiveSelectionToString();

protected:

	UFUNCTION(BlueprintCallable, category = "RTS HUD")
	void HandleMarqueeSelectionPressed();
	
	UFUNCTION(BlueprintCallable, category = "RTS HUD")
	void HandleMarqueeSelectionReleased();

	UFUNCTION(BlueprintCallable, Category = "RTS HUD")
	void RenderSelectionBox(FLinearColor RectColor);
	
	UFUNCTION(BlueprintCallable, Category = "RTS HUD")
	void UpdateSelectionGroup(UClass* ClassFilter);

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
