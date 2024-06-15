#include <ultra64.h>
#include <macros.h>
#include <mk64.h>
#include <common_structs.h>
#include <defines.h>
#include <course.h>

#include "render_courses.h"
#include "code_800029B0.h"
#include "main.h"
#include "actors.h"
#include "math_util.h"
#include "memory.h"
#include "code_80281780.h"
#include "collision.h"
#include "skybox_and_splitscreen.h"
#include "courses/all_course_data.h"
#include "courses/all_course_packed.h"
#include "courses/all_course_offsets.h"

s16 D_802B87B0 = 995;
s16 D_802B87B4 = 1000;
UNUSED s32 D_802B87B8 = 0;
s32 D_802B87BC = 0;
UNUSED s32 D_802B87C0 = 0;
s32 D_802B87C4 = 0;
s32 D_802B87C8 = 0;
s32 D_802B87CC = 0;
s16 D_802B87D0 = 0;
s16 D_802B87D4 = 0;
s16 currentScreenSection = 0;

s32 func_80290C20(Camera *camera) {
    if (camera->unk_54.unk34 == 0) {
        return 1;
    }
    if ((camera->unk_54.unk30 == 1) && (camera->unk_54.unk3C[0] < 3.0f)) {
        return 1;
    }
    if ((camera->unk_54.unk32 == 1) && (camera->unk_54.unk3C[1] < 3.0f)) {
        return 1;
    }
    return 0;
}

void parse_course_displaylists(uintptr_t addr) {
    s32 segment = SEGMENT_NUMBER2(addr);
    s32 offset = SEGMENT_OFFSET(addr);
    TrackSections *section = (TrackSections *) VIRTUAL_TO_PHYSICAL2(gSegmentTable[segment] + offset);

    while(section->addr != 0) {
        if (section->flags & 0x8000) {
            D_8015F59C = 1;
        } else {
            D_8015F59C = 0;
        }
        if (section->flags & 0x2000) {
            D_8015F5A0 = 1;
        } else {
            D_8015F5A0 = 0;
        }
        if (section->flags & 0x4000) {
            D_8015F5A4 = 1;
        } else {
            D_8015F5A4 = 0;
        }
        find_and_set_vertex_data(section->addr, section->surfaceType, section->sectionId);
        section++;
    }
}

void load_surface_map(uintptr_t addr, struct UnkStruct_800DC5EC *arg1) {
    Player *player = arg1->player;
    Camera *camera = arg1->camera;
    u32 segment = SEGMENT_NUMBER2(addr);
    u32 offset = SEGMENT_OFFSET(addr);
    //! @todo Should be Gfx*
    s32 *gfx = (s32 *) VIRTUAL_TO_PHYSICAL2(gSegmentTable[segment] + offset);
    s16 var_a3;
    s16 temp_v1;
    s16 sp1E;
    s16 temp_v0_3;
    u16 rot;
    if (gIsMirrorMode) {
        rot = (u16) camera->rot[1];
        if (rot < 0x2000) {
            var_a3 = 2;
        } else if (rot < 0x6000) {
            var_a3 = 3;
        } else if (rot < 0xA000) {
            var_a3 = 0;
        } else if (rot < 0xE000) {
            var_a3 = 1;
        } else {
            var_a3 = 2;
        }
    } else {
        rot = (u16) camera->rot[1];
        if (rot < 0x2000) {
            var_a3 = 2;
        } else if (rot < 0x6000) {
            var_a3 = 1;
        }
        else if (rot < 0xA000) {
            var_a3 = 0;
        }
        else if (rot < 0xE000) {
            var_a3 = 3;
        }
        else {
            var_a3 = 2;
        }
    }
    arg1->playerDirection = var_a3;

    if (D_80152300[camera - camera1] == 1) {
        sp1E = func_802ABD40(camera->unk_54.unk3A);
        temp_v0_3 = func_802ABD40(player->unk_110.unk3A);
        temp_v1 = sp1E - temp_v0_3;
        if ((temp_v1 < 2) && (temp_v1 >= -1)) {
            if (sp1E == 255) {
                if (temp_v0_3 == 255) {
                    temp_v1 = arg1->pathCounter;
                } else if (player->unk_110.unk3C[2] > 30.0f) {
                    temp_v1 = arg1->pathCounter;
                } else { 
                    temp_v1 = temp_v0_3;
                }
            } else if (camera->unk_54.unk3C[2] > 30.0f) {
                temp_v1 = arg1->pathCounter;
            } else { 
                temp_v1 = sp1E;
            }
        } else {

            switch(gCurrentCourseId) {
                case COURSE_BOWSER_CASTLE:
                        if ((temp_v0_3 >= 0x11) && (temp_v0_3 < 0x18)) {
                            temp_v1 = temp_v0_3;
                        } else if ((temp_v0_3 == 255) && (sp1E != 255)) {
                            temp_v1 = sp1E;
                        } else if ((temp_v0_3 != 255) && (sp1E == 255)) {
                            temp_v1 = temp_v0_3;
                        } else {
                            temp_v1 = arg1->pathCounter;
                        }
                    break;
                case COURSE_CHOCO_MOUNTAIN:
                    if ((temp_v0_3 >= 0xE) && (temp_v0_3 < 0x16)) {
                        temp_v1 = temp_v0_3;
                    } else if ((temp_v0_3 == 255) && (sp1E != 255)) {
                        temp_v1 = sp1E;
                    } else if ((temp_v0_3 != 255) && (sp1E == 255)) {
                        temp_v1 = temp_v0_3;
                    } else {
                        temp_v1 = arg1->pathCounter;
                    }
                    break;
                default:
                    if (temp_v0_3 == 255) {
                        temp_v1 = arg1->pathCounter;
                    } else if (player->unk_110.unk3C[2] > 30.0f) {
                        temp_v1 = arg1->pathCounter;
                    } else { 
                        temp_v1 = temp_v0_3;
                    }
                    break;
            }
        }
    } else {
        temp_v1 = func_802ABD40(camera->unk_54.unk3A);
        if (camera->unk_54.unk3C[2] > 30.0f) {
            temp_v1 = arg1->pathCounter;
        } else if (temp_v1 == 255) { 
            temp_v1 = arg1->pathCounter;
        }
    }

    arg1->pathCounter = temp_v1;
    temp_v1 = ((temp_v1 - 1) * 4) + var_a3;
    
    gSPDisplayList(gDisplayListHead++, gfx[temp_v1]);
}

void func_80291198(void) {
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_mario_raceway_packed_dl_1140));
}

void func_802911C4(void) {
    if (gScreenModeSelection == SCREEN_MODE_1P) {
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_mario_raceway_packed_dl_8E8));
    } else {
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_mario_raceway_packed_dl_2D68));
    }
}

