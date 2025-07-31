// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagAssetInterface.h"
#include "SkyAbilitySystemInterface.h"
#include "SkyAbilityCharacter.generated.h"

class USkyAbilitySystemComponent;

UCLASS()
class SKYABILITYSYSTEM_API ASkyAbilityCharacter : public ACharacter, public ISkyAbilitySystemInterface , public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASkyAbilityCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;
		
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AbilitySystem")
	TObjectPtr<USkyAbilitySystemComponent> AbilitySystemComponent;

};
