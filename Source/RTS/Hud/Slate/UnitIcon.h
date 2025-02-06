#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class RTS_API SUnitIcon : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SUnitIcon) {}
		SLATE_ARGUMENT(TSharedPtr<FSlateBrush>, Image)
	SLATE_END_ARGS()
	
	void Construct(const FArguments& InArgs);

	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

	virtual FReply OnMouseButtonUp(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

private:
	TSharedPtr<FSlateBrush> ImageSharedPtr;
	FVector2f BaseImageSize = FVector2f::ZeroVector;
	bool IsActive = false;
};
