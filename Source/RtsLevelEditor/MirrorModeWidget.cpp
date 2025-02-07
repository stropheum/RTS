// Fill out your copyright notice in the Description page of Project Settings.


#include "MirrorModeWidget.h"

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
	
	ChildSlot
		[
			SNew(SComboBox<TSharedPtr<FString>>)
			.OptionsSource(&MirrorModeOptions)
			.OnGenerateWidget(this, &SMirrorModeWidget::GenerateButtonWidget)
			.OnSelectionChanged(this, &SMirrorModeWidget::OnSelectionChanged)
			[
				// TODO: change text according to selected item
				SNew(STextBlock)
				.Text(FText::FromString("Mirror Mode"))
			]
		];
	
}

TSharedRef<SWidget> SMirrorModeWidget::GenerateButtonWidget(TSharedPtr<FString> Item)
{
	return SNew(SButton)
		.Text(FText::FromString(*Item))
		.OnClicked(this, &SMirrorModeWidget::OnButtonClicked, Item);
}

FReply SMirrorModeWidget::OnButtonClicked(TSharedPtr<FString> Item)
{
	UE_LOG(LogTemp, Warning, TEXT("Button clicked: %s"), **Item);
	return FReply::Handled();
}

void SMirrorModeWidget::OnSelectionChanged(TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo)
{
	if (NewSelection.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Selected: %s"), **NewSelection);
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
