#include <ultra64.h>
#include <PR/os.h>
#include <macros.h>
#include <types.h>
#include <defines.h>
#include "flycam.h"

#include <camera.h>
#include "main.h"
#include <libc/math.h>
#include <common_structs.h>
#include "racing/collision.h"
#include "player_controller.h"
#include "code_80057C60.h"
#include "code_80005FD0.h"
#include "code_800029B0.h"
#include "hooks.h"
#include "render_player.h"
#include "render_courses.h"

// Yaw/pitch rotation sensitivity
#define SENSITIVITY_X 0.0003f
#define SENSITIVITY_Y 0.0003f

u32 mod_isFlycam = FALSE;
u32 fRankIndex = 0;
u32 fTargetPlayer = FALSE;
u32 fMode; // flycam mode should probably be an enum
u32 fModeInit = FALSE;
bool last_pressed = FALSE;

typedef struct {
    Vec3f pos;
    Vec3f lookAt;
    Vec3s rot; 
} FlycamSaveState;

FlycamSaveState fState;

void flycam_calculate_forward_vector(Camera* camera, Vec3f forwardVector);
void flycam_move_camera_forward(Camera* camera, struct Controller *controller, f32 distance);
void flycam_update(Camera* camera, struct Controller *controller);
void flycam_controller_manager(Camera *camera, struct Controller *controller, Player *player);
void flycam_target_player(Camera *camera, u32 playerIndex);
void flycam_move_camera_up(Camera* camera, struct Controller *controller, f32 distance);
void flycam_save_state(Camera *camera);
void flycam_load_state(Camera *camera);

HOOK(check_player_camera_collision, START, 0)
u16 ignore_for_flycam(bool* cancel, UNUSED Player *player, UNUSED Camera *camera, UNUSED f32 arg2, UNUSED f32 arg3) {
    if (mod_isFlycam) {
        *cancel = TRUE;
        return TRUE;
    }
}

HOOK(is_within_render_distance, START, 0)
f32 ignore_render_distance(bool* cancel, UNUSED Vec3f cameraPos, UNUSED Vec3f objectPos, UNUSED u16 orientationY, UNUSED f32 minDistance, UNUSED f32 fov, UNUSED f32 maxDistance){
    if (mod_isFlycam) {
        *cancel = TRUE;
        return 1.0;
    }
}

HOOK(load_surface_map, END, 0)
void over_load_surface_map(UNUSED uintptr_t addr, UNUSED struct UnkStruct_800DC5EC *arg1) {
    if (mod_isFlycam) {
        gDisplayListHead--; // remove gSPDisplayList(gDisplayListHead++, gfx[temp_v1]); instruction
        func_8029569C();
        return;
    }
}

/**
 * Controls
 * 
 * Forward: A
 * Backward: B
 * 
 * Go faster: Z
 * 
 * Up:       C-up
 * Down:     C-down
 * 
 * Targets players based on rank position
 * 
 * Target player: R-trig
 * Target next player: C-right
 * Target previous player: C-left
 * 
 * Switch camera modes:   D-pad left
 * 
 * Camera mode 1: Enter flycam at the player's position
 * Camera mode 2: Enter flycam at previous flycam spot
 * 
*/
HOOK(func_8001E45C, START, 0)
void flycam(bool* cancel, Camera *camera, Player *player, UNUSED s8 index) {
    struct Controller *controller = &gControllers[0];
    if (controller->buttonPressed & L_TRIG && last_pressed != (controller->buttonPressed & L_TRIG)) {
        last_pressed = controller->buttonPressed & L_TRIG;
        mod_isFlycam = !mod_isFlycam;

        // Don't use `bool = !bool` here as the game code can swap these on you.
        // Which will confuse the code. This forces it to always be correct
        if (mod_isFlycam) {
            player->type |= PLAYER_CPU;
        } else {
            player->type &= PLAYER_CPU;
        }

        gIsHUDVisible = !mod_isFlycam;

        if (mod_isFlycam) {

            if (fMode && fModeInit) {
                flycam_load_state(camera);
            } else {
                // !fMode or fMode not initialized
                flycam_target_player(camera, get_player_index_for_player(player));
            }

            return;
        } else {
            if(fMode) {
                flycam_save_state(camera);
            }
        }
    }

    last_pressed = controller->buttonPressed & L_TRIG;

    // Driving mode
    if (!mod_isFlycam) {
        *cancel = FALSE;
        return;
    }


    //if (player == gPlayerOne) { return; }

    //player->type &= ~PLAYER_HUMAN;
    //player->type |= PLAYER_HUMAN;

    if ((player->type & PLAYER_START_SEQUENCE)) { return; }

    flycam_controller_manager(camera, controller, player);

    *cancel = TRUE;
}

