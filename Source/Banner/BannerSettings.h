// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "BannerSettings.generated.h"

USTRUCT(BlueprintType)
struct BANNER_API FBannerIcon
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Icon;
};

USTRUCT(BlueprintType)
struct BANNER_API FBannerFont
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FSlateFontInfo FontInfo;
};


USTRUCT(BlueprintType)
struct BANNER_API FBannerConfigItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Tooltip = "ÆµµÀ"))
		FString Channel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FColor Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Show = true;
};

USTRUCT(BlueprintType)
struct BANNER_API FBannerTagConfigItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FColor Color;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Show = true;
};


UCLASS(config = BannerSettings, defaultconfig)
class BANNER_API UBannerSettings :public UDeveloperSettings
{
	GENERATED_BODY()
public:

public:
	/** Gets the settings container name for the settings, either Project or Editor */
	virtual FName GetContainerName() const override { return TEXT("Project"); }
	/** Gets the category for the settings, some high level grouping like, Editor, Engine, Game...etc. */
	virtual FName GetCategoryName() const override { return TEXT("Banner"); }
	/** The unique name for your section of settings, uses the class's FName. */
	virtual FName GetSectionName() const override { return TEXT("Banner"); }
public:
	UBannerSettings();
public:
	UFUNCTION(BlueprintPure)
		static UBannerSettings* BannerSettings();

	UFUNCTION(BlueprintPure)
		bool FindBanner(FString id, FBannerConfigItem& ResultItem)const;
	UFUNCTION( BlueprintPure)
		bool FindIcon(FString id, FBannerIcon& ResultIcon)const;
	UFUNCTION( BlueprintPure)
		bool FindFont(FString id, FBannerFont& ResultFont)const;
	UFUNCTION(BlueprintPure)
		bool FindBannerTag(FString id, FBannerTagConfigItem& ResultItem)const;

	UFUNCTION(BlueprintPure)
		FString DefaultBannerId()const;
	UFUNCTION(BlueprintPure)
		FString DefaultIconId()const;
	UFUNCTION(BlueprintPure)
		FString DefaultFontId()const;
	UFUNCTION(BlueprintPure)
		FString DefaultBannerTagId()const;
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
		TArray<FBannerIcon> Icons;
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
		TArray<FBannerFont> Fonts;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
		TArray<FBannerConfigItem> Items;

	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite)
		TArray<FBannerTagConfigItem> Tags;
private:
};