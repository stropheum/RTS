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

protected:
	TSharedRef<SWidget> GenerateButtonWidget(TSharedPtr<FString> NewSelection);
	FReply OnButtonClicked(TSharedPtr<FString> NewSelection);
	void OnSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo);

private:
	TSharedPtr<FRtsLevelEditorModule> Context;
	TSharedPtr<SComboBox<TSharedPtr<FString>>> ComboBox;
	TArray<TSharedPtr<FString>> MirrorModeOptions;
	TSharedPtr<FString> ActiveSelection;
};
