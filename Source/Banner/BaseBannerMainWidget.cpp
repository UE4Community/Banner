// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseBannerMainWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "BannerGameModeBase.h"

#include "Engine/TextureRenderTarget2D.h"
#include "Slate/SceneViewport.h"
#include "Slate/WidgetRenderer.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Serialization/BufferArchive.h"
#include "IImageWrapperModule.h"

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
	widgetRT->RenderTargetFormat = ETextureRenderTargetFormat::RTF_RGBA8;
	widgetRT->InitCustomFormat(ScreenshotSize.X, ScreenshotSize.Y, PixelFormat, !bIsSRGB);

	FWidgetRenderer* WidgetRenderer = new FWidgetRenderer(true, false);
	check(WidgetRenderer);
	WidgetRenderer->DrawWidget(widgetRT, widget->TakeWidget(), ScreenshotSize, 0.f);
	FlushRenderingCommands();
	BeginCleanup(WidgetRenderer);


	resultFileName += "_" + title + +"_" + channel + ".jpg";
	resultFileName.ReplaceInline(TEXT("&"), TEXT("and"));

	FString TotalFileName = FPaths::Combine(resultFilePath, resultFileName);
	FText PathError;
	FPaths::ValidatePath(TotalFileName, &PathError);
	FArchive* Ar = IFileManager::Get().CreateFileWriter(*TotalFileName);
	if (Ar)
	{
		FBufferArchive Buffer;
		if (ExportRenderTarget2DAsJpeg(widgetRT, Buffer))
		{
			Ar->Serialize(const_cast<uint8*>(Buffer.GetData()), Buffer.Num());
		}
		delete Ar;
	}


	//UKismetRenderingLibrary::ExportRenderTarget(this, widgetRT, resultFilePath, resultFileName);	//can only png


	return FPaths::Combine(resultFilePath, resultFileName);
}


static bool GetRawData(UTextureRenderTarget2D* TexRT, TArray64<uint8>& RawData)
{
	FRenderTarget* RenderTarget = TexRT->GameThread_GetRenderTargetResource();
	EPixelFormat Format = TexRT->GetFormat();

	int32 ImageBytes = CalculateImageBytes(TexRT->SizeX, TexRT->SizeY, 0, Format);
	RawData.AddUninitialized(ImageBytes);
	bool bReadSuccess = false;
	switch (Format)
	{
	case PF_FloatRGBA:
	{
		TArray<FFloat16Color> FloatColors;
		bReadSuccess = RenderTarget->ReadFloat16Pixels(FloatColors);
		FMemory::Memcpy(RawData.GetData(), FloatColors.GetData(), ImageBytes);
	}
	break;
	case PF_B8G8R8A8:
		bReadSuccess = RenderTarget->ReadPixelsPtr((FColor*)RawData.GetData());
		break;
	}
	if (bReadSuccess == false)
	{
		RawData.Empty();
	}
	return bReadSuccess;
}

bool UBaseBannerMainWidget::ExportRenderTarget2DAsJpeg(UTextureRenderTarget2D* TexRT, FArchive& Ar)
{
	bool bSuccess = false;
	if (TexRT->GetFormat() == PF_B8G8R8A8)
	{
		check(TexRT != nullptr);
		FRenderTarget* RenderTarget = TexRT->GameThread_GetRenderTargetResource();
		FIntPoint Size = RenderTarget->GetSizeXY();

		TArray64<uint8> RawData;
		bSuccess = GetRawData(TexRT, RawData);

		IImageWrapperModule& ImageWrapperModule = FModuleManager::Get().LoadModuleChecked<IImageWrapperModule>(TEXT("ImageWrapper"));

		TSharedPtr<IImageWrapper> JPEGImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::JPEG);

		JPEGImageWrapper->SetRaw(RawData.GetData(), RawData.GetAllocatedSize(), Size.X, Size.Y, ERGBFormat::BGRA, 8);

		const TArray64<uint8>& PNGData = JPEGImageWrapper->GetCompressed(100);

		Ar.Serialize((void*)PNGData.GetData(), PNGData.GetAllocatedSize());
	}

	return bSuccess;
}