void func_8029122C(struct UnkStruct_800DC5EC *arg0, s32 playerId) {
    UNUSED s32 pad;
    Player *player = arg0->player;
    Mat4 matrix;
    Vec3f vector;
    u16 pathCounter;
    u16 cameraRot;
    s16 playerDirection;

    init_rdp();
    pathCounter = (u16) arg0->pathCounter;
    cameraRot = (u16) arg0->camera->rot[1];
    playerDirection = arg0->playerDirection;
    switch (playerId) {
        case PLAYER_ONE:
            gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&gGfxPool->mtxPersp[PLAYER_ONE]), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
            gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&gGfxPool->mtxLookAt[PLAYER_ONE]), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
            break;
        case PLAYER_TWO:
            gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&gGfxPool->mtxPersp[PLAYER_TWO]), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
            gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&gGfxPool->mtxLookAt[PLAYER_TWO]), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
            break;
        case PLAYER_THREE:
            gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&gGfxPool->mtxPersp[PLAYER_THREE]), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
            gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&gGfxPool->mtxLookAt[PLAYER_THREE]), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
            break;
        case PLAYER_FOUR:
            gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&gGfxPool->mtxPersp[PLAYER_FOUR]), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
            gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&gGfxPool->mtxLookAt[PLAYER_FOUR]), G_MTX_NOPUSH | G_MTX_MUL | G_MTX_PROJECTION);
            break;
    }
    mtxf_identity(matrix);
    render_set_position(matrix, 0);
    switch (gCurrentCourseId) {
        case COURSE_BOWSER_CASTLE:
            if (gActiveScreenMode != SCREEN_MODE_1P) { return; }
            if (pathCounter < 6) { return; }
            if (pathCounter > 9) { return; }
            if (pathCounter == 9) {
                if (cameraRot < 0xA000) { return; }
                if (cameraRot > 0xE000) { return; }
            }
            gSPDisplayList(gDisplayListHead++, d_course_bowsers_castle_dl_9228);
            break;
        case COURSE_BANSHEE_BOARDWALK:
            gDPPipeSync(gDisplayListHead++);
            gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
            gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);
            gDPSetBlendMask(gDisplayListHead++, 0xFF);
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            gSPDisplayList(gDisplayListHead++, d_course_banshee_boardwalk_packed_dl_878);
            gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
            gDPPipeSync(gDisplayListHead++);
            break;
        case COURSE_KOOPA_BEACH:

            gDPPipeSync(gDisplayListHead++);
            gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
            gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);
            gDPSetBlendMask(gDisplayListHead++, 0xFF);
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);

            switch (pathCounter) {
                case 22:
                case 23:
                case 29:
                case 30:
                case 31:
                case 37:
                    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);
                    gSPDisplayList(gDisplayListHead++, d_course_koopa_troopa_beach_packed_dl_9E70);
                    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
                    break;
            }
            vector[0] = 0.0f;
            vector[1] = D_8015F8E4;
            vector[2] = 0.0f;
            mtxf_translate(matrix, vector);
            render_set_position(matrix, 0);

            gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);
            gDPSetBlendMask(gDisplayListHead++, 0xFF);
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);
            load_surface_map((uintptr_t) d_course_koopa_troopa_beach_dl_list2, arg0);
            gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 1, 1, G_OFF);
            gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
            gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
            gDPPipeSync(gDisplayListHead++);
            break;
        case COURSE_SHERBET_LAND:

            gDPPipeSync(gDisplayListHead++);
            gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
            gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetBlendMask(gDisplayListHead++, 0xFF);
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
            gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);

            mtxf_identity(matrix);
            render_set_position(matrix, 0);
            load_surface_map((uintptr_t) sherbet_land_dls_2, arg0);

            gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
            if ((func_80290C20(arg0->camera) == 1) && (func_802AAB4C(player) < player->pos[1])) {
                gSPSetGeometryMode(gDisplayListHead++, G_ZBUFFER);
                gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
                gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
                gSPDisplayList(gDisplayListHead++, d_course_sherbet_land_packed_dl_2B48);
            }
            gDPPipeSync(gDisplayListHead++);
            break;
        case COURSE_RAINBOW_ROAD:
            gDPPipeSync(gDisplayListHead++);
            mtxf_identity(matrix);
            render_set_position(matrix, 0);
            gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);
            load_surface_map((uintptr_t) &d_course_rainbow_road_dl_list, arg0);
            gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
            gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
            gDPPipeSync(gDisplayListHead++);
            break;
        case COURSE_WARIO_STADIUM:
            gDPPipeSync(gDisplayListHead++);
            gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
            gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);
            gDPSetBlendMask(gDisplayListHead++, 0xFF);
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
            gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);

            mtxf_identity(matrix);
            render_set_position(matrix, 0);

            gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
            gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_XLU_SURF, G_RM_AA_ZB_XLU_SURF2);
            gDPSetPrimColor(gDisplayListHead++, 0, 0, 0xFF, 0xFF, 0x00, 0xFF);
            gSPDisplayList(gDisplayListHead++, d_course_wario_stadium_packed_dl_EC0);
            gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 1, 1, G_OFF);
            gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
            gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
            gDPPipeSync(gDisplayListHead++);
            break;
        case COURSE_DK_JUNGLE:
            gDPPipeSync(gDisplayListHead++);
            gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
            gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetBlendMask(gDisplayListHead++, 0xFF);
            gDPSetTextureFilter(gDisplayListHead++, G_TF_BILERP);
            gDPSetTexturePersp(gDisplayListHead++, G_TP_PERSP);

            mtxf_identity(matrix);
            render_set_position(matrix, 0);

            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_XLU_INTER, G_RM_NOOP2);

            if (pathCounter < 17) {
                gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3E40);
                gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3EB0);
                if ((pathCounter >= 6) && (pathCounter < 13)) {
                    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                    gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3DD0);
                }
            } else if ((pathCounter == 21) || (pathCounter == 22)) {
                    if (playerDirection == 3) {
                        gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_36A8);
                    }
                    if ((playerDirection == 1) || (playerDirection == 0)) {
                        gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_36A8);
                    } else {
                        gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3F30);
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_36A8);
                    }
                } else if (pathCounter == 24) {
                    if ((playerDirection == 0) || (playerDirection == 3)) {
                        gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_36A8);
                    }
                } else if (pathCounter == 23) {
                    if (playerDirection == 3) {
                        gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_36A8);
                    } else if (playerDirection == 0) {
                        gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_36A8);
                    }
                }
            gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
            switch (pathCounter) {
                case 5:
                    if (playerDirection != 3) {
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3DD0);
                    }
                    break;
                case 17:
                    switch (playerDirection) {
                        case 0:
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3E40);
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3EB0);
                            break;
                        case 1:
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3DD0);
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3E40);
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3EB0);
                            break;
                        case 2:
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3E40);
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3EB0);
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3F30);
                            break;
                        case 3:
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3EB0);
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3F30);
                            break;
                    }
                    break;
                case 18:
                    switch (playerDirection) {
                        case 0:
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3E40);
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3EB0);
                            break;
                        case 1:
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3DD0);
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3E40);
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3EB0);
                            break;
                        case 2:
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3E40);
                            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3EB0);
                            break;
                    }
                    break;
                case 21:
                    if ((playerDirection == 0) || (playerDirection == 1)) {
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3E40);
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3EB0);
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3F30);
                    } else {
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3EB0);
                    }
                    break;
                case 22:
                    if (playerDirection == 0) {
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3F30);
                    }
                    break;
                case 23:
                    if (playerDirection != 1) {
                        gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_packed_dl_3F30);
                    }
                    break;
            }
            gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 1, 1, G_OFF);
            gDPSetAlphaCompare(gDisplayListHead++, G_AC_NONE);
            gDPPipeSync(gDisplayListHead++);
            break;
    }
}

