# Sky Ability System

The Sky Ability System is a custom gameplay ability system plugin for Unreal Engine that exposes various aspects of the framework to blueprints or providing default implementations.

## Main Features

### `SkyAbilitySystemComponent`
- Exposed component event bindings for gameplay event callbacks
- Exposed component event bindings for any gameplay tag being modified
  - **NOTE** As of now, these events will only trigger the *first* tag added, not following ones
- Blueprint exposed functions for adding, removing and setting tags directly

### `SkyAbilitySystemInterface`
- Exposed adding, removing and setting tag counts
- Helpers for "enabling" and "disabling" a tag
- Register gameplay events from any gameplay actor
- Register tags add/remove events from any gameplay actor

### Base Classes
- `SkyAbilityCharacter`: Base character class with integrated ability system functionality
- `SkyAbilityActor`: Base actor class for objects that can interact with the ability system

### Utility & Support
- `SkyGameplayTags`: Example of an object that defines and manages native gameplay tags
- `SkyAbilityLogs`: Logging helpers for ability-related debugging and monitoring

## Coming Soon
- Interface binding for tag query callback

## Getting Started
1. Add the plugin to your Unreal Engine project
2. Inherit from `SkyAbilityCharacter` for characters that need ability support
3. Inherit from `SkyAbilityActor` for custom actors that need ability support
4. Use `SkyAbilitySystemComponent` to manage abilities
5. Utilize `SkyGameplayTags` to categorize and organize abilities

For detailed implementation examples and API documentation, please refer to the header files in the Public directory.For detailed implementation examples and API documentation, please refer to the header files in the Public directory.## Troubleshooting

### Linker Errors
If you encounter `LNK1120` (unresolved external symbol) errors when extending the SkyAbilitySystem classes in C++, make sure the following modules are added to your project's Build.cs file:
``` c++
PrivateDependencyModuleNames.AddRange(new string[] {
  "SkyAbilitySystem",
  "GameplayAbilities",
  "GameplayTags"
});
```
