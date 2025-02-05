#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class ARTSHud;

class RTS_API SHudRootWidget : public SCompoundWidget
{
#pragma region Slate Arguments

public:
	SLATE_BEGIN_ARGS(SHudRootWidget) {}
		SLATE_ARGUMENT(TWeakPtr<AHUD>, HudContext)
		SLATE_ARGUMENT(FVector2f, MinimapImageSize)
	SLATE_END_ARGS()

#pragma endregion Slate Arguments
#pragma region Methods

	void Construct(const FArguments& InArgs);

#pragma endregion Methods
#pragma region Fields

private:
	TWeakPtr<AHUD> HudContextWeakPtr;

#pragma endregion Fields
};

