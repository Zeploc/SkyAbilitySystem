// Copyright Skyward Studios, Inc. All Rights Reserved.

#include "SkyAbilitySystem.h"

#include "SkyGameplayTags.h"

#define LOCTEXT_NAMESPACE "FSkyAbilitySystemModule"

void FSkyAbilitySystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FSkyGameplayTags::InitializeNativeTags();
}

void FSkyAbilitySystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSkyAbilitySystemModule, SkyAbilitySystem)