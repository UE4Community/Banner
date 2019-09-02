#include "SDropWidget.h"
#include "BaseBannerMainWidget.h"

SDropWidget::SDropWidget()
{

}

void SDropWidget::Construct(const FArguments& InArgs)
{
	
}

void SDropWidget::OnDragEnter(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	TSharedPtr<FExternalDragOperation> op = DragDropEvent.GetOperationAs<FExternalDragOperation>();
	const TArray<FString>& files = op->GetFiles();
	if (files.Num() > 0)
	{
		mWidget->DropFile(files[0]);
	}
}

void SDropWidget::OnDragLeave(const FDragDropEvent& DragDropEvent)
{

}

FReply SDropWidget::OnDragOver(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	if (mWidget->HasFile())
	{
		FVector2D delta = DragDropEvent.GetCursorDelta();
		mWidget->OnMoveImage(delta);

	}
	return FReply::Handled();
}

FReply SDropWidget::OnDrop(const FGeometry& MyGeometry, const FDragDropEvent& DragDropEvent)
{
	if (mWidget->HasFile())
	{
		mWidget->OnExportImage();
		return FReply::Handled();
	}
	else
	{
		TSharedPtr<FExternalDragOperation> op = DragDropEvent.GetOperationAs<FExternalDragOperation>();
		const TArray<FString>& files = op->GetFiles();
		if (files.Num() > 0)
		{
			mWidget->DropFile(files[0]);
		}
	}

	

	return FReply::Handled();
}


void SDropWidget::AddWidget(TWeakObjectPtr<UBaseBannerMainWidget> widget)
{
	mWidget = widget;
	ChildSlot[mWidget->TakeWidget()];

}
