// Fill out your copyright notice in the Description page of Project Settings.


#include "UnitSelectionViewWidget.h"

#include "SlateOptMacros.h"
#include "Widgets/Layout/SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SUnitSelectionViewWidget::Construct(const FArguments& InArgs)
{
	IconList = InArgs._IconList;
	const TSharedRef<SUniformGridPanel> GridPanel = SNew(SUniformGridPanel);

	for (int i = 0; i < IconList.Num(); i++)
	{
		const int Row = i / NumColumns;
		const int Column = i % NumColumns;

		if (Row < NumRows)
		{
			GridPanel->AddSlot(Column, Row)
			[
				SNew(SImage)
				.Image(IconList[i].Get())
			];
		}
	}
	
	ChildSlot
	[
		GridPanel
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
