// Copyright Skyward Studios, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "SkyGameplayTags.generated.h"

USTRUCT(BlueprintType, meta = (Categories="GameplayCue"), DisplayName="Gameplay Cue Tag")
struct FSkyGameplayCueTag : public FGameplayTag
{
	GENERATED_USTRUCT_BODY()
};

class UGameplayTagsManager;

/**
 * 
 */
struct SKYABILITYSYSTEM_API FSkyGameplayTags
{
	static const FSkyGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

	/* Custom Tags */
	// ...
	
protected:

	//Registers all of the tags with the GameplayTags Manager
	void AddAllTags(UGameplayTagsManager& Manager);

	//Helper function used by AddAllTags to register a single tag with the GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment ="");

private:	
	static FSkyGameplayTags GameplayTags;
};