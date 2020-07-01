// Fill out your copyright notice in the Description page of Project Settings.

#include "BannerGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "BannerSave.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "BannerSettings.h"


void UBannerGameInstance::Init()
{
	Super::Init();

	const FString slotName = TEXT("Banner");
	Save = Cast<UBannerSave>(UGameplayStatics::LoadGameFromSlot(slotName, 0));
	if (Save == nullptr)
	{
		Save = Cast<UBannerSave>(UGameplayStatics::CreateSaveGameObject(UBannerSave::StaticClass()));
		Save->Reset();
	}
}

void UBannerGameInstance::Shutdown()
{
	Super::Shutdown();
	SaveGame();
}

UBannerGameInstance* UBannerGameInstance::BannerGameInstance(const UObject* WorldContextobject)
{
	return Cast<UBannerGameInstance>(UGameplayStatics::GetGameInstance(WorldContextobject));
}

void UBannerGameInstance::SaveGame()
{
	const FString slotName = TEXT("Banner");
	UGameplayStatics::SaveGameToSlot(Save, slotName, 0);
}

FBannerConfigItem UBannerGameInstance::GetSelectedBanner() const
{
	FBannerConfigItem item;
	UBannerSettings::BannerSettings()->FindBanner(Save->SelectedBanner, item);
	return item;
}

FBannerIcon UBannerGameInstance::GetSelectedIcon() const
{
	FBannerIcon item;
	UBannerSettings::BannerSettings()->FindIcon(Save->SelectedIcon, item);
	return item;
}

FBannerFont UBannerGameInstance::GetSelectedFont() const
{
	FBannerFont item;
	UBannerSettings::BannerSettings()->FindFont(Save->SelectedFont, item);
	return item;
}

FBannerTagConfigItem UBannerGameInstance::GetSelectedTag() const
{
	FBannerTagConfigItem item;
	UBannerSettings::BannerSettings()->FindBannerTag(Save->SelectedTag, item);
	return item;
}
