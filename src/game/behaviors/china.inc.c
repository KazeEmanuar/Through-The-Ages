// dolphin.c.inc
#include "sm64.h"
#include "types.h"
//#include "game/game.h"
#include "game/level_update.h"
#include "dialog_ids.h"
#include "game/object_helpers.h"
//#include "game/kaze_library.h"
#include "seq_ids.h"
#include "game/camera.h"
#include "engine/math_util.h"
#include "buffers/buffers.h"
#include "game/segment2.h"
#include "game/ingame_menu.h"
#include "audio/external.h"
#include "engine/surface_collision.h"

#define m gMarioState
#define o gCurrentObject
#pragma intrinsic(sqrtf)

void bouncylamp(void) {
    switch (o->oAction) {
        case 0:
            cur_obj_init_animation(0);
            // o->oPosY = o->oHomeY + sins(o->oTimer * 0x800) * 10.0f;
            // wait for mario close
            if (obj_check_if_collided_with_object(o, gMarioObject)) {
                o->oAction = 1;
                set_mario_action(m, ACT_SPECIAL_TRIPLE_JUMP, 0);
                m->vel[1] = 80.f;
                cur_obj_play_sound_2(SOUND_OBJ_BOO_LAUGH_SHORT);
            }
            rotateTowardsMario(0x400);
            break;
        case 1:
            cur_obj_init_animation(1);
            if (cur_obj_check_if_at_animation_end()) {
                o->oAction = 0;
                o->oIntangibleTimer = 0;
            }
            if (o->oTimer > 20) {
                rotateTowardsMario(0x400);
            }
            // animate
            break;
    }
}

u8 gongOrder[5] = { 4, 1, 3, 2, 5 };
u8 gongID = 0;

