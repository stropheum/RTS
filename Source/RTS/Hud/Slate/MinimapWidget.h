#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class RTS_API SMinimapWidget final : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMinimapWidget) {}
		SLATE_ARGUMENT(FVector2f, ImageSize);
		SLATE_ARGUMENT(FVector4f, Padding);
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	
	TSharedPtr<FSlateBrush> Brush;
};