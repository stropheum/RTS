// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class RTS_API SUnitSelectionViewWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUnitSelectionViewWidget) {}
		SLATE_ARGUMENT(TArray<TSharedPtr<FSlateBrush>>, IconList);
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	TArray<TSharedPtr<FSlateBrush>> IconList;
	const int NumRows = 4;
	const int NumColumns = 16;
};
