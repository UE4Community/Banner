// Fill out your copyright notice in the Description page of Project Settings.


#include "BannerGameModeBase.h"
#include "SDropWidget.h"
#include "IImageWrapperModule.h"
#include "BaseBannerMainWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ABannerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	FSlateApplication& slateApp = FSlateApplication::Get();
	TSharedRef<SDropWidget> widget = SNew(SDropWidget);
	GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull)->GetGameViewport()->AddViewportWidgetContent(widget);
	APlayerController* pc = UGameplayStatics::GetPlayerController(this, 0);
	UBaseBannerMainWidget* w = CreateWidget<UBaseBannerMainWidget>(pc, BannerWidgetClass, "BannerWidget");
	widget->AddWidget(w);
}


#define RETURN_NULL_IF_FALSE(cond) if ((cond)==false){return nullptr;}

UTexture2D* ABannerGameModeBase::LoadTexture(FString fullPath)
{
	TSharedPtr<IImageWrapper> outImageWrapper;
	return LoadTextureEx(fullPath, &outImageWrapper);
}

UTexture2D* ABannerGameModeBase::LoadTextureEx(FString fullPath, TSharedPtr<IImageWrapper>* outImageWrapper)
{
	RETURN_NULL_IF_FALSE(FPaths::FileExists(fullPath));

	FString extension = FPaths::GetExtension(fullPath, false);
	bool isPng = extension == TEXT("png");
	bool isExr = extension == TEXT("exr");
	EImageFormat imageFormat = isExr ? EImageFormat::EXR : (isPng ? EImageFormat::PNG : EImageFormat::JPEG);
	EPixelFormat pixelFormat = isExr ? PF_FloatRGBA : PF_B8G8R8A8;
	int bitDepth = isExr ? 16 : 8;

	TArray<uint8> RawFileData;
	UTexture2D* MyTexture = NULL;
	RETURN_NULL_IF_FALSE(FFileHelper::LoadFileToArray(RawFileData, *fullPath));
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(imageFormat);
	RETURN_NULL_IF_FALSE(ImageWrapper.IsValid());
	RETURN_NULL_IF_FALSE(ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()));

	const TArray<uint8>* UncompressedBGRA = NULL;
	RETURN_NULL_IF_FALSE(ImageWrapper->GetRaw(ERGBFormat::BGRA, bitDepth, UncompressedBGRA));

	// Create the UTexture for rendering
	UTexture2D* result = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), pixelFormat);

	// Fill in the source data from the file
	void* TextureData = result->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(TextureData, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
	result->PlatformData->Mips[0].BulkData.Unlock();

	// Update the rendering resource from data.
	result->UpdateResource();

	if (outImageWrapper != nullptr)
	{
		*outImageWrapper = ImageWrapper;
	}

	return result;

}