// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBannerMainWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "BannerGameModeBase.h"

#include "Engine/TextureRenderTarget2D.h"
#include "Slate/SceneViewport.h"
#include "Slate/WidgetRenderer.h"
#include "Kismet/KismetRenderingLibrary.h"

void UBaseBannerMainWidget::NativePreConstruct()
{
	UUserWidget::NativePreConstruct();
}

void UBaseBannerMainWidget::NativeConstruct()
{
	UUserWidget::NativeConstruct();
}

void UBaseBannerMainWidget::DropFile(FString file)
{
	FString ext = FPaths::GetExtension(file).ToLower();
	if (ext == "png" || ext == "jpg" || ext == "jpeg")
	{
		UTexture2D* texture = ABannerGameModeBase::LoadTexture(file);
		if (texture != nullptr)
		{
			OnDropImage(texture);
			mDropFileName = file;
		}
	}
	else
	{
		OnDropVideo(file);
		mDropFileName = file;
	}
}


FString UBaseBannerMainWidget::RenderWidgetToFile(UUserWidget* widget, FString title, FString channel, bool isExclusive)
{
	if (mDropFileName.IsEmpty())
	{
		return "";
	}

	FString resultFilePath = FPaths::GetPath(mDropFileName);
	FString resultFileName = FPaths::GetBaseFilename(mDropFileName);

	if (isExclusive)
	{
		IFileManager& fileManager = IFileManager::Get();
		TArray<FString> outFiles;
		fileManager.FindFiles(outFiles, *resultFilePath, TEXT("*.jpg"));
		for (FString file : outFiles)
		{
			if(file.Find(resultFileName,ESearchCase::CaseSensitive)==0)
			{
				FString fileFullPath= FPaths::Combine(resultFilePath, file);
				fileManager.Delete(*fileFullPath);
			}
		}
	}


	UTextureRenderTarget2D* widgetRT = NewObject<UTextureRenderTarget2D>(this);
	bool bIsSRGB = false;
	EPixelFormat PixelFormat = PF_B8G8R8A8;
	FIntPoint ScreenshotSize(2880, 1800);	//4K 3840*2160 1440*900
	

	widgetRT->ClearColor = FLinearColor::Black;
	widgetRT->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RG8;
	widgetRT->InitCustomFormat(ScreenshotSize.X, ScreenshotSize.Y, PixelFormat, !bIsSRGB);

	FWidgetRenderer* WidgetRenderer = new FWidgetRenderer(true, false);
	check(WidgetRenderer);
	WidgetRenderer->DrawWidget(widgetRT, widget->TakeWidget(), ScreenshotSize, 0.f);
	FlushRenderingCommands();
	BeginCleanup(WidgetRenderer);


	resultFileName += "_" + title + +"_" + channel + ".jpg";
	resultFileName.ReplaceInline(TEXT("&"), TEXT("and"));

	UKismetRenderingLibrary::ExportRenderTarget(this, widgetRT, resultFilePath, resultFileName);

	return FPaths::Combine(resultFilePath, resultFileName);
}
