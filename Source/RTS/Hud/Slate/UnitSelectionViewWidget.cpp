#include "UnitSelectionViewWidget.h"

#include "ImageUtils.h"
#include "SlateOptMacros.h"
#include "Widgets/Layout/SUniformGridPanel.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SUnitSelectionViewWidget::Construct(const FArguments& InArgs)
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

void SUnitSelectionViewWidget::PopulateDefaultIconList()
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

TSharedRef<SUniformGridPanel> SUnitSelectionViewWidget::GenerateGridPanel(const float SlotPadding) const
{
	const TSharedRef<SUniformGridPanel> GridPanel = SNew(SUniformGridPanel)
			.SlotPadding(SlotPadding);

	for (int i = 0; i < IconList.Num(); i++)
	{
		const int Row = i / NumColumns;
		const int Column = i % NumColumns;

		if (Row < NumRows)
		{
			IconList[i].Get()->ImageSize = FVector2f(48.0f, 48.0f);
			GridPanel->AddSlot(Column, Row)
			[
				SNew(SImage).Image(IconList[i].Get())
			];
		}
	}

	return GridPanel;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
