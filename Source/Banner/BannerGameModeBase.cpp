// Fill out your copyright notice in the Description page of Project Settings.


#include "BannerGameModeBase.h"
#include "SDropWidget.h"
#include "IImageWrapperModule.h"
#include "BaseBannerMainWidget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ImageUtils.h"

void ABannerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	TSharedRef<SDropWidget> dropWidget = SNew(SDropWidget);
	GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull)->GetGameViewport()->AddViewportWidgetContent(dropWidget);
	APlayerController* pc = UGameplayStatics::GetPlayerController(this, 0);
	UBaseBannerMainWidget* mainWidget = CreateWidget<UBaseBannerMainWidget>(pc, BannerWidgetClass, "BannerWidget");
	dropWidget->AddWidget(mainWidget);
}


#define RETURN_NULL_IF_FALSE(cond) if ((cond)==false){return nullptr;}

UTexture2D* ABannerGameModeBase::LoadTexture(FString fullPath)
{
	return FImageUtils::ImportFileAsTexture2D(fullPath);
}
