// Copyright 2017-2022 Mighty Eyes Ltd. All Rights Reserved.

#include "SkyAbilitySystemInterface.h"

#include "AbilitySystemComponent.h"
#include "SkyAbilityLogs.h"
#include "SkyAbilitySystemComponent.h"

void ISkyAbilitySystemInterface::AddGameplayTags(const FGameplayTagContainer TagContainer, int Count)
{
	GetAbilitySystemComponent()->AddLooseGameplayTags(TagContainer, Count);
}

void ISkyAbilitySystemInterface::AddGameplayTag(const FGameplayTag GameplayTag, int Count)
{
	GetAbilitySystemComponent()->AddLooseGameplayTag(GameplayTag, Count);
}

void ISkyAbilitySystemInterface::RemoveGameplayTags(const FGameplayTagContainer TagContainer, int Count)
{
	GetAbilitySystemComponent()->RemoveLooseGameplayTags(TagContainer, Count);
}

void ISkyAbilitySystemInterface::RemoveGameplayTag(const FGameplayTag GameplayTag, int Count)
{
	GetAbilitySystemComponent()->RemoveLooseGameplayTag(GameplayTag, Count);
}

void ISkyAbilitySystemInterface::SetGameplayTagCount(const FGameplayTag GameplayTag, int Count)
{
	GetAbilitySystemComponent()->SetLooseGameplayTagCount(GameplayTag, Count);
}

void ISkyAbilitySystemInterface::EnableGameplayTags(const FGameplayTagContainer TagContainer)
{
	for (const FGameplayTag& GameplayTag : TagContainer)
	{
		EnableGameplayTag(GameplayTag);
	}
}

void ISkyAbilitySystemInterface::EnableGameplayTag(const FGameplayTag GameplayTag)
{
#if !(UE_BUILD_TEST || UE_BUILD_SHIPPING)
	if (GetAbilitySystemComponent()->GetTagCount(GameplayTag) > 0)
	{
		SKY_ABILITY_LOG_VERBOSE("Enabling (setting to 1) tag %s on %s", *GetAbilitySystemComponent()->GetOwner()->GetName(), *GameplayTag.ToString())
	}
#endif
	GetAbilitySystemComponent()->SetLooseGameplayTagCount(GameplayTag, 1);
}

void ISkyAbilitySystemInterface::ToggleGameplayTagByInstigator(const FGameplayTag GameplayTag, UObject* Instigator, bool bEnabled)
{
	USkyAbilitySystemComponent* SkyAbilitySystemComponent = Cast<USkyAbilitySystemComponent>(GetAbilitySystemComponent());
	if (SkyAbilitySystemComponent)
	{
		SkyAbilitySystemComponent->ToggleGameplayTagByInstigator(GameplayTag, Instigator, bEnabled);
	}
}

void ISkyAbilitySystemInterface::ToggleGameplayTag(const FGameplayTag GameplayTag)
{
	ToggleGameplayTagWithBool(GameplayTag, !GetAbilitySystemComponent()->HasMatchingGameplayTag(GameplayTag));
}

void ISkyAbilitySystemInterface::ToggleGameplayTagWithBool(const FGameplayTag GameplayTag, bool bEnabled)
{
	if (bEnabled)
	{
		EnableGameplayTag(GameplayTag);
	}
	else
	{
		DisableGameplayTag(GameplayTag);
	}
}

void ISkyAbilitySystemInterface::DisableGameplayTags(const FGameplayTagContainer TagContainer)
{
	for (const FGameplayTag& GameplayTag : TagContainer)
	{
		DisableGameplayTag(GameplayTag);
	}
}

void ISkyAbilitySystemInterface::DisableGameplayTag(const FGameplayTag GameplayTag)
{
#if !(UE_BUILD_TEST || UE_BUILD_SHIPPING)
	if (GetAbilitySystemComponent()->GetTagCount(GameplayTag) > 0)
	{
		SKY_ABILITY_LOG_VERBOSE("Clearing (setting to 0) tag %s on %s", *GetAbilitySystemComponent()->GetOwner()->GetName(), *GameplayTag.ToString())
	}
#endif
	GetAbilitySystemComponent()->SetLooseGameplayTagCount(GameplayTag, 0);
}

void ISkyAbilitySystemInterface::RegisterGameplayTagEvent(const FGameplayTag Tag, FOnTagCountChanged TagEvent)
{
	Cast<USkyAbilitySystemComponent>(GetAbilitySystemComponent())->K2_RegisterGameplayTagEvent(Tag, TagEvent);
}

void ISkyAbilitySystemInterface::RegisterAndCallGameplayTagEvent(const FGameplayTag Tag, FOnTagCountChanged TagEvent)
{
	USkyAbilitySystemComponent* SkyAbilitySystemComponent = Cast<USkyAbilitySystemComponent>(GetAbilitySystemComponent());
	SkyAbilitySystemComponent->K2_RegisterGameplayTagEvent(Tag, TagEvent);
	const int32 TagCount = SkyAbilitySystemComponent->GetTagCount(Tag);
	if (TagCount > 0)
	{
		TagEvent.Execute(SkyAbilitySystemComponent, Tag, SkyAbilitySystemComponent->GetTagCount(Tag));
	}
}

void ISkyAbilitySystemInterface::RegisterGameplayEvent(const FGameplayTag Tag, FOnGameplayTagEvent Event)
{
	Cast<USkyAbilitySystemComponent>(GetAbilitySystemComponent())->K2_RegisterGameplayEvent(Tag, Event);
}

void ISkyAbilitySystemInterface::UnregisterGameplayEvent(const FGameplayTag Tag, FOnGameplayTagEvent Event)
{
	Cast<USkyAbilitySystemComponent>(GetAbilitySystemComponent())->K2_UnregisterGameplayEvent(Tag, Event);
}