extern u8 pitchChange;
void bellCode(void) {
    switch (o->oAction) {
        case 0:
            o->oAction = 1;
            cur_obj_scale(1.1f - o->oBehParams2ndByte * 0.1f);
            o->hitboxRadius *= 1.1f - o->oBehParams2ndByte * 0.1f;
            o->hitboxHeight *= 1.1f - o->oBehParams2ndByte * 0.1f;
            o->hitboxDownOffset *= 1.1f - o->oBehParams2ndByte * 0.1f;
            break;
        case 1:
            if (abs_angle_diff(gMarioState->faceAngle[1], obj_angle_to_object(gMarioState->marioObj, o))
                < 0x2000) {
                if (lateral_dist_between_objects(gMarioState->marioObj, o)
                    < (o->hitboxRadius + 150.f)) {
                    if ((gMarioState->pos[1] < (o->oPosY - o->hitboxDownOffset + o->hitboxHeight))) {
                        if ((gMarioState->pos[1] > (o->oPosY - o->hitboxDownOffset))) {
                            if (gMarioState->action & ACT_FLAG_ATTACKING) {
                                o->oAction = 2;
                                gMarioState->forwardVel = -30.f;
                                cur_obj_play_sound_2(SOUND_ACTION_HIT_3);
                                pitchChange = o->oBehParams2ndByte - 1;
                                cur_obj_play_sound_2(SOUND_GENERAL_BELL);
                                if (gongID < 5) {
                                    if (o->oBehParams2ndByte == gongOrder[gongID]) {
                                        gongID++;
                                        if (gongID == 5) {
                                            gongID = 0;
                                            cur_obj_nearest_object_with_behavior(bhvDragonBridge)
                                                ->oAction = 1;
                                        }
                                    } else {
                                        gongID = 0;
                                        if (o->oBehParams2ndByte == gongOrder[gongID]) {
                                            gongID++;
                                        }
                                    }
                                }
                                if ((obj_angle_to_object(o, gMarioObject) - o->oFaceAngleYaw + 0x4000)
                                    & 0x8000) {
                                    o->oAngleVelPitch = -0x300;
                                } else {
                                    o->oAngleVelPitch = 0x300;
                                }
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            if (o->oTimer > 90) {
                o->oAction = 1;
            }
            break;
    }
    o->oFaceAnglePitch += o->oAngleVelPitch;
    o->oAngleVelPitch -= o->oFaceAnglePitch * 0.05f;
    o->oAngleVelPitch *= 0.98f;
}
void gongcode(void) {
    struct Object *spawn;
    if (!o->oHiddenBlueCoinSwitch) {
        o->oHiddenBlueCoinSwitch = spawn_object(o, 0, bhvGongSpawn);
    }
    if (gMarioState->wall && (gMarioState->wall->object == o->oHiddenBlueCoinSwitch)) {
        if (gMarioState->forwardVel > 10.f) {
            o->oTimer = 0;
            if ((obj_angle_to_object(o, gMarioObject) - o->oFaceAngleYaw + 0x4000) & 0x8000) {
                o->oAngleVelPitch = gMarioState->forwardVel * -35.f;
            } else {
                o->oAngleVelPitch = gMarioState->forwardVel * 35.f;
            }
        }
    }
    o->oFaceAnglePitch += o->oAngleVelPitch;
    o->oAngleVelPitch -= o->oFaceAnglePitch * 0.05f;
    o->oAngleVelPitch *= 0.98f;
    if ((absi(o->oAngleVelPitch) + absi(o->oFaceAnglePitch)) > 0x100) {
        if (o->oTimer < 50) {
            play_sound(SOUND_GENERAL2_GONG, gDefaultSoundArgs);
        }
    }
    if (absi(o->oFaceAnglePitch) > 0x1000) {
        if (!(o->oBehParams & 0x0000FF00)) {
            o->oBehParams |= 0x0000FF00;
            spawn = spawn_object(o, MODEL_BLUE_COIN, bhvMrIBlueCoin);
            spawn->oMoveAngleYaw = obj_angle_to_object(o, gMarioObject);
        }
    }
}

// dog stands still until mario gets close. then he runs at mario while adjusting his face angle. mario
// has to jump over him to dodge
void foodogcode(void) {
    switch (o->oAction) {
        case 0:
            // stand still
            o->oDamageOrCoinValue = 3;
            cur_obj_init_animation(0);
            o->oOpacity = o->oFaceAngleYaw;
            o->oDrawingDistance = 100000.f;
            if (abs_angle_diff(obj_angle_to_object(o, gMarioObject), o->oFaceAngleYaw)
                < (0x7f00 - o->oDistanceToMario * 8)) {
                o->oAction++;
                cur_obj_play_sound_2(SOUND_GENERAL_SHAKE_COFFIN);
            }
            o->header.gfx.unk38.animFrame = 0;
            break;
        case 1:
            if (o->header.gfx.unk38.animFrame >= 20) {
                o->oAction++;
                cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
            }
            // little get up jump
            break;
        case 2:
            // run forward
            if (o->oForwardVel < 38.f) {
                o->oForwardVel += 4.f;
            }
            if (abs_angle_diff(o->oMoveAngleYaw, o->oOpacity) < 0x2000) {
                rotateTowardsMario((4000.f - o->oDistanceToMario) / 25);
            }
            if (o->oVelY < -15.f) {
                if (o->header.gfx.unk38.animFrame == 45) {
                    o->header.gfx.unk38.animFrame = 44;
                }
            }
            if (o->oPosY < (o->oHomeY - 2500.f)) {
                o->oAction++;
            }
            break;
        case 3:
            // disappear wait for respawn
            o->header.gfx.unk38.animFrame = 0;
            cur_obj_hide();
            if (cur_obj_lateral_dist_from_mario_to_home() > 7000.f) {
                o->oAction = 0;
                o->oFaceAngleYaw = o->oOpacity;
                o->oMoveAngleYaw = o->oOpacity;
                o->oPosX = o->oHomeX;
                o->oPosY = o->oHomeY;
                o->oPosZ = o->oHomeZ;
                o->oForwardVel = 0;
                cur_obj_unhide();
            }
            break;
    }
    if ((o->header.gfx.unk38.animFrame == 45) || (o->header.gfx.unk38.animFrame == 49)) {
        play_sound(SOUND_OBJ_BULLY_WALKING, gDefaultSoundArgs);
    }
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(78);
    if (cur_obj_check_if_at_animation_end()) {
        o->header.gfx.unk38.animFrame = 44;
    }
}

extern struct Object *find_obj_with_bparam(const BehaviorScript *behavior, u32 bParam);
void pagodagate(void) {
    if (o->oAction) {
        o->oPosY -= 10.f;
        if (o->oTimer > 80) {
            obj_mark_for_deletion(o);
        }
    } else {
        if (find_obj_with_bparam(bhvFloorSwitchAnimatesObject, o->oBehParams & 0xff)->oAction) {
            o->oAction = 1;
        }
    }
    load_object_collision_model();
}
extern void obj_spit_fire(s16 relativePosX, s16 relativePosY, s16 relativePosZ, f32 scale, s32 model,
                          f32 startSpeed, f32 endSpeed, s16 movePitch);
void firelampcode(void) {
    rotateTowardsMario(0x600);
    switch (o->oAction) {
        case 0:
            if (o->oDistanceToMario < 1250.f) {
                o->oAction = 1;
                o->header.gfx.unk38.animFrame = 0;
            }
            break;
        case 1:
            if (o->oDistanceToMario > 1250.f) {
                o->oAction = 0;
            }
            if (cur_obj_check_if_at_animation_end()) {
                o->oAction = 0;
            }
            if (o->header.gfx.unk38.animFrame == 18) {
                obj_spit_fire(
                    /*relativePos*/ 0, -50, 20,
                    /*scale      */ 2.5f,
                    /*model      */ MODEL_RED_FLAME_SHADOW,
                    /*startSpeed */ 40.0f,
                    /*endSpeed   */ 30.0f,
                    /*movePitch  */ 0x0800);
            }
            break;
    }
}

u8 checkOOb() {
    if (o->oPosX < (o->oHomeX - 2195.f)) {
        return 1;
    }
    if (o->oPosX > (o->oHomeX + 2195.f)) {
        return 1;
    }
    if (o->oPosZ < (o->oHomeZ - 2195.f)) {
        return 1;
    }
    if (o->oPosZ > (o->oHomeZ + 2195.f)) {
        return 1;
    }
    return 0;
}

u8 checkMarioOOb() {
    if (gMarioState->marioObj->oPosX < (o->oHomeX - 2195.f)) {
        return 1;
    }
    if (gMarioState->marioObj->oPosX > (o->oHomeX + 2195.f)) {
        return 1;
    }
    if (gMarioState->marioObj->oPosZ < (o->oHomeZ - 2195.f)) {
        return 1;
    }
    if (gMarioState->marioObj->oPosZ > (o->oHomeZ + 2195.f)) {
        return 1;
    }
    return 0;
}
u8 stepsounds = 0;
// oBobombBuddyPosXCopy
// 2200 coordinates and he falls off
void chinabosscode(void) {
    switch (o->oAction) {
        case 0:
            // wait mario for init
            cur_obj_init_animation(0);
            o->header.gfx.unk38.animFrame = 18;
            if (o->oDistanceToMario < 1250.f) {
                o->oAction++;
                o->oHealth = 0;
            }
            break;
        case 1:
            // talk to mario
            cur_obj_init_animation(0);
            o->header.gfx.unk38.animFrame = 18;
            if (talkToMario(149)) {
                o->oAction++;
                sequence_player_unlower(SEQ_PLAYER_LEVEL, 60);
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
            }
            break;
        case 2:
            // walk idle
            if (o->header.gfx.unk38.animFrame > 18) {
                if (!(stepsounds & 1)) {
                    cur_obj_play_sound_2(SOUND_OBJ_UKIKI_STEP_DEFAULT);
                    stepsounds |= 1;
                }
            } else {
                stepsounds = 0;
            }
            if (o->header.gfx.unk38.animFrame > 58) {
                if (!(stepsounds & 2)) {
                    cur_obj_play_sound_2(SOUND_OBJ_UKIKI_STEP_DEFAULT);
                    stepsounds |= 2;
                }
            }
#define FRAMESPEED 9.f
            cur_obj_init_animation(0);
            if (!o->oTimer) {
                o->oOpacity = obj_angle_to_object(o, gMarioState->marioObj) - 0x4000;
            }
            o->oBobombBuddyPosXCopy = o->oHomeX + sins(o->oOpacity) * 1600.f;
            o->oBobombBuddyPosZCopy = o->oHomeZ + coss(o->oOpacity) * 1600.f;
            o->oYoshiTargetYaw =
                atan2s(o->oBobombBuddyPosZCopy - o->oPosZ, o->oBobombBuddyPosXCopy - o->oPosX);
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oYoshiTargetYaw, 0x400);
            o->oForwardVel = approach_f32_symmetric(
                o->oForwardVel, (coss(o->oMoveAngleYaw - o->oYoshiTargetYaw) + 1.f) * 15.f, 2.0f);
            o->oOpacity += 0x00E0;
            o->header.gfx.unk38.animFrame += o->oForwardVel / FRAMESPEED;
            if (o->oTimer > (80 - o->oHealth * 20)) {
                if (!(random_u16() % (40 - o->oHealth * 10))) {
                    if (checkMarioOOb()) {
                        o->oTimer = 0;
                    } else {
                        if (random_u16() & 1) {
                            o->oAction = 3;
                        } else {
                            o->oAction = 6;
                            o->oVelY = 32.f;
                            o->oMoveAngleYaw = o->oAngleToMario;
#define AIRFRAME 20.f
                            o->oForwardVel =
                                lateral_dist_between_objects(o, gMarioState->marioObj) / AIRFRAME;
                        }
                    }
                }
            }
            if (o->oTimer > 5) {
                if (checkOOb()) {
                    o->oAction = 4;
                }
            }
            break;
        case 3:
            cur_obj_init_animation(3);
            if (o->header.gfx.unk38.animFrame == 12) {
                cur_obj_play_sound_2(SOUND_GENERAL_SWISH_AIR);
            }
            if (o->header.gfx.unk38.animFrame == 25) {
                cur_obj_play_sound_2(SOUND_GENERAL_SWISH_AIR);
            }
            if (o->header.gfx.unk38.animFrame >= 32) {
                o->header.gfx.unk38.animFrame = 7;
            }
            // attack in a line (turning radius depends on dmg taken)
            o->oYoshiTargetYaw = o->oAngleToMario;
            if (o->oTimer > 10) {
                o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oYoshiTargetYaw,
                                                          0x100 + o->oHealth * 0x100);
            } else {
                o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oYoshiTargetYaw, 0x600);
            }
            o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 40.f, 1.0f);
            if (o->oTimer > 270) {
                o->oAction = 2;
            }
            if (checkOOb()) {
                o->oAction = 4;
            }
            break;
        case 4:
            if (o->oTimer < 10) {
                o->oForwardVel *= 0.9f;
            } else if (o->oTimer == 10) {
                o->oForwardVel = 0;
            }
            cur_obj_init_animation(1);
            o->oMoveAngleYaw =
                approach_s16_symmetric(o->oMoveAngleYaw, cur_obj_angle_to_home() + 0x8000, 0x600);
            if (cur_obj_check_if_at_animation_end()) {
                o->oAction = 2;
            }
            if (o->header.gfx.unk38.animFrame == 125) {
                o->oVelY = 70.f;
                o->oForwardVel = -40.f;
                cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
            }
            // fall off arena
            if (o->oInteractStatus & (INT_STATUS_INTERACTED | INT_STATUS_WAS_ATTACKED)) {
                if (o->oTimer > 30) {
                    o->oAction = 5;
                    o->oHealth++;
                    if (o->oHealth == 3) {
                        create_sound_spawner(SOUND_OBJ_KING_WHOMP_DEATH);
                        spawn_mist_particles_variable(0, 0, 200.0f);
                        spawn_triangle_break_particles(20, 138, 3.0f, 4);
                        cur_obj_shake_screen(SHAKE_POS_SMALL);
                        spawn_default_star(o->oHomeX, o->oHomeY + 200.f, o->oHomeZ);
                        stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
                        o->activeFlags = 0;
                    }
                }
            }
            break;
        case 5:
            if (o->header.gfx.unk38.animFrame < 120) {
                o->header.gfx.unk38.animFrame = 120;
            }
            if (o->header.gfx.unk38.animFrame == 125) {
                o->oVelY = 70.f;
                o->oForwardVel = -40.f;
                cur_obj_play_sound_2(SOUND_OBJ_KING_BOBOMB_JUMP);
            }
            if (cur_obj_check_if_at_animation_end()) {
                o->oAction = 2;
            }
            // damaged
            break;
        case 6:
            // spin attacks
            // todo: make it so he cant go out of bound
            o->oMoveAngleYaw =
                approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x40 + o->oHealth * 0x20);
            o->oVelY += 2.f;
            if (o->header.gfx.unk38.animFrame == 15) {
                cur_obj_play_sound_2(SOUND_GENERAL_SWISH_AIR);
            }
            cur_obj_init_animation(2);
            if (o->oMoveFlags & OBJ_MOVE_LANDED) {
                o->oSubAction = 1;
            }
            if (!o->oSubAction) {
                if (o->header.gfx.unk38.animFrame >= 24) {
                    o->header.gfx.unk38.animFrame = 4;
                }
            } else {
                o->oForwardVel *= 0.8f;
            }
            if (o->header.gfx.unk38.animFrame >= 34) {
                o->oAction = 2;
            }
            if (o->oPosX < (o->oHomeX - 2100.f)) {
                o->oPosX = o->oHomeX - 2100.f;
            }
            if (o->oPosX > (o->oHomeX + 2100.f)) {
                o->oPosX = o->oHomeX + 2100.f;
            }
            if (o->oPosZ < (o->oHomeZ - 2100.f)) {
                o->oPosZ = o->oHomeZ - 2100.f;
            }
            if (o->oPosZ > (o->oHomeZ + 2100.f)) {
                o->oPosZ = o->oHomeZ + 2100.f;
            }
            break;
    }
    switch (o->oAction) {
        case 0:
        case 1:
        case 5:
            o->oInteractType = INTERACT_IGLOO_BARRIER;
            break;
        case 2:
        case 6:
            o->oInteractType = INTERACT_DAMAGE;
            o->oDamageOrCoinValue = 2;
            break;
        case 4:
            o->oInteractType = INTERACT_BOUNCE_TOP;
            o->oDamageOrCoinValue = 2;
            break;
    }
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(78);
    o->oInteractStatus = 0;
}