void flycam_save_state(Camera *camera) {
    fState.pos[0] = camera->pos[0];
    fState.pos[1] = camera->pos[1];
    fState.pos[2] = camera->pos[2];

    fState.lookAt[0] = camera->lookAt[0];
    fState.lookAt[1] = camera->lookAt[1];
    fState.lookAt[2] = camera->lookAt[2];

    fState.rot[0] = camera->rot[0];
    fState.rot[1] = camera->rot[1];
    fState.rot[2] = camera->rot[2];
    fModeInit = TRUE;
}

void flycam_load_state(Camera *camera) {
    camera->pos[0] = fState.pos[0];
    camera->pos[1] = fState.pos[1];
    camera->pos[2] = fState.pos[2];

    camera->lookAt[0] = fState.lookAt[0];
    camera->lookAt[1] = fState.lookAt[1];
    camera->lookAt[2] = fState.lookAt[2];

    camera->rot[0] = fState.rot[0];
    camera->rot[1] = fState.rot[1];
    camera->rot[2] = fState.rot[2];
}

void flycam_controller_manager(Camera *camera, struct Controller *controller, UNUSED Player *player) {

    if (controller->buttonPressed & U_JPAD) {
        fMode = !fMode;
    }

    // Target a player
    if (controller->buttonPressed & R_TRIG) {
        fTargetPlayer = !fTargetPlayer;
    }

    // Target next player
    if (controller->buttonPressed & L_CBUTTONS) {
        if (fRankIndex > 0) {
            fRankIndex--;
            camera->playerId = fRankIndex;
            D_800DC5EC->player = &gPlayers[fRankIndex];
        }
    }

    // Target previous player
    if (controller->buttonPressed & R_CBUTTONS) {
        if (fRankIndex < 7) {
            fRankIndex++;
            camera->playerId = fRankIndex;
            D_800DC5EC->player = &gPlayers[fRankIndex];
        }
    }

    // Target camera at chosen player
    if (fTargetPlayer) {
        flycam_target_player(camera, gGPCurrentRacePlayerIdByRank[fRankIndex]);
        // Don't run the other camera code.
        return;
    }

    // Rotation
    if (!fTargetPlayer) {
        if (controller->stickDirection != 0) {
            flycam_update(camera, controller);
        }
    }

    // Forward
    if (controller->button & A_BUTTON)  {
        flycam_move_camera_forward(camera, controller, 3.0f);
    }

    // Backward     B button but not A button.
    if (controller->button & B_BUTTON && !(controller->button & A_BUTTON))  {
        flycam_move_camera_forward(camera, controller, -3.0f);
    }

    // Up
    if (controller->button & U_CBUTTONS) {
        flycam_move_camera_up(camera, controller, 2.0f);
    }
    // Up
    if (controller->button & D_CBUTTONS) {
        flycam_move_camera_up(camera, controller, -2.0f);
    }
}

// Calculates the forward direction vector based on camera orientation
void flycam_calculate_forward_vector(Camera* camera, Vec3f forwardVector) {
    f32 pitch = (camera->rot[2] / 65535.0f) * 360.0f; // Convert pitch from 0-65535 to degrees
    f32 yaw = (camera->rot[1] / 65535.0f) * 360.0f;   // Convert yaw from 0-65535 to degrees

    // Convert degrees to radians
    pitch = pitch * M_PI / 180.0f;
    yaw = yaw * M_PI / 180.0f;

    forwardVector[0] = -sinf(yaw) * cosf(pitch);
    forwardVector[1] = -sinf(pitch);
    forwardVector[2] = cosf(yaw) * cosf(pitch);
}

