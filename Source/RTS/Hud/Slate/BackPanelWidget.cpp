#include "BackPanelWidget.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SBackPanelWidget::Construct(const FArguments& InArgs)
{
	UTexture2D* Texture = LoadObject<UTexture2D>(nullptr, TEXT("/Game/Art/hud_back_panel.hud_back_panel"));
	if (!Texture)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load texture. Aborting render back panel"));
		return;
	}

	const TSharedPtr<FSlateBrush> Brush = MakeShared<FSlateBrush>();
	Brush->SetResourceObject(Texture);
	
	ChildSlot
	[
		SNew(SBox)
		[
			SNew(SImage).Image(Brush.Get())
		]
	]; 
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
