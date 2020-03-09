// Fill out your copyright notice in the Description page of Project Settings.

#include "BannerSave.h"
#include "BannerSettings.h"

void UBannerSave::Reset()
{
	SelectedBanner = UBannerSettings::BannerSettings()->DefaultBannerId();
	SelectedIcon = UBannerSettings::BannerSettings()->DefaultIconId();
	SelectedFont = UBannerSettings::BannerSettings()->DefaultFontId();

}
