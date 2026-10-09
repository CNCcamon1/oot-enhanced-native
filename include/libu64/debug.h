#ifndef LIBU64_DEBUG_H
#define LIBU64_DEBUG_H

#include "ultra64.h"

#define LOG(exp, value, format, file, line) (void)(value)

#define LOG_STRING(string, file, line) LOG(#string, string, "%s", file, line)
#define LOG_ADDRESS(exp, value, file, line) LOG(exp, value, "%08x", file, line)
#define LOG_TIME(exp, value, file, line) LOG(exp, value, "%lld", file, line)
#define LOG_NUM(exp, value, file, line) LOG(exp, value, "%d", file, line)
#define LOG_HEX(exp, value, file, line) LOG(exp, value, "%x", file, line)
#define LOG_HEX32(exp, value, file, line) LOG(exp, value, "%08x", file, line)
#define LOG_FLOAT(exp, value, file, line) LOG(exp, value, "%f", file, line)

#if PLATFORM_N64 || DEBUG_FEATURES
f32 LogUtils_CheckFloatRange(const char* exp, int line, const char* valueName, f32 value, const char* minName, f32 min,
                             const char* maxName, f32 max);
#endif

#define LOG_UTILS_CHECK_NULL_POINTER(exp, ptr, file, line) (void)0
#define LOG_UTILS_CHECK_VALID_POINTER(exp, ptr, file, line) (void)0

void LogUtils_HungupThread(const char* name, int line);
void LogUtils_ResetHungup(void);

#endif