void render_mario_raceway(struct UnkStruct_800DC5EC *arg0) {
    UNUSED s32 pad;
    u16 sp22 = arg0->pathCounter;
    u16 temp_t0 = arg0->playerDirection;

    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);

    if (func_80290C20(arg0->camera) == 1) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_mario_raceway_packed_dl_3050));
    }

    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gDPPipeSync(gDisplayListHead++);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);



    switch (sp22) {
        case 1:
        case 2:
        case 17:
            if ((temp_t0 == 2) || (temp_t0 == 1)) {
                func_802911C4();
            }
            break;
        case 3:
            if (temp_t0 != 0) {
                func_802911C4();
            }
            break;
        case 4:
            if (temp_t0 == 0) {
                func_80291198();
            } else {
                if (temp_t0 == 1) {
                    func_80291198();
                }
                func_802911C4();
            }
            break;
        case 5:
        case 6:
            if ((temp_t0 == 2) || (temp_t0 == 3)) {
                func_802911C4();
            } else {
                func_80291198();
            }
            break;
        case 7:
            func_80291198();
            if ((temp_t0 == 2) || (temp_t0 == 3)) {
                func_802911C4();
            }
            break;
        case 8:
        case 9:
            if (temp_t0 != 1) {
                func_802911C4();
            }
            /* fallthrough */
        case 10:
            if (temp_t0 != 2) {
                func_80291198();
            }
            break;
        case 11:
            if (temp_t0 == 0) {
                func_802911C4();
                func_80291198();
            } else if (temp_t0 == 3) {
                func_802911C4();
            }
            break;
        case 12:
            if ((temp_t0 == 0) || (temp_t0 == 3)) {
                func_802911C4();
            }
            break;
        case 13:
        case 14:
            if (temp_t0 != 1) {
            case 15:
            case 16:
                func_802911C4();
            }
            break;
    }
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_mario_raceway_packed_dl_3508));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_mario_raceway_packed_dl_3240));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_mario_raceway_packed_dl_14A0));

    load_surface_map((uintptr_t) mario_raceway_dls, arg0);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_mario_raceway_packed_dl_450));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_mario_raceway_packed_dl_240));
    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_mario_raceway_packed_dl_E0));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_mario_raceway_packed_dl_160));
}

void render_choco_mountain(struct UnkStruct_800DC5EC *arg0) {
    UNUSED s32 pad[13];

    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);

    if (func_80290C20(arg0->camera) == 1) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_choco_mountain_packed_dl_4608));
    }
    gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
    gDPSetFogColor(gDisplayListHead++, D_801625EC, D_801625F4, D_801625F0, 0xFF);
    gSPFogPosition(gDisplayListHead++, D_802B87B0, D_802B87B4);

    gDPPipeSync(gDisplayListHead++);
    gSPSetGeometryMode(gDisplayListHead++, G_FOG);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATERGB, G_CC_PASS2);

    gDPSetRenderMode(gDisplayListHead++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_choco_mountain_packed_dl_5A70));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_choco_mountain_packed_dl_828));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_choco_mountain_packed_dl_8E0));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_choco_mountain_packed_dl_5868));
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);

    load_surface_map((uintptr_t) choco_mountain_dls, arg0);

    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gDPSetRenderMode(gDisplayListHead++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_PASS2);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_choco_mountain_packed_dl_448));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_choco_mountain_packed_dl_5D8));
    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_choco_mountain_packed_dl_718));
    gSPClearGeometryMode(gDisplayListHead++, G_FOG);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
    gDPPipeSync(gDisplayListHead++);

}

void render_bowsers_castle(struct UnkStruct_800DC5EC *arg0) {

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);

    if (func_80290C20(arg0->camera) == 1) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_bowsers_castle_packed_dl_6A80));
    }

    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);

    D_802B87BC++;
    if (D_802B87BC > 255) {
        D_802B87BC = 0;
    }
    load_surface_map((uintptr_t) bowsers_castle_dls, arg0);

    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_bowsers_castle_packed_dl_248));
}

void render_banshee_boardwalk(struct UnkStruct_800DC5EC *arg0) {
    Camera *camera = arg0->camera;
    Mat4 spCC;
    UNUSED s32 pad[6];
    Vec3f spA8;
    UNUSED s32 pad2[6];

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_banshee_boardwalk_packed_dl_7228));

    gSPFogPosition(gDisplayListHead++, D_802B87B0, D_802B87B4);

    gDPPipeSync(gDisplayListHead++);

    gSPClearGeometryMode(gDisplayListHead++, G_SHADE | G_CULL_BOTH | G_FOG |
    G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_banshee_boardwalk_packed_dl_5CD0));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_banshee_boardwalk_packed_dl_4E60));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_banshee_boardwalk_packed_dl_69B0));

    load_surface_map((uintptr_t) banshee_boardwalk_dls, arg0);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADE | G_SHADING_SMOOTH);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_banshee_boardwalk_packed_dl_580));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_banshee_boardwalk_packed_dl_60));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_banshee_boardwalk_packed_dl_540));

    if (camera->pos[1] < -20.0f) {
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_banshee_boardwalk_packed_dl_6310));
    }
    spA8[0] = camera->pos[0];
    spA8[1] = -82.0f;
    spA8[2] = camera->pos[2];
    mtxf_translate(spCC, spA8);
    render_set_position(spCC, 0);

    gSPDisplayList(gDisplayListHead++, d_course_banshee_boardwalk_dl_B278);
    gDPPipeSync(gDisplayListHead++);
}

void render_yoshi_valley(struct UnkStruct_800DC5EC *arg0) {

    gDPPipeSync(gDisplayListHead++);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEI, G_CC_MODULATEI);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    load_surface_map((uintptr_t) d_course_yoshi_valley_dl_list, arg0);
    gDPPipeSync(gDisplayListHead++);
}

void render_frappe_snowland(struct UnkStruct_800DC5EC *arg0) {

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);

    if (func_80290C20(arg0->camera) == 1) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_frappe_snowland_packed_dl_65E0));
    }

    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    load_surface_map((uintptr_t) d_course_frappe_snowland_dl_list, arg0);
}

void render_koopa_troopa_beach(struct UnkStruct_800DC5EC *arg0) {

    gDPPipeSync(gDisplayListHead++);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);

    if (func_80290C20(arg0->camera) == 1) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_koopa_troopa_beach_packed_dl_9CC0));
    }
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_koopa_troopa_beach_packed_dl_9688));
    load_surface_map((uintptr_t) d_course_koopa_troopa_beach_dl_list1, arg0);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_koopa_troopa_beach_packed_dl_2C0));
    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gDPPipeSync(gDisplayListHead++);
}

