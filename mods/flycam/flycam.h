#ifndef MOD_FLYCAM
#define MOD_FLYCAM
#include <ultra64.h>
#include <defines.h>
#include "code_800029B0.h"
#include "camera.h"

void flycam(Camera *, Player *, s8, bool*);
void over_load_surface_map(uintptr_t, struct UnkStruct_800DC5EC *);
u16 ignore_for_flycam(bool*);
extern u32 mod_isFlycam;
#endif
