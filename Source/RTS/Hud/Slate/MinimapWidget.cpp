#include "MinimapWidget.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMinimapWidget::Construct(const FArguments& InArgs)
{
	Brush = MakeShared<FSlateBrush>();
	Brush->TintColor = FColor::Blue;
	Brush->ImageSize = InArgs._ImageSize;
	
	ChildSlot
	[
		SNew(SBox)
		.Padding(InArgs._Padding)
		[
			SNew(SImage).Image(Brush.Get())
		]
	]; 
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
