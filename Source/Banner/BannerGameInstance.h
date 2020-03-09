// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "BannerSettings.h"
#include "BannerGameInstance.generated.h"

class UBannerSave;

UCLASS(Blueprintable)
class BANNER_API UBannerGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init()override;
	virtual void Shutdown()override;

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
		static UBannerGameInstance* BannerGameInstance(const UObject* WorldContextobject);

	UFUNCTION(BlueprintCallable)
	void SaveGame();
public:
	UFUNCTION(BlueprintPure)
		FBannerConfigItem GetSelectedBanner()const;
	UFUNCTION(BlueprintPure)
		FBannerIcon GetSelectedIcon()const;
	UFUNCTION(BlueprintPure)
		FBannerFont GetSelectedFont()const;
public:
	UPROPERTY(BlueprintReadOnly)
		UBannerSave* Save;
};
