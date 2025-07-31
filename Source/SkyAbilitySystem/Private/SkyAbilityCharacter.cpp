// Fill out your copyright notice in the Description page of Project Settings.


#include "SkyAbilityCharacter.h"

ASkyAbilityCharacter::ASkyAbilityCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<USkyAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

UAbilitySystemComponent* ASkyAbilityCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ASkyAbilityCharacter::GetOwnedGameplayTags(FGameplayTagContainer& TagContainer) const
{
	AbilitySystemComponent->GetOwnedGameplayTags(TagContainer);
}