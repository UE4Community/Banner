// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "IImageWrapper.h"
#include "BannerGameModeBase.generated.h"


class UBaseBannerMainWidget;

UCLASS()
class BANNER_API ABannerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay();
	UFUNCTION(BlueprintCallable, Category = "Banner")
		static UTexture2D* LoadTexture(FString fullPath);
public:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UBaseBannerMainWidget> BannerWidgetClass;
};