extern const Collision dragonbridge2_collision[];
void dragonbridgecode(void) {
    u32 *coll2 = segmented_to_virtual(dragonbridge2_collision);
    switch (o->oAction) {
        case 0:
            o->header.gfx.unk38.animFrame = 0;
            break;
        case 1:
            if (gMarioState->pos[1] <= gMarioState->floorHeight) {
                if (set_mario_npc_dialog(2) == 2 && cutscene_object(CUTSCENE_STAR_SPAWN, o) == 1) {
                    o->oAction++;
                    play_puzzle_jingle();
                }
            }
            break;
        case 2:
            cur_obj_init_animation(0);
            if (cur_obj_check_if_at_animation_end()) {
                o->oAction = 3;
                o->oHomeX = gMarioState->pos[0] + sins(0) * -750.f;
                o->oHomeZ = gMarioState->pos[2] + coss(0) * -750.f;
                o->oHomeY = gMarioState->pos[1] + 300.f;
                gCurrentObject->collisionData = coll2;
            }
            if (o->header.gfx.unk38.animFrame == 183) {
                o->oForwardVel = 60.f;
                o->oVelY = 30.f;
                create_sound_spawner(SOUND_OBJ2_BOWSER_ROAR);
                spawn_mist_particles_variable(0, 0, 200.0f);
                spawn_triangle_break_particles(20, 138, 3.0f, 4);
            }
            if ((o->header.gfx.unk38.animFrame > 170) && (o->header.gfx.unk38.animFrame < 183)) {
                cur_obj_shake_screen(SHAKE_ENV_EXPLOSION);
            }
            break;
        case 3:
            if ((o->header.gfx.unk38.animFrame > 298)) {
                o->header.gfx.unk38.animFrame = 219;
            }
            o->oVelY = approach_f32_symmetric(o->oVelY, -15.f, 0.75f);
            if (o->oTimer > 200) {
                gObjCutsceneDone = TRUE;
                if (cutscene_object(CUTSCENE_STAR_SPAWN, o) == -1) {
                    set_mario_npc_dialog(0);
                    o->oAction = 4;
                }
            }
            o->oPosY = approach_f32_symmetric(o->oPosY, o->oHomeY, 2.f);
            o->oYoshiTargetYaw = atan2s(o->oHomeZ - o->oPosZ, o->oHomeX - o->oPosX);
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oYoshiTargetYaw, 0x00AB);
            o->oForwardVel = approach_f32_symmetric(
                o->oForwardVel, (coss(o->oMoveAngleYaw - o->oYoshiTargetYaw) + 1.f) * 23.f, 0.25f);
            break;
        case 4:
            if ((o->header.gfx.unk38.animFrame > 298)) {
                o->header.gfx.unk38.animFrame = 219;
            }
            o->oPosY = approach_f32_symmetric(o->oPosY, o->oHomeY, 15.f);
            if (o->oTimer > 50) {
                o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 0, 0.5f);
            }
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, 0x4000, 0x00A4);
            if (cur_obj_is_mario_on_platform()) {
                o->oAction++;
                level_trigger_warp(m, WARP_OP_WARP_FLOOR);
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x14, 0xff, 0xa0, 0xa0);
                sSourceWarpNodeId = 0x11;
            }
            break;
    }
    load_object_collision_model();
    cur_obj_move_xz_using_fvel_and_yaw();
    o->oPosY += o->oVelY;
}