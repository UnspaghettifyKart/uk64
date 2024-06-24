# Hook
With hook you can execute your function at the same time then function in game without modify src directory. This also allow to replace a function and multiple mod do that in the same time. With the priority system you add compatibility for let other hook execute before or after your function.

## Example
I want to replace check_player_camera_collision only when my mod are enable so a way to do it is:
```c
HOOK(check_player_camera_collision, AT(FUNCTION_CALL), TRUE, 0)
u16 ignore(bool* cancel, UNUSED Player *player, UNUSED Camera *camera, UNUSED f32 arg2, UNUSED f32 arg3) {
    if (mymod_enable) {
        *cancel = TRUE;
        return 1;
    }
}
```
so we have the line before to say we when a hook, who will be insert at check_player_camera_collision function, at the start of function with a priority of zero. we can see in argument he take all same argument then before but he have one more extra argument who are `bool* cancel`. `cancel` can say if we stop the execution of chain of hook. the code who are generate in back-end look like that:
```c
u16 check_player_camera_collision(Player *player, Camera *camera, f32 arg2, f32 arg3) {
    bool cancel = FALSE;
    u16 ret;
    ret = ignore(&cancel, player, camera, arg2, arg3);
    if (cancel) { return ret; }
    ret = other_hook(&cancel, player, camera, arg2, arg3);
    if (cancel) { return ret; }
    ret = original_check_player_camera_collision(player, camera, arg2, arg3);
    return ret;
}
```
so when you set this cancel to true other_hook will not be execute but if you change the priority to be more low then you function will be execute after other_hook.