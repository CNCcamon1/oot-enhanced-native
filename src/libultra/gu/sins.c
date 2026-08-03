#include "ultra64.h"

/**
 * @param angle binang
 * @return sin(angle)*0x7FFF
 */
s16 sins(u16 angle) {
    return coss(angle - 0x4000);
}