void render_royal_raceway(struct UnkStruct_800DC5EC *arg0) {

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);

    if (func_80290C20(arg0->camera) == 1) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_royal_raceway_packed_dl_B030));
    }
    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_royal_raceway_packed_dl_A648));

    load_surface_map((uintptr_t) royal_raceway_dls, arg0);

    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_royal_raceway_packed_dl_11A8));
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_royal_raceway_packed_dl_8A0));
    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void render_luigi_raceway(struct UnkStruct_800DC5EC *arg0) {

    UNUSED s32 pad;
    u16 sp22 = (u16)arg0->pathCounter;
    s16 prevFrame;

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);

    if (func_80290C20(arg0->camera) == 1) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_luigi_raceway_packed_dl_9EC0));
    }

    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);

    load_surface_map((uintptr_t) luigi_raceway_dls, arg0);
    
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_luigi_raceway_packed_dl_E0));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_luigi_raceway_packed_dl_68));

    D_800DC5DC = 88;
    D_800DC5E0 = 72;

    // Render only the first player camera onto the television billboard. Screen agnostic screens of other players).
    if ((gActiveScreenMode == SCREEN_MODE_1P) && (sp22 >= 10) && (sp22 < 17)) {

        prevFrame = (s16)sRenderedFramebuffer - 1;

        if (prevFrame < 0) {
            prevFrame = 2;
        } else if (prevFrame >= 3) {
            prevFrame = 0;
        }
        currentScreenSection++;
        if (currentScreenSection >= 6) {
            currentScreenSection = 0;
        }
        /**
         * The jumbo television screen is split into six sections each section is copied one at a time.
         * This is done to fit within the n64's texture size requirements; 64x32
         */
        switch (currentScreenSection) {
            case 0:
                copy_framebuffer(D_800DC5DC, D_800DC5E0, 64, 32, (u16 *) PHYSICAL_TO_VIRTUAL(gPhysicalFramebuffers[prevFrame]), (u16 *) PHYSICAL_TO_VIRTUAL(gSegmentTable[5] + 0xF800));
                break;
            case 1:
                copy_framebuffer(D_800DC5DC + 64, D_800DC5E0, 64, 32, (u16 *) PHYSICAL_TO_VIRTUAL(gPhysicalFramebuffers[prevFrame]), (u16 *) PHYSICAL_TO_VIRTUAL(gSegmentTable[5] + 0x10800));
                break;
            case 2:
                copy_framebuffer(D_800DC5DC, D_800DC5E0 + 32, 64, 32, (u16 *) PHYSICAL_TO_VIRTUAL(gPhysicalFramebuffers[prevFrame]), (u16 *) PHYSICAL_TO_VIRTUAL(gSegmentTable[5] + 0x11800));
                break;
            case 3:
                copy_framebuffer(D_800DC5DC + 64, D_800DC5E0 + 32, 64, 32, (u16 *) PHYSICAL_TO_VIRTUAL(gPhysicalFramebuffers[prevFrame]), (u16 *) PHYSICAL_TO_VIRTUAL(gSegmentTable[5] + 0x12800));
                break;
            case 4:
                copy_framebuffer(D_800DC5DC, D_800DC5E0 + 64, 64, 32, (u16 *) PHYSICAL_TO_VIRTUAL(gPhysicalFramebuffers[prevFrame]), (u16 *) PHYSICAL_TO_VIRTUAL(gSegmentTable[5] + 0x13800));
                break;
            case 5:
                copy_framebuffer(D_800DC5DC + 64, D_800DC5E0 + 64, 64, 32, (u16 *) PHYSICAL_TO_VIRTUAL(gPhysicalFramebuffers[prevFrame]), (u16 *) PHYSICAL_TO_VIRTUAL(gSegmentTable[5] + 0x14800));
                break;
        }
    }
}

// Missing {} around if statements necessary for matching.
void render_moo_moo_farm(struct UnkStruct_800DC5EC *arg0) {
    UNUSED s32 pad[13];
    s16 temp_s0 = arg0->pathCounter;
    s16 temp_s1 = arg0->playerDirection;

    func_802B5D64((uintptr_t) D_800DC610, D_802B87D4, 0, 1);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEI, G_CC_MODULATEI);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_moo_moo_farm_packed_dl_4DF8));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_moo_moo_farm_packed_dl_5640));
    gSPFogPosition(gDisplayListHead++, D_802B87B0, D_802B87B4);

    load_surface_map((uintptr_t) moo_moo_farm_dls, arg0);

    if ((temp_s0 < 14) && (temp_s0 > 10)) {
        if ((temp_s1 == 2) || (temp_s1 == 3) || (temp_s1 == 1))
            // 
            gSPDisplayList(gDisplayListHead++, d_course_moo_moo_farm_dl_13FF8);
        
    } else if (temp_s0 < 16) {
            gSPDisplayList(gDisplayListHead++, d_course_moo_moo_farm_dl_13FF8);
    } else if (temp_s0 < 19) {
        if (temp_s1 != 2) 
            gSPDisplayList(gDisplayListHead++, d_course_moo_moo_farm_dl_13FF8);
        
    } else if (temp_s0 < 20) {
        if (temp_s1 == 0) 
            gSPDisplayList(gDisplayListHead++, d_course_moo_moo_farm_dl_13FF8);
        
    }
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEI, G_CC_MODULATEI);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);

    if ((temp_s0 >= 16) && (temp_s0 < 24)) {
        if ((temp_s1 == 2) || (temp_s1 == 3)) 
            gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_moo_moo_farm_packed_dl_5410));
        
    } else if (temp_s0 < 9) {
        if (temp_s1 == 2) 
            gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_moo_moo_farm_packed_dl_5410));
        
    }
    if (temp_s0 < 4) {
        if (temp_s1 != 0)
            gSPDisplayList(gDisplayListHead++, d_course_moo_moo_farm_dl_14060);
        
    } else if (temp_s0 < 8) {
        if (temp_s1 == 2)
            gSPDisplayList(gDisplayListHead++, d_course_moo_moo_farm_dl_14060);
        
    } else if (temp_s0 >= 22) {
            gSPDisplayList(gDisplayListHead++, d_course_moo_moo_farm_dl_14060);
    } else if (temp_s0 >= 18) {
        if ((temp_s1 == 0) || (temp_s1 == 3))
            gSPDisplayList(gDisplayListHead++, d_course_moo_moo_farm_dl_14060);
        
    }
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_moo_moo_farm_packed_dl_10C0));
}

void render_toads_turnpike(struct UnkStruct_800DC5EC *arg0) {
    UNUSED s32 pad[13];

    func_802B5D64((uintptr_t) &D_800DC610, D_802B87D4, 0, 1);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gDPSetFogColor(gDisplayListHead++, D_801625EC, D_801625F4, D_801625F0, 0xFF);
    gDPSetCycleType(gDisplayListHead++, G_CYC_2CYCLE);
    gSPFogPosition(gDisplayListHead++, D_802B87B0, D_802B87B4);
    gSPSetGeometryMode(gDisplayListHead++, G_FOG);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEI, G_CC_PASS2);
    gDPSetRenderMode(gDisplayListHead++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);

    load_surface_map((uintptr_t) d_course_toads_turnpike_dl_list, arg0);

    gDPSetRenderMode(gDisplayListHead++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2);
    gDPSetCombineMode(gDisplayListHead++, G_CC_DECALRGBA, G_CC_PASS2);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_toads_turnpike_packed_dl_0));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_toads_turnpike_packed_dl_68));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_toads_turnpike_packed_dl_D8));
    gSPClearGeometryMode(gDisplayListHead++, G_FOG);
    gDPSetCycleType(gDisplayListHead++, G_CYC_1CYCLE);
}

