// Copyright Skyward Studios, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagAssetInterface.h"
#include "SkyAbilitySystemInterface.h"

#include "SkyAbilityActor.generated.h"

class USkyAbilitySystemComponent;

UCLASS()
class SKYABILITYSYSTEM_API ASkyAbilityActor : public AActor, public ISkyAbilitySystemInterface , public IGameplayTagAssetInterface
{
	GENERATED_BODY()

public:
	ASkyAbilityActor();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ExposeOnSpawn))
	FGameplayTagContainer InitialTags;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "AbilitySystem")
	TObjectPtr<USkyAbilitySystemComponent> AbilitySystemComponent;

protected:
	virtual void BeginPlay() override;

};
