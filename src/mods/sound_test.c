#include "sound_test.h"
#include "sounds.h"
#include <PR/os.h>
#include "main.h"
#include <macros.h>
#include "src/audio/external.h"

u32 soundTestArr[] = {
    SOUND_MENU_OK_CLICKED,
    SOUND_MENU_CURSOR_MOVE,
    SOUND_MENU_GO_BACK,
    SOUND_MENU_STEREO,
    SOUND_MENU_HEADPHONES,
    SOUND_MENU_MONO,
    SOUND_MENU_FILE_NOT_FOUND,
    SOUND_MENU_SELECT,
    SOUND_MENU_EXPLOSION,
    SOUND_INTRO_ENTER_MENU,
    SOUND_MENU_OPTION,
    SOUND_MENU_DATA,
    SOUND_MENU_GP,
    SOUND_MENU_VERSUS,
    SOUND_MENU_TIME_TRIALS,
    SOUND_MENU_BATTLE,
    SOUND_MENU_SELECT_LEVEL,
    SOUND_MENU_OK,
    SOUND_MENU_SELECT_PLAYER,
    SOUND_MENU_SELECT_MAP,
    SOUND_ACTION_PING,
    SOUND_ACTION_REV_ENGINE,
    SOUND_ACTION_REV_ENGINE_2,
    SOUND_INTRO_WELCOME,
    SOUND_CEREMONY_CONGRATULATION,
    SOUND_CEREMONY_BALLOON_POP,
    SOUND_CEREMONY_FISH,
    SOUND_CEREMONY_FISH_2,
    SOUND_CEREMONY_SHOOT_TROPHY,
    SOUND_CEREMONY_PODIUM,
    SOUND_CEREMONY_TROPHY,
    SOUND_CREDITS_FAREWELL,
    SOUND_ACTION_COUNTDOWN_LIGHT,
    SOUND_ACTION_GREEN_LIGHT,
    SOUND_ACTION_GO_BACK_2,
    SOUND_ACTION_UNKNOWN_CONFIRMATION,
    0x4900801C,
    0x49009009,
    0x49018008,
    0x49008017,
    0x49008015,
    0x49008000,
    0x4900801B,
    0x49008016,
    0x49008001,
    0x4900FF07,
    0x49008002,
    0x49008005,
    SOUND_ACTION_CONTINUE_UNKNOWN,
};

s32 soundTestIndex = 0;
bool mod_soundTestActive = FALSE;

/**
 * Press R at any menu to loop through the various sound effects.
 * todo: Implement play_sound if possible.
*/
void mod_sound_test(void) {
    struct Controller *controller = &gControllers[0];

    if (controller->buttonPressed & R_TRIG) {
        play_sound2(soundTestArr[soundTestIndex]);
        soundTestIndex += 1;
        if (soundTestIndex >= ARRAY_COUNT(soundTestArr) - 1) { soundTestIndex = 0; } // wrap back around.
    }
}
