#ifndef MOD_FLYCAM
#define MOD_FLYCAM
#include <ultra64.h>
#include <defines.h>

void flycam(bool*,Camera *, Player *, s8);
void over_load_surface_map(bool*, uintptr_t, struct UnkStruct_800DC5EC *);
u16 ignore_for_flycam(bool*, Player *, Camera *, f32, f32);
extern u32 mod_isFlycam;
#endif
