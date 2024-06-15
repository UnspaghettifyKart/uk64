#include <ultra64.h>
#include <macros.h>
#include <mk64.h>
#include "buffers.h"

ALIGNED8 union_D_802BFB80 D_802BFB80;
ALIGNED8 struct_D_802DFB80 D_802DFB80[2][2][8];
#ifdef AVOID_UB
ALIGNED8 struct_D_802F1F80 D_802F1F80[2][4][8];
#else
ALIGNED8 u16 D_802F1F80[2][4][0x100 * 8];
#endif

ALIGNED8 u16 gZBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

#ifdef AVOID_UB
ALIGNED8 u16 gFramebuffers[3][SCREEN_WIDTH * SCREEN_HEIGHT];
#else
u16 gFramebuffer0[SCREEN_WIDTH * SCREEN_HEIGHT];
u16 gFramebuffer1[SCREEN_WIDTH * SCREEN_HEIGHT];
u16 gFramebuffer2[SCREEN_WIDTH * SCREEN_HEIGHT];
#endif
