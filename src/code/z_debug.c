#include "libc64/malloc.h"
#include "libu64/gfxprint.h"
#include "libu64/pad.h"
#include "array_count.h"
#include "color.h"
#include "controller.h"
#include "gfx.h"
#include "gfxalloc.h"
#include "regs.h"
#include "rumble.h"
#include "ultra64.h"
#include "debug.h"

typedef struct DebugCamTextBufferEntry {
    /* 0x0 */ u8 x;
    /* 0x1 */ u8 y;
    /* 0x2 */ u8 colorIndex;
    /* 0x3 */ char text[21];
} DebugCamTextBufferEntry; // size = 0x18

typedef struct InputCombo {
    /* 0x0 */ u16 hold;
    /* 0x2 */ u16 press;
} InputCombo; // size = 0x4

#pragma increment_block_number "gc-eu:0 gc-eu-mq:0 gc-jp:0 gc-jp-ce:0 gc-jp-mq:0 gc-us:0 gc-us-mq:0 ique-cn:0" \
                               "ntsc-1.0:0 ntsc-1.1:0 ntsc-1.2:0 pal-1.0:0 pal-1.1:0"

RegEditor* gRegEditor;

DebugCamTextBufferEntry sDebugCamTextBuffer[22];

s16 sDebugCamTextEntryCount = 0;

Color_RGBA8 sDebugCamTextColors[] = {
    { 255, 255, 32, 192 },  // DEBUG_CAM_TEXT_YELLOW
    { 255, 150, 128, 192 }, // DEBUG_CAM_TEXT_PEACH
    { 128, 96, 0, 64 },     // DEBUG_CAM_TEXT_BROWN
    { 192, 128, 16, 128 },  // DEBUG_CAM_TEXT_ORANGE
    { 255, 192, 32, 128 },  // DEBUG_CAM_TEXT_GOLD
    { 230, 230, 220, 64 },  // DEBUG_CAM_TEXT_WHITE
    { 128, 150, 255, 128 }, // DEBUG_CAM_TEXT_BLUE
    { 128, 255, 32, 128 },  // DEBUG_CAM_TEXT_GREEN
};

void Regs_Init(void) {
    s32 i;

    gRegEditor = SYSTEM_ARENA_MALLOC(sizeof(RegEditor), "../z_debug.c", 260);
    gRegEditor->regPage = 0;
    gRegEditor->regGroup = 0;
    gRegEditor->regCur = 0;
    gRegEditor->dPadInputPrev = 0;
    gRegEditor->inputRepeatTimer = 0;
    for (i = 0; i < ARRAY_COUNT(gRegEditor->data); i++) {
        gRegEditor->data[i] = 0;
    }
}

// Function is stubbed. Name is assumed by similarities in signature to `DebugCamera_ScreenTextColored` and usage.
void DebugCamera_ScreenText(u8 x, u8 y, const char* text) {
}

void DebugCamera_ScreenTextColored(u8 x, u8 y, u8 colorIndex, const char* text) {
    DebugCamTextBufferEntry* entry = &sDebugCamTextBuffer[sDebugCamTextEntryCount];
    char* textDest;
    s16 charCount;

    if (sDebugCamTextEntryCount < ARRAY_COUNT(sDebugCamTextBuffer)) {
        entry->x = x;
        entry->y = y;
        entry->colorIndex = colorIndex;

        // Copy text into the entry, truncating if needed
        charCount = 0;
        textDest = entry->text;

        while ((*textDest++ = *text++) != '\0') {
            if (charCount++ > (ARRAY_COUNT(entry->text) - 1)) {
                break;
            }
        }

        *textDest = '\0';

        sDebugCamTextEntryCount++;
    }
}

void DebugCamera_DrawScreenText(GfxPrint* printer) {
    s32 i;
    Color_RGBA8* color;
    DebugCamTextBufferEntry* entry;

    for (i = 0; i < sDebugCamTextEntryCount; i++) {
        entry = &sDebugCamTextBuffer[i];
        color = &sDebugCamTextColors[entry->colorIndex];

        GfxPrint_SetColor(printer, color->r, color->g, color->b, color->a);
        GfxPrint_SetPos(printer, entry->x, entry->y);
        GfxPrint_Printf(printer, "%s", entry->text);
    }
}

/**
 * Draws the Reg Editor and Debug Camera text on screen
 */
void Debug_DrawText(GraphicsContext* gfxCtx) {
    Gfx* gfx;
    Gfx* opaStart;
    GfxPrint printer;
    s32 pad;

    OPEN_DISPS(gfxCtx, "../z_debug.c", 628);

    GfxPrint_Init(&printer);
    opaStart = POLY_OPA_DISP;
    gfx = Gfx_Open(POLY_OPA_DISP);
    gSPDisplayList(OVERLAY_DISP++, gfx);
    GfxPrint_Open(&printer, gfx);

    if ((OREG(0) == 1) || (OREG(0) == 8)) {
        DebugCamera_DrawScreenText(&printer);
    }

    sDebugCamTextEntryCount = 0;

    gfx = GfxPrint_Close(&printer);
    gSPEndDisplayList(gfx++);
    Gfx_Close(opaStart, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx, "../z_debug.c", 664);

    GfxPrint_Destroy(&printer);
}
