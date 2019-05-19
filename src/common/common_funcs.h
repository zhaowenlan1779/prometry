// Copyright 2013 Dolphin Emulator Project / 2014 Citra Emulator Project

#pragma once

#include <string>

#if !defined(ARCHITECTURE_x86_64)
#include <cstdlib> // for exit
#endif
#include "common/common_types.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

// Inlining
#ifdef _WIN32
#define FORCE_INLINE __forceinline
#else
#define FORCE_INLINE inline __attribute__((always_inline))
#endif

#ifndef _MSC_VER

#ifdef ARCHITECTURE_x86_64
#define Crash() __asm__ __volatile__("int $3")
#else
#define Crash() exit(1)
#endif

#else // _MSC_VER

#if (_MSC_VER < 1900)
// Function Cross-Compatibility
#define snprintf _snprintf
#endif

// Locale Cross-Compatibility
#define locale_t _locale_t

extern "C" {
__declspec(dllimport) void __stdcall DebugBreak(void);
}
#define Crash() DebugBreak()

#endif // _MSC_VER ndef
