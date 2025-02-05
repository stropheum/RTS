#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class RTS_API SUnitSelectionViewWidget : public SCompoundWidget
{
#pragma region Slate Arguments
	
public:
	SLATE_BEGIN_ARGS(SUnitSelectionViewWidget) {}
		SLATE_ARGUMENT(TArray<TSharedPtr<FSlateBrush>>, IconList);
		SLATE_ARGUMENT(float, SlotPadding);
		SLATE_ARGUMENT(FVector4f, Padding);
	SLATE_END_ARGS()
	
#pragma endregion Slate Arguments
#pragma region Methods

	void Construct(const FArguments& InArgs);


private:
	void PopulateDefaultIconList();
	TSharedRef<class SUniformGridPanel> GenerateGridPanel(float SlotPadding) const;

#pragma endregion Methods
#pragma region Fields
	
private:
	TArray<TSharedPtr<FSlateBrush>> IconList;
	const int NumRows = 4;
	const int NumColumns = 8;
	
#pragma endregion Fields
};
