#include <ultra64.h>

#include "config.h"
#include "buffers.h"

u16 gRandomSeed16;

u8 randomSeedPadding[216];

#ifdef VERSION_EU
u8 frameBufferPadding[0x5750];
#else
u8 frameBufferPadding[0x5810];
#endif

struct_D_802BFB80 D_802BFB80[2][2][8];
struct_D_802DFB80 D_802DFB80[2][2][8];
#ifdef AVOID_UB
struct_D_802F1F80 D_802F1F80[2][4][8];
#else
u16 D_802F1F80[2][4][0x100 * 8];
#endif

u16 gZBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

#ifdef AVOID_UB
u16 gFramebuffers[3][SCREEN_WIDTH * SCREEN_HEIGHT];
#else
u16 gFramebuffer0[SCREEN_WIDTH * SCREEN_HEIGHT];
u16 gFramebuffer1[SCREEN_WIDTH * SCREEN_HEIGHT];
u16 gFramebuffer2[SCREEN_WIDTH * SCREEN_HEIGHT];
#endif
