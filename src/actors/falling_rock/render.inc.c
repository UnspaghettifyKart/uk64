#include <actors.h>
#include <main.h>
#include "courses/choco_mountain/course_data.h"

/**
 * @brief Renders the falling rock actor.
 * Actor used in Choco Mountain.
 * 
 * @param camera 
 * @param rock 
 */
void render_actor_falling_rock(Camera *camera, struct FallingRock *rock) {
    Vec3s sp98;
    Vec3f sp8C;
    Mat4 sp4C;
    f32 temp_f0;
    UNUSED s32 pad[4];

    if (rock->respawnTimer != 0) { return; }

    temp_f0 = is_within_render_distance(camera->pos, rock->pos, camera->rot[1], 400.0f, gCameraZoom[camera - camera1], 4000000.0f);

    if (temp_f0 < 0.0f) { return; }

    if (temp_f0 < 250000.0f) {

        if (rock->unk30.unk34 == 1) {
            sp8C[0] = rock->pos[0];
            sp8C[2] = rock->pos[2];
            temp_f0 = func_802ABE30(sp8C[0], rock->pos[1], sp8C[2], rock->unk30.unk3A);
            sp98[0] = 0;
            sp98[1] = 0;
            sp98[2] = 0;
            sp8C[1] = temp_f0 + 2.0f;
            mtxf_pos_rotation_xyz(sp4C, sp8C, sp98);
            if (render_set_position(sp4C, 0) == 0) {
                return;
            }
            gSPDisplayList(gDisplayListHead++, d_course_choco_mountain_dl_6F88);
        }
    }
    mtxf_pos_rotation_xyz(sp4C, rock->pos, rock->rot);
    if (render_set_position(sp4C, 0) == 0) {
        return;
    }
    gSPDisplayList(gDisplayListHead++, d_course_choco_mountain_dl_falling_rock);
}
