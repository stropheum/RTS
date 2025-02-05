// Fill out your copyright notice in the Description page of Project Settings.


#include "HudRootWidget.h"

#include "MinimapWidget.h"
#include "SlateOptMacros.h"
#include "UnitCommandViewWidget.h"
#include "UnitSelectionViewWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SHudRootWidget::Construct(const FArguments& InArgs)
{
	HudContextWeakPtr = InArgs._HudContext;
	const FVector4f Padding(32.0f, 32.0f, 32.0f, 16.0f);

	ChildSlot
	[
		SNew(SOverlay)
		+ SOverlay::Slot()
		.VAlign(VAlign_Bottom)
		[
			SNew(SHorizontalBox)

			// Spawn minimap left-justified
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Bottom)
			.AutoWidth()
			[
				SNew(SMinimapWidget)
				.ImageSize(InArgs._MinimapImageSize)
				.Padding(Padding)
			]

			// Spawn unit selection view in the center
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			.FillWidth(1.0f)
			[
				SNew(SUnitSelectionViewWidget)
				.SlotPadding(4.0f)
				.Padding(Padding)
			]

			// // Spawn Command panel right-justified
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.AutoWidth()
			[
				SNew(SUnitCommandViewWidget)
				.SlotPadding(4.0f)
				.Padding(Padding)
			]
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