void render_kalimari_desert(struct UnkStruct_800DC5EC *arg0) {

    func_802B5D64((uintptr_t) D_800DC610, D_802B87D4, 0, 1);

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);

    if (func_80290C20(arg0->camera) == 1) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_kalimari_desert_packed_dl_71C8));
    }

    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEI, G_CC_MODULATEI);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    load_surface_map((uintptr_t) kalimari_desert_dls, arg0);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_kalimari_desert_packed_dl_1ED8));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_kalimari_desert_packed_dl_1B18));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_kalimari_desert_packed_dl_8330));
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_kalimari_desert_packed_dl_998));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_kalimari_desert_packed_dl_270));
    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void render_sherbet_land(struct UnkStruct_800DC5EC *arg0) {

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEI, G_CC_MODULATEI);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
    load_surface_map((uintptr_t) sherbet_land_dls, arg0);
}

void render_rainbow_road(UNUSED struct UnkStruct_800DC5EC *arg0) {

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIA, G_CC_MODULATEIA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
}

void render_wario_stadium(struct UnkStruct_800DC5EC *arg0) {
    s16 prevFrame;

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);

    if (func_80290C20(arg0->camera) == 1) {

        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_wario_stadium_packed_dl_A0C8));

    }
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATERGBA, G_CC_MODULATERGBA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);

    load_surface_map((uintptr_t) wario_stadium_dls, arg0);

    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_wario_stadium_packed_dl_A228));
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_wario_stadium_packed_dl_A88));
    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);

    D_800DC5DC = 88;
    D_800DC5E0 = 72;
    if (gActiveScreenMode == SCREEN_MODE_1P) {
        prevFrame = (s16) sRenderedFramebuffer - 1;
        if (prevFrame < 0) {
            prevFrame = 2;
        } else if (prevFrame >= 3) {
            prevFrame = 0;
        }
        currentScreenSection++;
        if (currentScreenSection > 5) {
            currentScreenSection = 0;
        }
        switch (currentScreenSection) {
        case 0:
            copy_framebuffer(D_800DC5DC, D_800DC5E0, 64, 32, (u16 *) PHYSICAL_TO_VIRTUAL(gPhysicalFramebuffers[prevFrame]), (u16 *) PHYSICAL_TO_VIRTUAL(gSegmentTable[5] + 0x8800));
            break;
        case 1:
            copy_framebuffer(D_800DC5DC + 64, D_800DC5E0, 64, 32, (u16 *) PHYSICAL_TO_VIRTUAL(gPhysicalFramebuffers[prevFrame]), (u16 *) PHYSICAL_TO_VIRTUAL(gSegmentTable[5] + 0x9800));
            break;
        case 2:
            copy_framebuffer(D_800DC5DC, D_800DC5E0 + 32, 64, 32, (u16 *) PHYSICAL_TO_VIRTUAL(gPhysicalFramebuffers[prevFrame]), (u16 *) PHYSICAL_TO_VIRTUAL(gSegmentTable[5] + 0xA800));
            break;
        case 3:
            copy_framebuffer(D_800DC5DC + 64, D_800DC5E0 + 32, 64, 32, (u16 *) PHYSICAL_TO_VIRTUAL(gPhysicalFramebuffers[prevFrame]), (u16 *) PHYSICAL_TO_VIRTUAL(gSegmentTable[5] + 0xB800));
            break;
        case 4:
            copy_framebuffer(D_800DC5DC, D_800DC5E0 + 64, 64, 32, (u16 *) PHYSICAL_TO_VIRTUAL(gPhysicalFramebuffers[prevFrame]), (u16 *) PHYSICAL_TO_VIRTUAL(gSegmentTable[5] + 0xC800));
            break;
        case 5:
            copy_framebuffer(D_800DC5DC + 64, D_800DC5E0 + 64, 64, 32, (u16 *) PHYSICAL_TO_VIRTUAL(gPhysicalFramebuffers[prevFrame]), (u16 *) PHYSICAL_TO_VIRTUAL(gSegmentTable[5] + 0xD800));
            break;
        }
    }
}

void render_block_fort(UNUSED struct UnkStruct_800DC5EC *arg0) {

    func_802B5D64((uintptr_t) &D_800DC610, D_802B87D4, 0, 1);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_block_fort_packed_dl_15C0));

}

void render_skyscraper(UNUSED struct UnkStruct_800DC5EC *arg0) {
    func_802B5D64((uintptr_t) &D_800DC610, D_802B87D4, 0, 1);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_skyscraper_packed_dl_FE8));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_skyscraper_packed_dl_C60));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_skyscraper_packed_dl_B70));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_skyscraper_packed_dl_6B8));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_skyscraper_packed_dl_570));
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_skyscraper_packed_dl_10C8));
    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_skyscraper_packed_dl_258));

}

void render_double_deck(UNUSED struct UnkStruct_800DC5EC *arg0) {

    func_802B5D64((uintptr_t) D_800DC610, D_802B87D4, 0, 1);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK);
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_double_deck_packed_dl_738));
    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void render_dks_jungle_parkway(struct UnkStruct_800DC5EC *arg0) {

    func_802B5D64((uintptr_t) D_800DC610, D_802B87D4, 0, 1);
    func_802B5D64((uintptr_t) &D_800DC610[1], D_802B87D4, D_802B87D0, 1);

    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_CULL_BACK | G_LIGHTING);

    if (func_80290C20(arg0->camera) == 1) {
        gSPTexture(gDisplayListHead++, 1, 1, 0, G_TX_RENDERTILE, G_OFF);
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_dks_jungle_parkway_packed_dl_92D8));
    }

    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(gDisplayListHead++, G_CC_MODULATEIDECALA, G_CC_MODULATEIDECALA);
    gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_TEX_EDGE, G_RM_AA_ZB_TEX_EDGE2);
    load_surface_map((uintptr_t) d_course_dks_jungle_parkway_unknown_dl_list, arg0);

    gSPSetGeometryMode(gDisplayListHead++, G_CULL_BACK);
}

void render_big_donut(struct UnkStruct_800DC5EC *arg0) {

    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);
    gSPClearGeometryMode(gDisplayListHead++, G_LIGHTING);
    func_802B5D64((uintptr_t) D_800DC610, D_802B87D4, 0, 1);
    gSPTexture(gDisplayListHead++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gDisplayListHead++, G_SHADING_SMOOTH);

    if (func_80290C20(arg0->camera) == 1) {
        gDPSetCombineMode(gDisplayListHead++, G_CC_SHADE, G_CC_SHADE);
        gDPSetRenderMode(gDisplayListHead++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_big_donut_packed_dl_DE8));
    }
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_big_donut_packed_dl_450));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_big_donut_packed_dl_AC0));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_big_donut_packed_dl_D20));
    gSPDisplayList(gDisplayListHead++, ((uintptr_t)d_course_big_donut_packed_dl_230));
}

