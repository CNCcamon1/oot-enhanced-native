#include "libc64/os_malloc.h"
#include "debug_arena.h"
#include "printf.h"
#include "translation.h"

#define LOG_SEVERITY_NOLOG 0
#define LOG_SEVERITY_ERROR 2
#define LOG_SEVERITY_VERBOSE 3

Arena sDebugArena;

#define DEBUG_ARENA_CHECK_POINTER(ptr, size, name, action) (void)0

void* DebugArena_Malloc(u32 size) {
    void* ptr = __osMalloc(&sDebugArena, size);

    DEBUG_ARENA_CHECK_POINTER(ptr, size, "debug_malloc", T("確保", "Secure"));
    return ptr;
}

void* DebugArena_MallocR(u32 size) {
    void* ptr = __osMallocR(&sDebugArena, size);

    DEBUG_ARENA_CHECK_POINTER(ptr, size, "debug_malloc_r", T("確保", "Secure"));
    return ptr;
}

void* DebugArena_Realloc(void* ptr, u32 newSize) {
    ptr = __osRealloc(&sDebugArena, ptr, newSize);
    DEBUG_ARENA_CHECK_POINTER(ptr, newSize, "debug_realloc", T("再確保", "Re-secure"));
    return ptr;
}


void DebugArena_Free(void* ptr) {
    __osFree(&sDebugArena, ptr);
}

void* DebugArena_Calloc(u32 num, u32 size) {
    void* ret;
    u32 n = num * size;

    ret = __osMalloc(&sDebugArena, n);
    if (ret != NULL) {
        bzero(ret, n);
    }

    DEBUG_ARENA_CHECK_POINTER(ret, n, "debug_calloc", T("確保", "Secure"));
    return ret;
}

#if PLATFORM_GC && DEBUG_FEATURES
void DebugArena_Display(void) {
    // Likely copypasted from ZeldaArena_Display, should say "Debug"
    PRINTF(T("ゼルダヒープ表示\n", "Zelda heap display\n"));
    __osDisplayArena(&sDebugArena);
}
#endif

void DebugArena_GetSizes(u32* outMaxFree, u32* outFree, u32* outAlloc) {
    ArenaImpl_GetSizes(&sDebugArena, outMaxFree, outFree, outAlloc);
}

void DebugArena_Check(void) {
    __osCheckArena(&sDebugArena);
}

void DebugArena_Init(void* start, u32 size) {
    __osMallocInit(&sDebugArena, start, size);
}

void DebugArena_Cleanup(void) {
    __osMallocCleanup(&sDebugArena);
}

s32 DebugArena_IsInitialized(void) {
    return __osMallocIsInitialized(&sDebugArena);
}
