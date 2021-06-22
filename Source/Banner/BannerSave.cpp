// Fill out your copyright notice in the Description page of Project Settings.

#include "BannerSave.h"
#include "BannerSettings.h"


void UBannerSave::Reset()
{
	SelectedBanner = UBannerSettings::BannerSettings()->DefaultBannerId();
	SelectedIcon = UBannerSettings::BannerSettings()->DefaultIconId();
	SelectedFont = UBannerSettings::BannerSettings()->DefaultFontId();
	Selectedlayout=EBannerLayout::Fullscreen;
}

TArray<FString> UBannerSave::GetBannerLayoutDisplayNames()
{
	TArray<FString> result;

	result.Add(TEXT("全屏"));
	result.Add(TEXT("上顶"));

	/*UEnum* enumClass=StaticEnum<EBannerLayout>();
	for (int i=0;i< enumClass->NumEnums();++i)
	{
		result.Add(enumClass->GetDisplayNameTextByIndex(i));
	}*/

	return result;	
}
