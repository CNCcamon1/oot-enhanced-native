#ifndef VERSIONS_H
#define VERSIONS_H

// OOT versions in build order
#define NTSC_1_0         1
#define NTSC_1_1         2
#define PAL_1_0          3
#define NTSC_1_2         4
#define PAL_1_1          5
#define GC_JP            6
#define GC_JP_MQ         7
#define GC_US            8
#define GC_US_MQ         9
#define GC_EU_DBG_2     10
#define GC_EU_MQ_DBG    11
#define GC_EU_DBG       12
#define GC_EU           13
#define GC_EU_MQ        14
#define GC_JP_CE        15
#define IQUE_CN         16

// NTSC/PAL
#define OOT_NTSC 1
#define OOT_PAL 0

// PAL N64 (50 Hz)
#define OOT_PAL_N64 0

// Master Quest
#define OOT_MQ 0

// Macro for constants that change in 50 Hz N64 PAL versions.
#define FRAMERATE_CONST(value60Hz, value50Hz) (value60Hz)

// Debug Assets
#define DEBUG_ASSETS 0

#endif
