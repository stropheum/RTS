// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTSHud.generated.h"

class SHudRootWidget;
class SUnitSelectionViewWidget;
class FClassViewerFilter;
/**
 * 
 */
UCLASS(Blueprintable)
class RTS_API ARTSHud : public AHUD
{
	GENERATED_BODY()

#pragma region Functions

public:
	ARTSHud();

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "RTS HUD")
	FString PassiveSelectionToString();

	UFUNCTION(BlueprintCallable, Category = "RTS HUD")
	FString ActiveSelectionToString();
	
	TArray<AActor*> GetSelectedUnits();
	
protected:

	UFUNCTION(BlueprintCallable, category = "RTS HUD")
	void HandleMarqueeSelectionPressed();
	
	UFUNCTION(BlueprintCallable, category = "RTS HUD")
	void HandleMarqueeSelectionReleased();

	UFUNCTION(BlueprintCallable, Category = "RTS HUD")
	void RenderSelectionBox(FLinearColor RectColor);
	
	UFUNCTION(BlueprintCallable, Category = "RTS HUD")
	void UpdateSelectionGroup(UClass* ClassFilter);

private:
	void SlateInitUnitSelectionView();
	
#pragma endregion

#pragma region Variables

public:

protected:

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS HUD", meta = (AllowPrivateAccess = "true"))
	UTexture2D* DefaultSelectionViewTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS HUD")
	float UnitSelectionViewSlotPadding;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS HUD")
	FVector4f UnitSelectionViewBottomScreenPadding;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RTS HUD")
	FVector2f MinimapSize;

private:
	
	TSharedPtr<SHudRootWidget> UnitSelectionViewSharedPtr;
	TSharedPtr<FSlateBrush> BrushSharedPtr;
	
#pragma endregion
};
