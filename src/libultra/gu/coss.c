#include "ultra64.h"

#define PI_2_U16 0x4000
#define PI_U16 0x8000
#define ThreePI_2_U16 0xC000


/**
 * @param angle binang
 * @return cos(angle)*0x7FFF
 */
s16 coss(u16 angle) {
    s16 value;
    u8 flipSign;
    f32 x;

    if(angle <= PI_2_U16){
        flipSign = 0;
    }
    else if(angle <= PI_U16){
        angle = PI_2_U16 - (angle - PI_2_U16);
        flipSign = 1;
    }
    else if(angle <= ThreePI_2_U16){
        angle = angle - PI_U16;
        flipSign = 1;
    }
    else{
        flipSign = 0;
        angle = PI_2_U16 - (angle - ThreePI_2_U16);
    }

    x = (2*GU_PI) * (((f32)angle)/(SHT_MAX * 2));
    value = (s16)(((GU_PI * GU_PI) - (4.0f * x * x))/((GU_PI * GU_PI) + (x * x)) * SHT_MAX);
    value = flipSign ? -value : value;
    return value;
}
