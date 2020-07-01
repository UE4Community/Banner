// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "BaseBannerMainWidget.generated.h"

UCLASS(Blueprintable, BlueprintType, Abstract,Category = "Banner")
class BANNER_API UBaseBannerMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
protected:
	virtual void NativePreConstruct()override;
	virtual void NativeConstruct()override;

public:
	bool HasFile()const { return !mDropFileName.IsEmpty(); }
	void DropFile(FString file);

	UFUNCTION(BlueprintImplementableEvent)
	void OnMoveImage(FVector2D delta);

	UFUNCTION(BlueprintImplementableEvent)
		void OnExportImage();

	UFUNCTION(BlueprintCallable)
		FString RenderWidgetToFile(UUserWidget* widget,FString title,FString channel,bool isExclusive=false);

	UFUNCTION(BlueprintImplementableEvent)
		void OnDropImage(UTexture2D* texture);

	UFUNCTION(BlueprintImplementableEvent)
		void OnDropVideo(const FString& file);

protected:
	FString mDropFileName;
};