void func_8029569C(void) {
    switch (gCurrentCourseId) {
        case COURSE_MARIO_RACEWAY:
            gSPDisplayList(gDisplayListHead++, d_course_mario_raceway_dl_9348);
            break;
        case COURSE_CHOCO_MOUNTAIN:
            gSPDisplayList(gDisplayListHead++, d_course_choco_mountain_dl_71B8);
            break;
        case COURSE_BOWSER_CASTLE:
            gSPDisplayList(gDisplayListHead++, d_course_bowsers_castle_dl_9148);
            break;
        case COURSE_BANSHEE_BOARDWALK:
            gSPDisplayList(gDisplayListHead++, d_course_banshee_boardwalk_dl_B308);
            break;
        case COURSE_YOSHI_VALLEY:
            gSPDisplayList(gDisplayListHead++, d_course_yoshi_valley_dl_18020);
            break;
        case COURSE_FRAPPE_SNOWLAND:
            gSPDisplayList(gDisplayListHead++, d_course_frappe_snowland_dl_76A0);
            break;
        case COURSE_KOOPA_BEACH:
            gSPDisplayList(gDisplayListHead++, d_course_koopa_troopa_beach_dl_18D68);
            break;
        case COURSE_ROYAL_RACEWAY:
            gSPDisplayList(gDisplayListHead++, d_course_royal_raceway_dl_D8E8);
            break;
        case COURSE_LUIGI_RACEWAY:
            gSPDisplayList(gDisplayListHead++, d_course_luigi_raceway_dl_FD40);
            break;
        case COURSE_MOO_MOO_FARM:
            gSPDisplayList(gDisplayListHead++, d_course_moo_moo_farm_dl_14088);
            break;
        case COURSE_TOADS_TURNPIKE:
            gSPDisplayList(gDisplayListHead++, d_course_toads_turnpike_dl_23930);
            break;
        case COURSE_KALAMARI_DESERT:
            gSPDisplayList(gDisplayListHead++, d_course_kalimari_desert_dl_22E00);
            break;
        case COURSE_SHERBET_LAND:
            gSPDisplayList(gDisplayListHead++, d_course_sherbet_land_dl_9AE8);
            break;
        case COURSE_RAINBOW_ROAD:
            gSPDisplayList(gDisplayListHead++, d_course_rainbow_road_dl_16220);
            break;
        case COURSE_WARIO_STADIUM:
            gSPDisplayList(gDisplayListHead++, d_course_wario_stadium_dl_CA78);
            break;
        case COURSE_BLOCK_FORT:
            gSPDisplayList(gDisplayListHead++, d_course_sherbet_land_dl_0);
            break;
        case COURSE_SKYSCRAPER:
            gSPDisplayList(gDisplayListHead++, d_course_sherbet_land_dl_0);
            break;
        case COURSE_DOUBLE_DECK:
            gSPDisplayList(gDisplayListHead++, d_course_sherbet_land_dl_0);
            break;
        case COURSE_DK_JUNGLE:
            gSPDisplayList(gDisplayListHead++, d_course_dks_jungle_parkway_dl_13C30);
            break;
        case COURSE_BIG_DONUT:
            gSPDisplayList(gDisplayListHead++, d_course_sherbet_land_dl_0);
            break;
    }
}

void render_course(struct UnkStruct_800DC5EC *arg0) {

    func_802B5D64((uintptr_t) D_800DC610, D_802B87D4, 0, 1);
    if (creditsRenderMode) {
        func_8029569C();
        return;
    }

    switch (gCurrentCourseId) {
    case COURSE_MARIO_RACEWAY:
        render_mario_raceway(arg0);
        break;
    case COURSE_CHOCO_MOUNTAIN:
        render_choco_mountain(arg0);
        break;
    case COURSE_BOWSER_CASTLE:
        render_bowsers_castle(arg0);
        break;
    case COURSE_BANSHEE_BOARDWALK:
        render_banshee_boardwalk(arg0);
        break;
    case COURSE_YOSHI_VALLEY:
        render_yoshi_valley(arg0);
        break;
    case COURSE_FRAPPE_SNOWLAND:
        render_frappe_snowland(arg0);
        break;
    case COURSE_KOOPA_BEACH:
        render_koopa_troopa_beach(arg0);
        break;
    case COURSE_ROYAL_RACEWAY:
        render_royal_raceway(arg0);
        break;
    case COURSE_LUIGI_RACEWAY:
        render_luigi_raceway(arg0);
        break;
    case COURSE_MOO_MOO_FARM:
        render_moo_moo_farm(arg0);
        break;
    case COURSE_TOADS_TURNPIKE:
        render_toads_turnpike(arg0);
        break;
    case COURSE_KALAMARI_DESERT:
        render_kalimari_desert(arg0);
        break;
    case COURSE_SHERBET_LAND:
        render_sherbet_land(arg0);
        break;
    case COURSE_RAINBOW_ROAD:
        render_rainbow_road(arg0);
        break;
    case COURSE_WARIO_STADIUM:
        render_wario_stadium(arg0);
        break;
    case COURSE_BLOCK_FORT:
        render_block_fort(arg0);
        break;
    case COURSE_SKYSCRAPER:
        render_skyscraper(arg0);
        break;
    case COURSE_DOUBLE_DECK:
        render_double_deck(arg0);
        break;
    case COURSE_DK_JUNGLE:
        render_dks_jungle_parkway(arg0);
        break;
    case COURSE_BIG_DONUT:
        render_big_donut(arg0);
        break;
    }
}

void func_80295BF8(s32 playerIndex) {
    Player* player = &gPlayers[playerIndex];
    func_802AAAAC(&player->unk_110);
    player->boundingBoxCorners[FRONT_RIGHT_TYRE].surfaceFlags = 0;
    player->boundingBoxCorners[FRONT_LEFT_TYRE].surfaceFlags  = 0;
    player->boundingBoxCorners[BACK_RIGHT_TYRE].surfaceFlags  = 0;
    player->boundingBoxCorners[BACK_LEFT_TYRE].surfaceFlags   = 0;

    player->boundingBoxCorners[FRONT_RIGHT_TYRE].surfaceMapIndex = 0x1388;
    player->boundingBoxCorners[FRONT_LEFT_TYRE].surfaceMapIndex  = 0x1388;
    player->boundingBoxCorners[BACK_RIGHT_TYRE].surfaceMapIndex  = 0x1388;
    player->boundingBoxCorners[BACK_LEFT_TYRE].surfaceMapIndex   = 0x1388;
}

void func_80295C6C(void) {
    gNextFreeMemoryAddress += ALIGN16(D_8015F588 * sizeof(mk64_surface_map_ram));
    gCourseMaxX += 20;
    gCourseMaxZ += 20;
    gCourseMinX += -20;
    gCourseMinZ += -20;
    gCourseMinY += -20;
    func_802AF314();
    gNextFreeMemoryAddress += ALIGN16(D_8015F58A * 2);
}

UNUSED void func_80295D50(s16 arg0, s16 arg1) {
    D_8015F6F4 = arg1;
    D_8015F6F6 = arg0;
}

void func_80295D6C(void) {
    D_8015F6F4 = 3000;
    D_8015F6F6 = -3000;
}

