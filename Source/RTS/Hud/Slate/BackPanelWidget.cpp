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
	
	Brush = MakeShared<FSlateBrush>();
	Brush->SetResourceObject(Texture);
	Brush->SetImageSize(Texture->GetImportedSize());
	
    ChildSlot
    [
	    SNew(SOverlay)
	    + SOverlay::Slot()
	    .HAlign(HAlign_Fill)
	    .VAlign(VAlign_Fill)
	    [
	    	SNew(SBox)
			// .Padding(InArgs._Padding)
			[
				SNew(SImage)
				.Image(Brush.Get())
			]    
	    ]
	    + SOverlay::Slot()
	    .HAlign(HAlign_Fill)
    	.VAlign(VAlign_Fill)
    	[
    		InArgs._Content.Widget
    	]
    ]; 
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
