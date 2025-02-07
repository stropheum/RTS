// Fill out your copyright notice in the Description page of Project Settings.


#include "RtsLevelEditor/Public/MirrorModeWidget.h"

#include "SlateOptMacros.h"
#include "InputCoreTypes.h"
#include "Framework/Application/SlateApplication.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMirrorModeWidget::Construct(const FArguments& InArgs)
{
	Context = InArgs._Context;
	MirrorModeOptions.Add(MakeShared<FString>("None"));
	MirrorModeOptions.Add(MakeShared<FString>("2-Way"));
	MirrorModeOptions.Add(MakeShared<FString>("4-Way"));

	ComboBox = SNew(SComboBox<TSharedPtr<FString>>)
		.OptionsSource(&MirrorModeOptions)
		.OnGenerateWidget(this, &SMirrorModeWidget::GenerateButtonWidget)
		.OnSelectionChanged(this, &SMirrorModeWidget::OnSelectionChanged)
		[
			SNew(STextBlock)
			.Text_Lambda([this]() -> FText
			{
				return FText::FromString(ActiveSelection.IsValid() ? *ActiveSelection : TEXT("None"));
			})
		];

	ChildSlot
	[
		SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.MinWidth(100.0f)
		.Padding(16.0f)
		[
			SNew(STextBlock)
			.Text(FText::FromString("Mirror Mode: "))
		]
		
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Left)
		.MinWidth(100.0f)
		.Padding(16.0f)
		.AutoWidth()
		[
			ComboBox.ToSharedRef()
		]
	];
}

TSharedRef<SWidget> SMirrorModeWidget::GenerateButtonWidget(TSharedPtr<FString> Item)
{
	return SNew(SButton)
		.Text(FText::FromString(*Item))
		.OnClicked(this, &SMirrorModeWidget::OnButtonClicked, Item);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
// ReSharper disable once CppPassValueParameterByConstReference
// ReSharper disable once CppMemberFunctionMayBeConst
FReply SMirrorModeWidget::OnButtonClicked(TSharedPtr<FString> NewSelection)
{
	ComboBox->SetSelectedItem(NewSelection);
	UE_LOG(LogTemp, Warning, TEXT("Button clicked: %s"), **NewSelection);
	return FReply::Handled();
}

// ReSharper disable once CppPassValueParameterByConstReference
void SMirrorModeWidget::OnSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
{
	if (NewSelection.IsValid())
	{
		ActiveSelection = NewSelection;
		UE_LOG(LogTemp, Warning, TEXT("Selected: %s"), **NewSelection);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