void func_80295D88(void) {
    gNumActors = 0;

    gCourseMinX = 0;
    gCourseMinY = 0;
    gCourseMinZ = 0;

    gCourseMaxX = 0;
    gCourseMaxY = 0;
    gCourseMaxZ = 0;
    
    D_8015F59C = 0;
    D_8015F5A0 = 0;
    func_80295D6C();
    D_8015F58C = 0;
    D_8015F588 = 0;
    gSurfaceMap = (mk64_surface_map_ram *) gNextFreeMemoryAddress;
    D_800DC5BC = 0;
    D_800DC5C8 = 0;
    switch (gCurrentCourseId) {
        case COURSE_MARIO_RACEWAY:
            // d_course_mario_raceway_packed_dl_1140
            set_vertex_data_with_defaults(d_course_mario_raceway_packed_dl_1140);
            if (gScreenModeSelection == SCREEN_MODE_1P) {
                // d_course_mario_raceway_packed_dl_8E8
                set_vertex_data_with_defaults(d_course_mario_raceway_packed_dl_8E8);
            } else {
                // d_course_mario_raceway_packed_dl_2D68
                set_vertex_data_with_defaults(d_course_mario_raceway_packed_dl_2D68);
            }
            parse_course_displaylists((uintptr_t) d_course_mario_raceway_addr);
            func_80295C6C();
            D_8015F8E4 = gCourseMinY - 10.0f;
            break;
        case COURSE_CHOCO_MOUNTAIN:
            D_800DC5BC = 1;
            D_801625EC = 255;
            D_801625F4 = 255;
            D_801625F0 = 255;
            D_802B87B0 = 0x3E3;
            D_802B87B4 = 0x3E8;
            D_802B87D4 = 0x71C;
            D_802B87D0 = 0xE38;

            // Spawn guardrail only for CC_50 and time trials.
            if ((gCCSelection != CC_50) && (gModeSelection != TIME_TRIALS)) {
                nullify_displaylist((uintptr_t)d_course_choco_mountain_packed_dl_0);
                nullify_displaylist((uintptr_t)d_course_choco_mountain_packed_dl_98);
                nullify_displaylist((uintptr_t)d_course_choco_mountain_packed_dl_178);
                nullify_displaylist((uintptr_t)d_course_choco_mountain_packed_dl_280);
                nullify_displaylist((uintptr_t)d_course_choco_mountain_packed_dl_340);
                nullify_displaylist((uintptr_t)d_course_choco_mountain_packed_dl_3C8);
            }
            parse_course_displaylists((uintptr_t) &d_course_choco_mountain_addr);
            func_802B5CAC(0x238E, 0x31C7, D_8015F590);
            func_80295C6C();
            D_8015F8E4 = -80.0f;
            break;
        case COURSE_BOWSER_CASTLE:
            parse_course_displaylists((uintptr_t) d_course_bowsers_castle_addr);
            func_80295C6C();
            find_vtx_and_set_colours((uintptr_t)d_course_bowsers_castle_packed_dl_1350, 0x32, 0, 0, 0);
            D_8015F8E4 = -50.0f;
            break;
        case COURSE_BANSHEE_BOARDWALK:
            D_800DC5BC = 1;
            D_801625EC = 0;
            D_801625F4 = 0;
            D_801625F0 = 0;
            parse_course_displaylists((uintptr_t) d_course_banshee_boardwalk_track_sections);
            func_80295C6C();
            find_vtx_and_set_colours((uintptr_t)d_course_banshee_boardwalk_packed_dl_878, 128, 0, 0, 0);
            D_8015F8E4 = -80.0f;
            break;
        case COURSE_YOSHI_VALLEY:
            func_802B5D64((uintptr_t) &d_course_yoshi_valley_lights4, -0x38F0, 0x1C70, 1);
            parse_course_displaylists((uintptr_t) d_course_yoshi_valley_addr);
            func_80295C6C();
            D_8015F8E4 = gCourseMinY - 10.0f;
            break;
        case COURSE_FRAPPE_SNOWLAND:
            parse_course_displaylists((uintptr_t) d_course_frappe_snowland_addr);
            func_80295C6C();
            D_8015F8E4 = -50.0f;
            break;
        case COURSE_KOOPA_BEACH:
            parse_course_displaylists((uintptr_t) d_course_koopa_troopa_beach_addr);
            func_80295C6C();
            find_vtx_and_set_colours((uintptr_t)d_course_koopa_troopa_beach_packed_dl_ADE0, -0x6A, 255, 255, 255);
            find_vtx_and_set_colours((uintptr_t)d_course_koopa_troopa_beach_packed_dl_A540, -0x6A, 255, 255, 255);
            find_vtx_and_set_colours((uintptr_t)d_course_koopa_troopa_beach_packed_dl_9E70, -0x6A, 255, 255, 255);
            find_vtx_and_set_colours((uintptr_t)d_course_koopa_troopa_beach_packed_dl_358, -0x6A, 255, 255, 255);
            break;
        case COURSE_ROYAL_RACEWAY:
            parse_course_displaylists((uintptr_t) d_course_royal_raceway_addr);
            func_80295C6C();
            D_8015F8E4 = -60.0f;
            break;
        case COURSE_LUIGI_RACEWAY:
            parse_course_displaylists((uintptr_t) d_course_luigi_raceway_addr);
            func_80295C6C();
            D_8015F8E4 = gCourseMinY - 10.0f;
            break;
        case COURSE_MOO_MOO_FARM:
            parse_course_displaylists((uintptr_t) d_course_moo_moo_farm_addr);
            func_80295C6C();
            D_8015F8E4 = gCourseMinY - 10.0f;
            break;
        case COURSE_TOADS_TURNPIKE:
            D_801625EC = 43;
            D_801625F4 = 13;
            D_801625F0 = 4;
            D_802B87B0 = 993;
            D_802B87B4 = 1000;
            parse_course_displaylists((uintptr_t) d_course_toads_turnpike_addr);
            func_80295C6C();
            D_8015F8E4 = gCourseMinY - 10.0f;
            break;
        case COURSE_KALAMARI_DESERT:
            parse_course_displaylists((uintptr_t) d_course_kalimari_desert_addr);
            func_80295C6C();
            D_8015F8E4 = gCourseMinY - 10.0f;
            break;
        case COURSE_SHERBET_LAND:
            parse_course_displaylists((uintptr_t) d_course_sherbet_land_addr);
            func_80295C6C();
            D_8015F8E4 = -18.0f;
            find_vtx_and_set_colours((uintptr_t)d_course_sherbet_land_packed_dl_1EB8, -0x4C, 255, 255, 255);
            find_vtx_and_set_colours((uintptr_t)d_course_sherbet_land_packed_dl_2308, -0x6A, 255, 255, 255);
            break;
        case COURSE_RAINBOW_ROAD:
            D_800DC5C8 = 1;
            parse_course_displaylists((uintptr_t) d_course_rainbow_road_addr);
            func_80295C6C();
            D_8015F8E4 = 0.0f;
            find_vtx_and_set_colours((uintptr_t)d_course_rainbow_road_packed_dl_2068, -0x6A, 255, 255, 255);
            find_vtx_and_set_colours((uintptr_t)d_course_rainbow_road_packed_dl_1E18, -0x6A, 255, 255, 255);
            find_vtx_and_set_colours((uintptr_t)d_course_rainbow_road_packed_dl_1318, 255, 255, 255, 0);
            if (gGamestate != CREDITS_SEQUENCE) {
                find_vtx_and_set_colours((uintptr_t)d_course_rainbow_road_packed_dl_1FB8, -0x6A, 255, 255, 255);
            }
            break;
        case COURSE_WARIO_STADIUM:
            parse_course_displaylists((uintptr_t) d_course_wario_stadium_addr);
            func_80295C6C();
            D_8015F8E4 = gCourseMinY - 10.0f;
            // d_course_wario_stadium_packed_dl_C50
            find_vtx_and_set_colours(d_course_wario_stadium_packed_dl_C50, 100, 255, 255, 255);
            // d_course_wario_stadium_packed_dl_BD8
            find_vtx_and_set_colours(d_course_wario_stadium_packed_dl_BD8, 100, 255, 255, 255);
            // d_course_wario_stadium_packed_dl_B60
            find_vtx_and_set_colours(d_course_wario_stadium_packed_dl_B60, 100, 255, 255, 255);
            // d_course_wario_stadium_packed_dl_AE8
            find_vtx_and_set_colours(d_course_wario_stadium_packed_dl_AE8, 100, 255, 255, 255);
            // d_course_wario_stadium_packed_dl_CC8
            find_vtx_and_set_colours(d_course_wario_stadium_packed_dl_CC8, 100, 255, 255, 255);
            // d_course_wario_stadium_packed_dl_D50
            find_vtx_and_set_colours(d_course_wario_stadium_packed_dl_D50, 100, 255, 255, 255);
            // d_course_wario_stadium_packed_dl_DD0
            find_vtx_and_set_colours(d_course_wario_stadium_packed_dl_DD0, 100, 255, 255, 255);
            // d_course_wario_stadium_packed_dl_E48
            find_vtx_and_set_colours(d_course_wario_stadium_packed_dl_E48, 100, 255, 255, 255);
            break;
        case COURSE_BLOCK_FORT:
            // d_course_block_fort_packed_dl_15C0
            set_vertex_data_with_default_section_id(d_course_block_fort_packed_dl_15C0, 1);
            func_80295C6C();
            D_8015F8E4 = gCourseMinY - 10.0f;
            break;
        case COURSE_SKYSCRAPER:
            // d_course_skyscraper_packed_dl_1110
            set_vertex_data_with_default_section_id(d_course_skyscraper_packed_dl_1110, 1);
            // d_course_skyscraper_packed_dl_258
            set_vertex_data_with_default_section_id(d_course_skyscraper_packed_dl_258, 1);
            func_80295C6C();

            D_8015F8E4 = -480.0f;
            break;
        case COURSE_DOUBLE_DECK:
            // d_course_double_deck_packed_dl_738
            set_vertex_data_with_default_section_id(d_course_double_deck_packed_dl_738, 1);
            func_80295C6C();
            D_8015F8E4 = gCourseMinY - 10.0f;
            break;
        case COURSE_DK_JUNGLE:
            parse_course_displaylists((uintptr_t) d_course_dks_jungle_parkway_addr);
            func_80295C6C();
            D_8015F8E4 =  -475.0f;
            find_vtx_and_set_colours((uintptr_t)d_course_dks_jungle_parkway_packed_dl_3FA8, 120, 255, 255, 255);
            break;
        case COURSE_BIG_DONUT:
            // d_course_big_donut_packed_dl_1018
            set_vertex_data_with_default_section_id(d_course_big_donut_packed_dl_1018, 6);
            // d_course_big_donut_packed_dl_450
            set_vertex_data_with_default_section_id(d_course_big_donut_packed_dl_450, 6);
            // d_course_big_donut_packed_dl_AC0
            set_vertex_data_with_default_section_id(d_course_big_donut_packed_dl_AC0, 6);
            // d_course_big_donut_packed_dl_B58
            set_vertex_data_with_default_section_id(d_course_big_donut_packed_dl_B58, 6);
            // d_course_big_donut_packed_dl_230
            set_vertex_data_with_default_section_id(d_course_big_donut_packed_dl_230, 6);
            func_80295C6C();
            D_8015F8E4 = 100.0f;
            break;
    }
}

