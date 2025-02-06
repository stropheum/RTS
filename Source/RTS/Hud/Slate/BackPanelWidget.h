#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class RTS_API SBackPanelWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBackPanelWidget) {}
		SLATE_DEFAULT_SLOT(FArguments, Content)
		SLATE_ARGUMENT(FVector2f, ImageSize)
		SLATE_ARGUMENT(FVector4f, Padding)
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);

private:
	TSharedPtr<FSlateBrush> Brush;
};
