#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class ARTSHud;

class RTS_API SHudRootWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SHudRootWidget) {}
		SLATE_ARGUMENT(TWeakPtr<AHUD>, HudContext)
		SLATE_ARGUMENT(FVector2f, MinimapImageSize)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	TWeakPtr<AHUD> HudContextWeakPtr;
};

