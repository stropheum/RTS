#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class RTS_API SMinimapWidget final : public SCompoundWidget
{
#pragma region Slate Arguments

public:
	SLATE_BEGIN_ARGS(SMinimapWidget) {}
		SLATE_ARGUMENT(FVector2f, ImageSize);
		SLATE_ARGUMENT(FVector4f, Padding);
	SLATE_END_ARGS()

#pragma endregion Slate Arguments
#pragma region Methods

	void Construct(const FArguments& InArgs);

#pragma endregion Methods
#pragma region Fields
private:
	TSharedPtr<FSlateBrush> Brush;
#pragma endregion Fields
};
