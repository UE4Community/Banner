#pragma once
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class UBaseBannerMainWidget;

class BANNER_API SDropWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SDropWidget) { }
	SLATE_END_ARGS()
public:
	SDropWidget();
	void Construct(const FArguments& InArgs);
	virtual void OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)override;
	virtual void OnDragLeave(const FDragDropEvent& DragDropEvent)override;
	virtual FReply OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)override;
	virtual FReply OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)override;
public:
	void AddWidget(TWeakObjectPtr<UBaseBannerMainWidget> widget);
protected:
	TWeakObjectPtr<UBaseBannerMainWidget> mWidget;
};
