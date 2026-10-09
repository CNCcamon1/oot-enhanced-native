#include "fault.h"
#include "printf.h"
#include "terminal.h"
#include "translation.h"

#if PLATFORM_N64 || DEBUG_FEATURES
f32 LogUtils_CheckFloatRange(const char* exp, int line, const char* valueName, f32 value, const char* minName, f32 min,
                             const char* maxName, f32 max) {
    if (value < min || max < value) {
        osSyncPrintf("%s %d: range error %s(%f) < %s(%f) < %s(%f)\n", exp, line, minName, min, valueName, value,
                     maxName, max);
    }
    return value;
}
#endif

void LogUtils_HungupThread(const char* name, int line) {
    OSId threadId = osGetThreadId(NULL);

#if PLATFORM_N64 || DEBUG_FEATURES
    osSyncPrintf("*** HungUp in thread %d, [%s:%d] ***\n", threadId, name, line);
#endif
    Fault_AddHungupAndCrash(name, line);
}

void LogUtils_ResetHungup(void) {
#if PLATFORM_N64 || DEBUG_FEATURES
    osSyncPrintf("*** Reset ***\n");
#endif
    Fault_AddHungupAndCrash("Reset", 0);
}
