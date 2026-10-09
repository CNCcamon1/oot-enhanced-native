#include "libc64/malloc.h"

#include "libc64/os_malloc.h"
#include "printf.h"
#include "translation.h"
#include "ultra64.h"

#define LOG_SEVERITY_NOLOG 0
#define LOG_SEVERITY_ERROR 2
#define LOG_SEVERITY_VERBOSE 3

Arena gSystemArena;

#define SYSTEM_ARENA_CHECK_POINTER(ptr, size, name, action) (void)0

void* SystemArena_Malloc(u32 size) {
    DECLARE_INTERRUPT_MASK
    void* ptr;

    DISABLE_INTERRUPTS();
    ptr = __osMalloc(&gSystemArena, size);
    RESTORE_INTERRUPTS();

    SYSTEM_ARENA_CHECK_POINTER(ptr, size, "malloc", T("確保", "Secure"));
    return ptr;
}

void* SystemArena_MallocR(u32 size) {
    DECLARE_INTERRUPT_MASK
    void* ptr;

    DISABLE_INTERRUPTS();
    ptr = __osMallocR(&gSystemArena, size);
    RESTORE_INTERRUPTS();

    SYSTEM_ARENA_CHECK_POINTER(ptr, size, "malloc_r", T("確保", "Secure"));
    return ptr;
}

void* SystemArena_Realloc(void* ptr, u32 newSize) {
    DECLARE_INTERRUPT_MASK

    DISABLE_INTERRUPTS();
    ptr = __osRealloc(&gSystemArena, ptr, newSize);
    RESTORE_INTERRUPTS();

    SYSTEM_ARENA_CHECK_POINTER(ptr, newSize, "realloc", T("再確保", "Re-secure"));
    return ptr;
}

void SystemArena_Free(void* ptr) {
    DECLARE_INTERRUPT_MASK

    DISABLE_INTERRUPTS();
    __osFree(&gSystemArena, ptr);
    RESTORE_INTERRUPTS();
}

void* SystemArena_Calloc(u32 num, u32 size) {
    DECLARE_INTERRUPT_MASK
    void* ret;
    u32 n = num * size;

    DISABLE_INTERRUPTS();
    ret = __osMalloc(&gSystemArena, n);
    RESTORE_INTERRUPTS();

    if (ret != NULL) {
        bzero(ret, n);
    }

    SYSTEM_ARENA_CHECK_POINTER(ret, n, "calloc", T("確保", "Secure"));
    return ret;
}

#if PLATFORM_GC && DEBUG_FEATURES
void SystemArena_Display(void) {
    PRINTF(T("システムヒープ表示\n", "System heap display\n"));
    __osDisplayArena(&gSystemArena);
}
#endif

void SystemArena_GetSizes(u32* outMaxFree, u32* outFree, u32* outAlloc) {
    ArenaImpl_GetSizes(&gSystemArena, outMaxFree, outFree, outAlloc);
}

void SystemArena_Check(void) {
    __osCheckArena(&gSystemArena);
}

void SystemArena_Init(void* start, u32 size) {
    __osMallocInit(&gSystemArena, start, size);
}

void SystemArena_Cleanup(void) {
    __osMallocCleanup(&gSystemArena);
}

s32 SystemArena_IsInitialized(void) {
    return __osMallocIsInitialized(&gSystemArena);
}
