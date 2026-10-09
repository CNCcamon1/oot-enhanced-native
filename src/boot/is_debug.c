#include "is_debug.h"

#include "ultra64.h"
#include "versions.h"

typedef struct ISVDbg {
    /* 0x00 */ u32 magic; // "IS64"
    /* 0x04 */ u32 get;
    /* 0x08 */ u8 unk_08[0xC];
    /* 0x14 */ u32 put;
    /* 0x18 */ u8 unk_18[0x8];
    /* 0x20 */ u8 data[0xFFE0];
} ISVDbg; // size = 0x10000

#define gISVDbgPrnAdrs ((ISVDbg*)0xB3FF0000)
#define ASCII_TO_U32(a, b, c, d) ((u32)((a << 24) | (b << 16) | (c << 8) | (d << 0)))

void osSyncPrintfUnused(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    va_end(args);
}

void osSyncPrintf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);


    va_end(args);
}

// assumption
void rmonPrintf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);


    va_end(args);
}

#if OOT_VERSION < PAL_1_0
void func_800015F4(void) {
}
#endif
