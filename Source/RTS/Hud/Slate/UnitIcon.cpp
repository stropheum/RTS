#include "UnitIcon.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SUnitIcon::Construct(const FArguments& InArgs)
{
	ImageSharedPtr = InArgs._Image;
	BaseImageSize = ImageSharedPtr->ImageSize;
	ChildSlot
	[
		SNew(SImage)
		.Image(ImageSharedPtr.Get())
	];
}

void SUnitIcon::OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	SCompoundWidget::OnMouseEnter(MyGeometry, MouseEvent);
	ImageSharedPtr->TintColor = FColor::Magenta;
}

void SUnitIcon::OnMouseLeave(const FPointerEvent& MouseEvent)
{
	SCompoundWidget::OnMouseLeave(MouseEvent);
	ImageSharedPtr->TintColor = IsActive ? FColor::Yellow : FColor::White;
}

FReply SUnitIcon::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	IsActive = !IsActive;
	ImageSharedPtr->TintColor = FColor::Yellow;
	return SCompoundWidget::OnMouseButtonDown(MyGeometry, MouseEvent);
}

FReply SUnitIcon::OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	
	return SCompoundWidget::OnMouseButtonUp(MyGeometry, MouseEvent);
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
