// Copyright Skyward Studios, Inc. All Rights Reserved.

#include "SkyAbilityActor.h"

#include "SkyAbilitySystemComponent.h"

ASkyAbilityActor::ASkyAbilityActor()
{
	AbilitySystemComponent = CreateDefaultSubobject<USkyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}

void ASkyAbilityActor::BeginPlay()
{
	// Add before blueprint begin
	AbilitySystemComponent->AddLooseGameplayTags(InitialTags);
	
	Super::BeginPlay();
}
 
UAbilitySystemComponent* ASkyAbilityActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASkyAbilityActor::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	AbilitySystemComponent->GetOwnedGameplayTags(TagContainer);
}
