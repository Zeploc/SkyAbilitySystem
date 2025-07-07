// Copyright Skyward Studios, Inc. All Rights Reserved.


#include "SkyAbilitySystemComponent.h"


void USkyAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Required for OnTagUpdated() to be called 
	GameplayTagChangeHandle = RegisterGenericGameplayTagEvent().AddUObject(this, &USkyAbilitySystemComponent::OnGameplayTagChanged);
}

void USkyAbilitySystemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	RegisterGenericGameplayTagEvent().Remove(GameplayTagChangeHandle);
}


void USkyAbilitySystemComponent::ToggleGameplayTagByInstigator(const FGameplayTag GameplayTag, UObject* Instigator, bool bEnabled)
{
	FGameplayTagContainer& ActiveToggles = InstigatorToggles.FindOrAdd(Instigator);
	const bool bToggleCurrentlyActive = ActiveToggles.HasTagExact(GameplayTag);
	// Change should be done
	if (bToggleCurrentlyActive != bEnabled)
	{
		if (bEnabled)
		{
			AddLooseGameplayTag(GameplayTag);
			ActiveToggles.AddTag(GameplayTag);
		}
		else
		{
			RemoveLooseGameplayTag(GameplayTag);
			ActiveToggles.RemoveTag(GameplayTag);
		}
	}
}

void USkyAbilitySystemComponent::K2_RegisterGameplayTagEvent(const FGameplayTag Tag, FOnTagCountChanged TagEvent)
{
	if (!TagDelegates.Contains(Tag))
	{
		RegisterGameplayTagEvent(Tag, EGameplayTagEventType::AnyCountChange).AddUObject(this, &USkyAbilitySystemComponent::OnRegisteredTagChanged);
	}
	TagDelegates.FindOrAdd(Tag).AddUnique(TagEvent);
}

FOnGameplayTagEventMulti& USkyAbilitySystemComponent::RegisterGameplayEvent(const FGameplayTag Tag)
{
	if (!EventDelegates.Contains(Tag))
	{
		EventDelegateHandles.FindOrAdd(Tag) = AddGameplayEventTagContainerDelegate(FGameplayTagContainer(Tag), FGameplayEventTagMulticastDelegate::FDelegate::CreateUObject(this, &USkyAbilitySystemComponent::OnRegisteredEvent));
	}
	return EventDelegates.FindOrAdd(Tag);
}

void USkyAbilitySystemComponent::K2_RegisterGameplayEvent(const FGameplayTag Tag, FOnGameplayTagEvent Event)
{
	RegisterGameplayEvent(Tag).AddUnique(Event);
}

void USkyAbilitySystemComponent::K2_UnregisterGameplayEvent(const FGameplayTag Tag, FOnGameplayTagEvent Event)
{
	if (EventDelegates.Contains(Tag))
	{
		RemoveGameplayEventTagContainerDelegate(FGameplayTagContainer(Tag), EventDelegateHandles.FindOrAdd(Tag));
	}
	EventDelegates.FindOrAdd(Tag).Remove(Event);
	if (!EventDelegates.FindOrAdd(Tag).IsBound())
	{
		EventDelegateHandles.Remove(Tag);
	}
}

int32 USkyAbilitySystemComponent::HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload)
{
	const int32 SuccessfulActivations = Super::HandleGameplayEvent(EventTag, Payload);
	OnGameplayEvent.Broadcast(EventTag, *Payload);
	return SuccessfulActivations;
}

void USkyAbilitySystemComponent::OnGameplayTagChanged(const FGameplayTag Tag, int32 Count)
{
	OnGameplayTagModified.Broadcast(Tag, Count > 0);
	if (Count > 0)
	{
		OnGameplayTagAdded.Broadcast(Tag);
	}
	else
	{
		OnGameplayTagRemoved.Broadcast(Tag);
	}
}

void USkyAbilitySystemComponent::OnRegisteredTagChanged(const FGameplayTag Tag, int32 TagCount)
{	
	TagDelegates[Tag].Broadcast(this, Tag, TagCount);
}

void USkyAbilitySystemComponent::OnRegisteredEvent(FGameplayTag Tag, const FGameplayEventData* Payload)
{
	for (auto& EventSet : EventDelegates)
	{
		if (!EventSet.Key.IsValid() || Tag.MatchesTag(EventSet.Key))
		{
			EventSet.Value.Broadcast(this, Tag, *Payload);
		}
	}
}

void USkyAbilitySystemComponent::K2_AddLooseGameplayTag(const FGameplayTag GameplayTag, int32 Count)
{
	AddLooseGameplayTag(GameplayTag, Count);
}

void USkyAbilitySystemComponent::K2_AddLooseGameplayTags(const FGameplayTagContainer GameplayTags, int32 Count)
{
	AddLooseGameplayTags(GameplayTags, Count);
}

void USkyAbilitySystemComponent::K2_RemoveLooseGameplayTag(const FGameplayTag GameplayTag, int32 Count)
{
	RemoveLooseGameplayTag(GameplayTag, Count);
}

void USkyAbilitySystemComponent::K2_RemoveLooseGameplayTags(const FGameplayTagContainer GameplayTags, int32 Count)
{
	RemoveLooseGameplayTags(GameplayTags, Count);
}

void USkyAbilitySystemComponent::K2_SetLooseGameplayTagCount(const FGameplayTag GameplayTag, int32 NewCount)
{
	SetLooseGameplayTagCount(GameplayTag, NewCount);
}