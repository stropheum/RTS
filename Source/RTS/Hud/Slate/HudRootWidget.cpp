// Fill out your copyright notice in the Description page of Project Settings.


#include "HudRootWidget.h"

#include "BackPanelWidget.h"
#include "MinimapWidget.h"
#include "SlateOptMacros.h"
#include "UnitCommandViewWidget.h"
#include "UnitSelectionViewWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SHudRootWidget::Construct(const FArguments& InArgs)
{
	HudContextWeakPtr = InArgs._HudContext;
	constexpr float BorderThickness = 20.0f;
	
	ChildSlot
	[
		SNew(SBackPanelWidget)
		[
			SNew(SHorizontalBox)

			// Minimap on the left
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Bottom)
			.AutoWidth()
			.Padding(BorderThickness + 16.0f, 0.0f, 0.0f, BorderThickness + 8.0f)
			[
				SNew(SMinimapWidget)
				.ImageSize(InArgs._MinimapImageSize)
			]

			// Unit Selection View in the center
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			.FillWidth(1.0f)
			.Padding(0.0f, 0.0f, 0.0f, BorderThickness)
			[
				SNew(SUnitSelectionViewWidget)
				.SlotPadding(4.0f)
			]

			// Command Panel on the right
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			.AutoWidth()
			.Padding(0.0f, 0.f, BorderThickness + 8.0f, BorderThickness)
			[
				SNew(SUnitCommandViewWidget)
				.SlotPadding(4.0f)
			]
		]
	];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
