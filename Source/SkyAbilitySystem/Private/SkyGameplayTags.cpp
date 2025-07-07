// Copyright Skyward Studios, Inc. All Rights Reserved.

#include "SkyGameplayTags.h"

#include "GameplayTagsManager.h"

FSkyGameplayTags FSkyGameplayTags::GameplayTags;

void FSkyGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(GameplayTagsManager);
}

void FSkyGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	// AddTag(Tag_Name, "Tag.Name");
}

void FSkyGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}
