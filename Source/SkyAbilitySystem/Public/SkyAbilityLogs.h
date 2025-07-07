// Copyright 2017-2022 Mighty Eyes Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(LogSkyAbility, Log, All);

#define SKY_ABILITY_LOG(Format, ...) \
{ \
UE_LOG(LogSkyAbility, Log, TEXT(Format"\n[File:%hs] [Line: %i]"), ##__VA_ARGS__, __FILE__, __LINE__); \
}
#define SKY_ABILITY_LOG_SIMPLE(Format, ...) \
{ \
UE_LOG(LogSkyAbility, Log, TEXT(Format), ##__VA_ARGS__); \
}
#define SKY_ABILITY_LOG_VERBOSE(Format, ...) \
{ \
UE_LOG(LogSkyAbility, Verbose, TEXT(Format "\n[File:%hs] [Line: %i]"), ##__VA_ARGS__, __FILE__, __LINE__); \
}

#define SKY_ABILITY_LOG_DISPLAY(Format, ...) \
{ \
UE_LOG(LogSkyAbility, Display, TEXT(Format"\n[File:%hs] [Line: %i]"), ##__VA_ARGS__, __FILE__, __LINE__); \
GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::White, FString::Printf(TEXT("Phox: " Format), ##__VA_ARGS__));\
}

#define SKY_ABILITY_LOG_WARNING(Format, ...) \
{ \
UE_LOG(LogSkyAbility, Warning, TEXT(Format"\n[File:%hs] [Line: %i]"), ##__VA_ARGS__, __FILE__, __LINE__); \
GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Orange, FString::Printf(TEXT("Phox: " Format), ##__VA_ARGS__));\
}
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST) // Do not Print in Shipping or Test

#endif

#define SKY_ABILITY_LOG_ERROR(Format, ...) \
{ \
UE_LOG(LogSkyAbility, Error, TEXT(Format"\n[File:%hs] [Line: %i]"), ##__VA_ARGS__, __FILE__, __LINE__); \
GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Red, FString::Printf(TEXT("Phox: " Format), ##__VA_ARGS__));\
}

#define SKY_ABILITY_LOG_FATAL(Format, ...) \
{ \
UE_LOG(LogSkyAbility, Fatal, TEXT(Format"\n[File:%hs] [Line: %i]"), ##__VA_ARGS__, __FILE__, __LINE__); \
}