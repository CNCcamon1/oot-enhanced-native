#include "libc64/os_malloc.h"
#include "printf.h"
#include "translation.h"

#define LOG_SEVERITY_NOLOG 0
#define LOG_SEVERITY_ERROR 2
#define LOG_SEVERITY_VERBOSE 3

Arena sZeldaArena;
#define ZELDA_ARENA_CHECK_POINTER(ptr, size, name, action) (void)0

void* ZeldaArena_Malloc(u32 size) {
    void* ptr = __osMalloc(&sZeldaArena, size);

    // TODO re-evaluate "secure" as a translation (in this file and others using "確保")
    ZELDA_ARENA_CHECK_POINTER(ptr, size, "zelda_malloc", T("確保", "Secure"));
    return ptr;
}

void* ZeldaArena_MallocR(u32 size) {
    void* ptr = __osMallocR(&sZeldaArena, size);

    ZELDA_ARENA_CHECK_POINTER(ptr, size, "zelda_malloc_r", T("確保", "Secure"));
    return ptr;
}

void* ZeldaArena_Realloc(void* ptr, u32 newSize) {
    ptr = __osRealloc(&sZeldaArena, ptr, newSize);
    ZELDA_ARENA_CHECK_POINTER(ptr, newSize, "zelda_realloc", T("再確保", "Re-securing"));
    return ptr;
}

void ZeldaArena_Free(void* ptr) {
    __osFree(&sZeldaArena, ptr);
}


void* ZeldaArena_Calloc(u32 num, u32 size) {
    void* ret;
    u32 n = num * size;

    ret = __osMalloc(&sZeldaArena, n);
    if (ret != NULL) {
        bzero(ret, n);
    }

    ZELDA_ARENA_CHECK_POINTER(ret, n, "zelda_calloc", T("確保", "Secure"));
    return ret;
}

#if PLATFORM_GC && DEBUG_FEATURES
void ZeldaArena_Display(void) {
    PRINTF(T("ゼルダヒープ表示\n", "Zelda heap display\n"));
    __osDisplayArena(&sZeldaArena);
}
#endif

void ZeldaArena_GetSizes(u32* outMaxFree, u32* outFree, u32* outAlloc) {
    ArenaImpl_GetSizes(&sZeldaArena, outMaxFree, outFree, outAlloc);
}

void ZeldaArena_Check(void) {
    __osCheckArena(&sZeldaArena);
}

void ZeldaArena_Init(void* start, u32 size) {
    __osMallocInit(&sZeldaArena, start, size);
}

void ZeldaArena_Cleanup(void) {
    __osMallocCleanup(&sZeldaArena);
}

s32 ZeldaArena_IsInitialized(void) {
    return __osMallocIsInitialized(&sZeldaArena);
}
