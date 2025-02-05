// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitCommandViewWidget.h"

#include "ImageUtils.h"
#include "SlateOptMacros.h"
#include "Widgets/Layout/SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SUnitCommandViewWidget::Construct(const FArguments& InArgs)
{
	IconList = InArgs._IconList;
	if (IconList.IsEmpty())
	{
		PopulateDefaultIconList();
	}
	
	const TSharedRef<SUniformGridPanel> GridPanel = GenerateGridPanel(InArgs._SlotPadding);
	
	ChildSlot[GridPanel]
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Bottom)
	.Padding(InArgs._Padding);
}

TSharedRef<SUniformGridPanel> SUnitCommandViewWidget::GenerateGridPanel(const float SlotPadding) const
{
	const TSharedRef<SUniformGridPanel> GridPanel = SNew(SUniformGridPanel)
			.SlotPadding(SlotPadding);

	for (int i = 0; i < IconList.Num(); i++)
	{
		const int Row = i / NumColumns;
		const int Column = i % NumColumns;

		if (Row < NumRows)
		{
			IconList[i].Get()->ImageSize = FVector2D(64.0f, 64.0f);
			GridPanel->AddSlot(Column, Row)
			[
				SNew(SImage).Image(IconList[i].Get())
			];
		}
	}

	return GridPanel;
}

void SUnitCommandViewWidget::PopulateDefaultIconList()
{
	const FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir() + TEXT("Art/unit_selection_frame.png"));
	if (UTexture2D* Texture = FImageUtils::ImportFileAsTexture2D(FilePath))
	{
		Brush = MakeShareable(new FSlateBrush);
		Brush->SetResourceObject(Texture);
			
		for (int i = 0; i < 32; i++)
		{
			IconList.Add(Brush);
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
