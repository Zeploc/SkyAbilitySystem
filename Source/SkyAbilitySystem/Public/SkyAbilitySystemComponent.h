// Copyright Skyward Studios, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "SkyAbilitySystemComponent.generated.h"

class USkyAbilitySystemComponent;

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnTagCountChanged, USkyAbilitySystemComponent*, OwningAbilitySystem, const FGameplayTag, Tag, int32, NewCount);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnGameplayTagEvent, USkyAbilitySystemComponent*, OwningAbilitySystem, const FGameplayTag, Tag, FGameplayEventData, Payload);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTagCountChangedMulti, USkyAbilitySystemComponent*, OwningAbilitySystem, const FGameplayTag, Tag, int32, NewCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnGameplayTagEventMulti, USkyAbilitySystemComponent*, OwningAbilitySystem, const FGameplayTag, Tag, FGameplayEventData, Payload);


UCLASS()
class SKYABILITYSYSTEM_API USkyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Abilities")
	virtual void ToggleGameplayTagByInstigator(const FGameplayTag GameplayTag, UObject* Instigator, bool bEnabled);

	UFUNCTION(BlueprintCallable, Category = "Abilities", Meta = (DisplayName = "Register Gameplay Tag Count Change", Keywords="assign,bind"))
	void K2_RegisterGameplayTagEvent(const FGameplayTag Tag, FOnTagCountChanged TagEvent);

	FOnGameplayTagEventMulti& RegisterGameplayEvent(const FGameplayTag Tag);
	
	UFUNCTION(BlueprintCallable, Category = "Abilities", Meta = (DisplayName = "Register Gameplay Event", Keywords="assign,bind"))
	void K2_RegisterGameplayEvent(const FGameplayTag Tag, FOnGameplayTagEvent Event);
	
	UFUNCTION(BlueprintCallable, Category = "Abilities", Meta = (DisplayName = "Unregister Gameplay Event", Keywords="assign,bind"))
	void K2_UnregisterGameplayEvent(const FGameplayTag Tag, FOnGameplayTagEvent Event);
	
	UFUNCTION(BlueprintCallable, Category = "Abilities", Meta = (DisplayName = "AddLooseGameplayTag"))
	void K2_AddLooseGameplayTag(const FGameplayTag GameplayTag, int32 Count = 1);

	UFUNCTION(BlueprintCallable, Category = "Abilities", Meta = (DisplayName = "AddLooseGameplayTags"))
	void K2_AddLooseGameplayTags(const FGameplayTagContainer GameplayTags, int32 Count = 1);

	UFUNCTION(BlueprintCallable, Category = "Abilities", Meta = (DisplayName = "RemoveLooseGameplayTag"))
	void K2_RemoveLooseGameplayTag(const FGameplayTag GameplayTag, int32 Count = 1);

	UFUNCTION(BlueprintCallable, Category = "Abilities", Meta = (DisplayName = "RemoveLooseGameplayTags"))
	void K2_RemoveLooseGameplayTags(const FGameplayTagContainer GameplayTags, int32 Count = 1);

	UFUNCTION(BlueprintCallable, Category = "Abilities", Meta = (DisplayName = "SetLooseGameplayTagCount"))
	void K2_SetLooseGameplayTagCount(const FGameplayTag GameplayTag, int32 NewCount);

	/* Only when a new tag is added or tag count is 0 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameplayTagModified, FGameplayTag, Tag, bool, bWasAdded);
	UPROPERTY(BlueprintAssignable, Category = "Abilities")
	FOnGameplayTagModified OnGameplayTagModified;

	/* Only when a new tag is added (count was 0) */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayTagAdded, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "Abilities")
	FOnGameplayTagAdded OnGameplayTagAdded;
	/* Only when the new tag count is 0 */
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayTagRemoved, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "Abilities")
	FOnGameplayTagRemoved OnGameplayTagRemoved;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameplayEvent, FGameplayTag, EventTag, FGameplayEventData, Payload);
	UPROPERTY(BlueprintAssignable, Category = "Abilities")
	FOnGameplayEvent OnGameplayEvent;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual int32 HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload) override;
	
	UFUNCTION()
	void OnGameplayTagChanged(const FGameplayTag Tag, int32 Count);

	UFUNCTION()
	void OnRegisteredTagChanged(const FGameplayTag Tag, int32 TagCount);
	void OnRegisteredEvent(FGameplayTag Tag, const FGameplayEventData* Payload);
	
	TMap<FGameplayTag, FOnTagCountChangedMulti> TagDelegates;
	TMap<FGameplayTag, FOnGameplayTagEventMulti> EventDelegates;
	TMap<FGameplayTag, FDelegateHandle> EventDelegateHandles;
	FDelegateHandle GameplayTagChangeHandle;

	UPROPERTY()
	TMap<TObjectPtr<UObject>, FGameplayTagContainer> InstigatorToggles;
};
