#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class FRtsLevelEditorModule;

class RTSLEVELEDITOR_API SMirrorModeWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMirrorModeWidget) {}
		SLATE_ARGUMENT(TSharedPtr<FRtsLevelEditorModule>, Context)
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);

private:
	TSharedPtr<FRtsLevelEditorModule> Context;
};
