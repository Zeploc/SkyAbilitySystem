// Copyright 2017-2022 Mighty Eyes Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "SkyAbilitySystemComponent.h"
#include "SkyAbilitySystemInterface.generated.h"

UINTERFACE(BlueprintType, MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class USkyAbilitySystemInterface  : public UAbilitySystemInterface
{
	GENERATED_BODY()
};

class SKYABILITYSYSTEM_API ISkyAbilitySystemInterface : public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category=GameplayAbility)
	virtual void AddGameplayTags(const FGameplayTagContainer TagContainer, int Count = 1);
	UFUNCTION(BlueprintCallable, Category=GameplayAbility)
	virtual void AddGameplayTag(const FGameplayTag GameplayTag, int Count = 1);
	UFUNCTION(BlueprintCallable, Category=GameplayAbility)
	virtual void RemoveGameplayTags(const FGameplayTagContainer TagContainer, int Count = 1);
	UFUNCTION(BlueprintCallable, Category=GameplayAbility)
	virtual void RemoveGameplayTag(const FGameplayTag GameplayTag, int Count = 1);
	
	UFUNCTION(BlueprintCallable, Category=GameplayAbility)
	virtual void SetGameplayTagCount(const FGameplayTag GameplayTag, int Count = 1);
	
	/* Sets the tags counts to 1 */
	UFUNCTION(BlueprintCallable, Category=GameplayAbility)
	virtual void EnableGameplayTags(const FGameplayTagContainer TagContainer);
	/* Sets the tag counts to 1 */
	UFUNCTION(BlueprintCallable, Category=GameplayAbility)
	virtual void EnableGameplayTag(const FGameplayTag GameplayTag);
	
	UFUNCTION(BlueprintCallable, Category=GameplayAbility)
	virtual void ToggleGameplayTagByInstigator(const FGameplayTag GameplayTag, UObject* Instigator, bool bEnabled);

	UFUNCTION(BlueprintCallable, Category=GameplayAbility)
	virtual void ToggleGameplayTag(const FGameplayTag GameplayTag);
	UFUNCTION(BlueprintCallable, Category=GameplayAbility)
	virtual void ToggleGameplayTagWithBool(const FGameplayTag GameplayTag, bool bEnabled);

	/* Sets the tag counts to 0 */
	UFUNCTION(BlueprintCallable, Category=GameplayAbility, meta=(Keywords="Clear,Remove"))
	virtual void DisableGameplayTags(const FGameplayTagContainer TagContainer);
	/* Sets the tag count to 0 */
	UFUNCTION(BlueprintCallable, Category=GameplayAbility, meta=(Keywords="Clear,Remove"))
	virtual void DisableGameplayTag(const FGameplayTag GameplayTag);	
	
	UFUNCTION(BlueprintCallable, Category=GameplayAbility, meta=(Keywords="assign,bind"))
	virtual void RegisterGameplayTagEvent(const FGameplayTag Tag, FOnTagCountChanged TagEvent);
	UFUNCTION(BlueprintCallable, Category=GameplayAbility, meta=(Keywords="assign,bind"))
	virtual void RegisterAndCallGameplayTagEvent(const FGameplayTag Tag, FOnTagCountChanged TagEvent);

	UFUNCTION(BlueprintCallable, Category=GameplayAbility, meta=(Keywords="assign,bind"))
	virtual void RegisterGameplayEvent(const FGameplayTag Tag, FOnGameplayTagEvent Event);
	
	UFUNCTION(BlueprintCallable, Category=GameplayAbility, meta=(Keywords="unassign,unbind"))
	virtual void UnregisterGameplayEvent(const FGameplayTag Tag, FOnGameplayTagEvent Event);
};