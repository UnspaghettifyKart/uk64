#include <ultra64.h>
#include <hook.h>
#include <libc/stdio.h>
#include "display_profiler.h"
#include "code_80091750.h"
#include <assets/common_data.h>
#include "data_segment2.h"
#include "profiler.h"

static u8 digit[] = "0123456789abcdef";

HOOK(end_master_display_list, AT(FUNCTION_CALL), 0)
void display_profiler(bool* cancel) {
    u32 vNameLen;
    char vName[] = "Profiler :";
    char cBuffer[11] = "";
    s32 deltaTime = 0.0f;
    s16 index;
    vNameLen = sizeof(vName) / sizeof(char) - 1;

    gDisplayListHead--;
    index = D_800DC668^1;
    deltaTime = gProfilerFrameData[index].gameTimes[AFTER_DISPLAY_LISTS] - gProfilerFrameData[index].gameTimes[THREAD5_AT(FUNCTION_CALL)];
    s32_to_string(cBuffer, OS_CYCLES_TO_USEC(deltaTime), DECIMAL);
	load_debug_font();

    debug_print_str2(TEXT_X_POSSITION, TEXT_Y_POSSITION, vName);
    debug_print_str2(TEXT_X_POSSITION + (vNameLen * 0x8), TEXT_Y_POSSITION, cBuffer);
    gSPDisplayList(gDisplayListHead++, D_0D007EB8);
	gSPDisplayList(gDisplayListHead++, D_020076E0);
	func_80093C98(1);
}

u32 pow(u32 base, u32 exponent) {
    u32 result = 1;
    while (exponent != 0) {
        result *= base;
        --exponent;
    }
    return result;
}

void s32_to_string(char* bufferedString, s32 variable, u8 base) {
    int i, n;
	char* buffer = bufferedString;
    for (i = 0; i < 10; i++) {
        bufferedString[i] = digit[0];
    }
    n = pow(base, 9);
    for (i = 0; i < 10; i++) {
        bufferedString[i] = digit[variable / n];
        variable = variable % n;
        n /= base;
    }
}