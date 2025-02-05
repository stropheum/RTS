#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SUniformGridPanel;

class RTS_API SUnitCommandViewWidget final : public SCompoundWidget
{

public:
	SLATE_BEGIN_ARGS(SUnitCommandViewWidget) {}
		SLATE_ARGUMENT(TWeakObjectPtr<class AHUD>, Owner);
		SLATE_ARGUMENT(TArray<TSharedPtr<FSlateBrush>>, IconList);
		SLATE_ARGUMENT(float, SlotPadding);
		SLATE_ARGUMENT(FVector4f, Padding);
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
	TSharedRef<SUniformGridPanel> GenerateGridPanel(const float SlotPadding) const;
	
	void PopulateDefaultIconList();

private:
	TWeakPtr<AHUD> HudContextWeakPtr;
	TArray<TSharedPtr<FSlateBrush>> IconList;
    const int NumRows = 4;
    const int NumColumns = 3;
};
