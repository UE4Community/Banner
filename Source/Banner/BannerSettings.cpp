// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.


#include "BannerSettings.h"
#include "Misc/Paths.h"
#include "Kismet/KismetMathLibrary.h"

UBannerSettings::UBannerSettings()
{
	
}

UBannerSettings* UBannerSettings::BannerSettings()
{
	return GetMutableDefault<UBannerSettings>();
}

bool UBannerSettings::FindBanner(FString id, FBannerConfigItem& ResultItem) const
{
	for (const FBannerConfigItem& item : Items)
	{
		if (item.Id == id)
		{
			ResultItem = item;
			return true;
		}
	}
	return false;
}

bool UBannerSettings::FindIcon(FString id, FBannerIcon& ResultIcon) const
{
	for (const FBannerIcon& item : Icons)
	{
		if (item.Id == id)
		{
			ResultIcon = item;
			return true;
		}
	}
	return false;
}

bool UBannerSettings::FindFont(FString id, FBannerFont& ResultFont) const
{
	for (const FBannerFont& item : Fonts)
	{
		if (item.Id == id)
		{
			ResultFont = item;
			return true;
		}
	}
	return false;
}

bool UBannerSettings::FindBannerTag(FString id, FBannerTagConfigItem& ResultItem) const
{
	for (const FBannerTagConfigItem& item : Tags)
	{
		if (item.Id == id)
		{
			ResultItem = item;
			return true;
		}
	}
	return false;
}

FString UBannerSettings::DefaultBannerId() const
{
	return Items.Top().Id;
}

FString UBannerSettings::DefaultIconId() const
{
	return Icons.Top().Id;
}

FString UBannerSettings::DefaultFontId() const
{
	return Fonts.Top().Id;

}

FString UBannerSettings::DefaultBannerTagId() const
{
	return Tags.Top().Id;
}