void func_802966A0(void) {

    switch(gCurrentCourseId) {
        case COURSE_KOOPA_BEACH:
            if (D_8015F8E8 < 0.0f) {
                if (D_8015F8E4 < -20.0f) { D_8015F8E8 *= -1.0f; }
            } else {
                if (D_8015F8E4 > 0.0f) { D_8015F8E8 *= -1.0f; }
            }
            D_8015F8E4 += D_8015F8E8;

            D_802B87BC += 9;
            if (D_802B87BC > 255) {
                D_802B87BC = 0;
            }
            D_802B87C4 += 3;
            if (D_802B87C4 > 255) {
                D_802B87C4 = 0;
            }
            // waterfall animation
            find_and_set_tile_size((uintptr_t)d_course_koopa_troopa_beach_packed_dl_9D58, 0, D_802B87BC);
            find_and_set_tile_size((uintptr_t)d_course_koopa_troopa_beach_packed_dl_9CD0, 0, D_802B87C4);
            D_802B87CC = random_int(300) / 40;
            if (D_802B87C8 < 0) {
                D_802B87C8 = random_int(300) / 40;
            } else {
                D_802B87C8 = -(random_int(300) / 40);
            }
            // Waterfall bubbling effect? (unused)
            find_and_set_tile_size((uintptr_t)d_course_koopa_troopa_beach_packed_dl_2E8, D_802B87C8, D_802B87CC);
            break;
        case COURSE_BANSHEE_BOARDWALK:
            D_802B87BC++;

            if (D_802B87BC >= 0x100) {
                D_802B87BC = 0;
            }
            find_and_set_tile_size((uintptr_t)d_course_banshee_boardwalk_dl_B278, 0, D_802B87BC);
            break;
        case COURSE_ROYAL_RACEWAY:
            D_802B87BC -= 20;
            if (D_802B87BC < 0) {
                D_802B87BC = 0xFF;
            }
            find_and_set_tile_size((uintptr_t)d_course_royal_raceway_packed_dl_A6A8, 0, D_802B87BC);
            find_and_set_tile_size((uintptr_t)d_course_royal_raceway_packed_dl_A648, 0, D_802B87BC);
            break;
        case COURSE_DK_JUNGLE:
            D_802B87BC += 2;
            if (D_802B87BC > 255) {
                D_802B87BC = 0;
            }
            find_and_set_tile_size((uintptr_t)d_course_dks_jungle_parkway_packed_dl_3DD0, 0, D_802B87BC);
            find_and_set_tile_size((uintptr_t)d_course_dks_jungle_parkway_packed_dl_3E40, 0, D_802B87BC);
            find_and_set_tile_size((uintptr_t)d_course_dks_jungle_parkway_packed_dl_3EB0, 0, D_802B87BC);
            find_and_set_tile_size((uintptr_t)d_course_dks_jungle_parkway_packed_dl_3F30, 0, D_802B87BC);
            find_and_set_tile_size((uintptr_t)d_course_dks_jungle_parkway_packed_dl_36A8, 0, D_802B87BC);
            D_802B87C4 -= 20;
            if (D_802B87C4 < 0) {
                D_802B87C4 = 0xFF;
            }
            // d_course_dks_jungle_parkway_packed_dl_9880
            find_and_set_tile_size((uintptr_t)d_course_dks_jungle_parkway_packed_dl_9880, 0, D_802B87C4);
            evaluate_collision_players_palm_trees();
            break;
    }
}

void func_802969F8(void) {

    switch(gCurrentCourseId) {
        case COURSE_MOO_MOO_FARM:
            D_8015F702 = 0;
            D_8015F700 = 200;
            break;
        case COURSE_KOOPA_BEACH:
            D_8015F8E8 = -0.1f;
            D_8015F8E4 = 0.0f;
            break;
    }
}
