#ifndef ZELDA_ARENA_H
#define ZELDA_ARENA_H

#include "ultra64.h"

extern s32 gZeldaArenaLogSeverity;

void* ZeldaArena_Malloc(u32 size);
void* ZeldaArena_MallocR(u32 size);
void* ZeldaArena_Realloc(void* ptr, u32 newSize);
void ZeldaArena_Free(void* ptr);
void* ZeldaArena_Calloc(u32 num, u32 size);
void ZeldaArena_GetSizes(u32* outMaxFree, u32* outFree, u32* outAlloc);
void ZeldaArena_Check(void);
void ZeldaArena_Init(void* start, u32 size);
void ZeldaArena_Cleanup(void);
s32 ZeldaArena_IsInitialized(void);

#define ZELDA_ARENA_MALLOC(size, file, line) ZeldaArena_Malloc(size)
#define ZELDA_ARENA_MALLOC_R(size, file, line) ZeldaArena_MallocR(size)
#define ZELDA_ARENA_FREE(size, file, line) ZeldaArena_Free(size)

#endif
