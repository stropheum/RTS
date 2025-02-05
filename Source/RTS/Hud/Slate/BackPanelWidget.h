#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class RTS_API SBackPanelWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SBackPanelWidget) {}
		
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);
};