// Function to move the camera forward
void flycam_move_camera_forward(Camera* camera, struct Controller *controller, f32 distance) {
    Vec3f forwardVector;
    f32 length;
    flycam_calculate_forward_vector(camera, forwardVector);

    if (controller->button & Z_TRIG) {
        distance *= 3;
    }

    // Normalize the forward vector
    length = sqrtf(forwardVector[0] * forwardVector[0] + forwardVector[1] * forwardVector[1] + forwardVector[2] * forwardVector[2]);
    forwardVector[0] /= length;
    forwardVector[1] /= length;
    forwardVector[2] /= length;

    // Move the camera's position along the forward vector while considering its up vector
    camera->pos[0] += forwardVector[0] * distance;
    camera->pos[1] += forwardVector[1] * distance;
    camera->pos[2] += forwardVector[2] * distance;

    // Optionally, you can also adjust the lookAt point to maintain the same relative position
    camera->lookAt[0] += forwardVector[0] * distance;
    camera->lookAt[1] += forwardVector[1] * distance;
    camera->lookAt[2] += forwardVector[2] * distance;
}

// Function to move the camera forward
void flycam_move_camera_up(Camera* camera, struct Controller *controller, f32 distance) {
    // Check if the Z button is pressed (for faster movement)
    if (controller->button & Z_TRIG) {
        distance *= 3;
    }

    // Move the camera's position along its up vector (Y-axis)
    camera->pos[1] += distance;

    // Optionally, adjust the lookAt point to maintain the same relative position
    camera->lookAt[1] += distance;
}

// Update camera rotation and lookAt point based on input
void flycam_update(Camera* camera, struct Controller *controller) {
    // Calculate yaw (horizontal movement)
    f32 yawChange = controller->rawStickX * SENSITIVITY_X;
    f32 pitchChange = controller->rawStickY * SENSITIVITY_Y;
    Vec3f forwardVector;

    func_802ADDC8(&camera->unk_54, 50, camera->pos[0], camera->pos[1], camera->pos[2]);

    camera->rot[1] += (short)(yawChange * 65535.0f / (2 * M_PI)); // Convert radians to 0-65535 range

    camera->rot[2] += (short)(-pitchChange * 65535.0f / (2 * M_PI)); // Convert radians to 0-65535 range

    if (camera->rot[2] > 15999) {
        camera->rot[2] = 15999;
    } else if (camera->rot[2] < -15999) {
        camera->rot[2] = -15999;
    }

    // Update the lookAt point based on the new orientation
    flycam_calculate_forward_vector(camera, forwardVector);
    camera->lookAt[0] = camera->pos[0] + forwardVector[0];
    camera->lookAt[1] = camera->pos[1] + forwardVector[1];
    camera->lookAt[2] = camera->pos[2] + forwardVector[2];
}

void flycam_target_player(Camera *camera, u32 playerIndex) {
    Player *player = &gPlayers[playerIndex];

    // Calculate the direction from the player to the camera
    f32 dirX = player->pos[0] - camera->pos[0];
    f32 dirY = player->pos[1] - camera->pos[1];
    f32 dirZ = player->pos[2] - camera->pos[2];

    // Normalize the direction vector (if needed)
    f32 length = sqrtf(dirX * dirX + dirY * dirY + dirZ * dirZ);
    if (length > 0) {
        dirX /= length;
        dirY /= length;
        dirZ /= length;
    }

    // Update the camera's look-at direction
    camera->lookAt[0] = camera->pos[0] + dirX;
    camera->lookAt[1] = camera->pos[1] + dirY;
    camera->lookAt[2] = camera->pos[2] + dirZ;
}
