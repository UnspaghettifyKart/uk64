#ifndef DISPLAY_PROFILER_H
#define DISPLAY_PROFILER_H

#include <ultra64.h>
#include <defines.h>
#include "profiler.h"
/**
 * This is the position of the displayed text.
 * It's calculated from the top left.
 */
#define TEXT_Y_POSSITION 200
#define TEXT_X_POSSITION -5

#define HEXIDECIMAL 16
#define DECIMAL 10
#define OCTAL 8
#define BINARY 2

#define OS_CYCLES_TO_USEC(c)   (s32) (((f32) c)* 21.91/1000)
#define FRAMETIME_COUNT 30
#define PROFILER_COUNT 60

extern struct ProfilerFrameData gProfilerFrameData[];
extern s16 D_800DC668;

void s32_to_string(char*, s32, u8);
void display_profiler(bool*);
#endif