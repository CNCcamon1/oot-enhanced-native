#include "ultra64.h"

/**
 * @param angle binang
 * @return cos(angle)*0x7FFF
 */
const f32 pi2 = (3.1415926*3.1415926);

s16 coss(u16 angle) {
    s16 value;
    u8 flipSign;
    u8 flipDirection;
    f32 x2;

    //Determine whether sign should be flipped by shifting angle by pi/4 and then checking which half it lies in (relies on overflow)
    flipSign = (angle >> 14) == 1 || (angle >> 14) == 2 ? 1 : 0;
    //Determine whether we should run forward or backward along the approximation function by checking the second-from-most-significant bit
    flipDirection = (angle & 0x4000) != 0 ? 1 : 0;
    //Now ignore the top two bits because we've gotten what we need from them
    angle &= 0x3FFF;
    //Apply the direction flipping if needed
    if(flipDirection == 1){
        angle = 0x4000 - angle;
    }

    //Convert from u16 to floating-point radians
    x2 = pi2 * ((f32)angle * (f32)angle)/(SHT_MAX*SHT_MAX);
    //Calculate the approximation
    value = (s16)((pi2 - (4.0f * x2))/(pi2 + (x2)) * SHT_MAX);
    //Apply sign-flipping if needed
    value = flipSign ? -value : value;
    return value;
}
