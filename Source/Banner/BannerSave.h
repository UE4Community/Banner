// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "BannerSave.generated.h"

UENUM(BlueprintType)
enum class EBannerLayout :uint8
{
	Fullscreen UMETA(DisplayName="全屏"),
	Up UMETA(DisplayName = "上顶")
};

UCLASS(Blueprintable, BlueprintType)
class BANNER_API UBannerSave : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SelectedFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SelectedIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SelectedBanner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SelectedTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsExclusive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EBannerLayout Selectedlayout;

	UFUNCTION(BlueprintCallable,BlueprintPure)
		static TArray<FString> GetBannerLayoutDisplayNames();
public:
	void Reset();
};
