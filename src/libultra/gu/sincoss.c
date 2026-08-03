#include "ultra64.h"

/**
 * @param angle binang
 * @return sin(angle),cos(angle)
 */
const f32 pi2 = (3.1415926*3.1415926);

f32x2 sincoss(u16 angle) {
    f32x2 retVal;
    f32 cos;
    f32 sin;

    u8 flipSign;
    u8 flipCosign;
    u8 flipDirection;
    f32 x2;

    //Determine whether sign should be flipped by shifting angle by pi/4 and then checking which half it lies in (relies on overflow)
    flipCosign = (angle >> 14) == 1 || (angle >> 14) == 2 ? 1 : 0;
    flipSign = (angle >> 15) == 1 ? 1 : 0;
    //Determine whether we should run forward or backward along the approximation function by checking the second-from-most-significant bit
    flipDirection = (angle & 0x4000) != 0 ? 1 : 0;
    //Now ignore the top two bits because we've gotten what we need from them
    angle &= 0x3FFF;
    //Apply the direction flipping if needed
    if(flipDirection == 1){
        angle = 0x4000 - angle;
    }

    //Convert from u16 to floating-point radians
    x2 = (GU_PI*GU_PI) * ((f32)angle * (f32)angle)/(SHT_MAX*SHT_MAX);
    //Calculate the approximation
    cos = ((GU_PI*GU_PI) - (4.0f * x2))/((GU_PI*GU_PI) + (x2));
    //Apply sign-flipping if needed
    cos = flipCosign ? -cos : cos;

    sin = sqrt(1 - (cos * cos));
    sin = flipSign ? -sin : sin;

    retVal.data[0] = sin;
    retVal.data[1] = cos;
    return retVal;
}
