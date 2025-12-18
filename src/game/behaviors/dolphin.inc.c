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
#include "audio/load.h"
#include "engine/surface_collision.h"
#include "game/object_list_processor.h"

#define m gMarioState
#define o gCurrentObject
#pragma intrinsic(sqrtf)
// uses wallhitboxradius set by behav cmd
void move_obj_with_physics(u8 clampFloor) {
    f32 bounciness = o->oBounciness;
    gCurrentObject->oVelY += gCurrentObject->oGravity;
    if (gCurrentObject->oVelY < -70.0f) {
        gCurrentObject->oVelY = -70.0f;
    }
    gCurrentObject->oPosY += gCurrentObject->oVelY;
    gCurrentObject->oMoveFlags &= ~OBJ_MOVE_ON_GROUND;
    if ((gCurrentObject->oPosY < find_floor_height(o->oPosX, o->oPosY + 70.f, o->oPosZ))
        && clampFloor) {
        o->oPosY = find_floor_height(o->oPosX, o->oPosY + 70.f, o->oPosZ);
        o->oVelY = o->oVelY * bounciness / 100.0f;
        gCurrentObject->oMoveFlags |= OBJ_MOVE_ON_GROUND;
    }
    o->oPosX += o->oForwardVel * sins(o->oMoveAngleYaw);
    o->oPosZ += o->oForwardVel * coss(o->oMoveAngleYaw);
    // wall collision
    cur_obj_resolve_wall_collisions();
}

s16 rotateTowardsMario(int speed) {
    o->oMoveAngleYaw =
        approach_s16_symmetric(o->oMoveAngleYaw, obj_angle_to_object(o, gMarioObject), speed);
}

void offsetChildByFloat(struct Object *child, struct Object *parent, float yOffset, float horizOffset) {
    child->oPosY = parent->oPosY + yOffset;
    child->oPosX = parent->oPosX + horizOffset * sins(parent->oMoveAngleYaw);
    child->oPosZ = parent->oPosZ + horizOffset * coss(parent->oMoveAngleYaw);
}


u8 talkToMario2(int dialogID, int actionArg) {
    return cur_obj_update_dialog_with_cutscene(actionArg, 1, CUTSCENE_DIALOG, dialogID);
}

u8 talkToMarioNoRotation2(int dialogID, int actionArg) {
    return cur_obj_update_dialog_with_cutscene(actionArg, 0, CUTSCENE_DIALOG, dialogID);
}

u8 askMario2(int dialogID, u8 rotate, int actionArg) {
    return cur_obj_update_dialog_with_cutscene(actionArg, rotate, CUTSCENE_RACE_DIALOG, dialogID);
}
u8 talkToMario(int dialogID) {
    return cur_obj_update_dialog_with_cutscene(2, 1, CUTSCENE_DIALOG, dialogID);
}

u8 talkToMarioNoRotation(int dialogID) {
    return cur_obj_update_dialog_with_cutscene(3, 0, CUTSCENE_DIALOG, dialogID);
}

u8 askMario(int dialogID, u8 rotate) {
    return cur_obj_update_dialog_with_cutscene(2, rotate, CUTSCENE_RACE_DIALOG, dialogID);
}

#define MAXX 12000.f
#define MINX -12000.f
#define CONVERGE -1300.f
void dolphinswimcode(void) {
    if ((save_file_get_total_star_count(gCurrSaveFileNum - 1, 0, 0x18) < 12)
        || (!(save_file_get_star_flags(gCurrSaveFileNum - 1, gCurrCourseNum - 1) & 0x02))) {
        obj_mark_for_deletion(o);
        return;
    }
    o->oForwardVel = 48.f;
    if (o->oSubAction) {
        o->oOpacity++;
        if (o->oOpacity == 25) {
            cur_obj_init_animation(1);
            o->oSubAction = 0;
            spawn_object(o, MODEL_WATER_SPLASH, bhvWaterSplash);
        }
        o->oVelY -= 4.0f;
    } else {
        o->oOpacity = 0;
        o->oVelY = approach_f32_symmetric(o->oVelY, 0, 3.0f);
        o->oPosY = approach_f32_symmetric(o->oPosY, CONVERGE, 5.0f);
        if ((o->oPosY + 100.f) > CONVERGE) {
            if (!(random_u16() & 0x3f)) {
                o->oSubAction = 1;
                spawn_object(o, MODEL_WATER_SPLASH, bhvWaterSplash);
                o->oVelY = 50.f;
                cur_obj_init_animation(0);
            }
        }
    }
    if (!o->oFreePointer1) {
        o->oFreePointer1 = spawn_object(o, 0, bhvHitbox);
        o->oFreePointer2 = spawn_object(o, 0, bhvHitbox);
        o->oFreePointer3 = spawn_object(o, 0, bhvHitbox);
    }
    move_obj_with_physics(1);
    offsetChildByFloat(o->oFreePointer1, o, 0.0f, 100.f);
    offsetChildByFloat(o->oFreePointer2, o, 0.0f, 10.f);
    offsetChildByFloat(o->oFreePointer3, o, 0.0f, -90.f);
    if (o->oPosX > MAXX) {
        o->oPosX = MINX;
    }
    if (o->oPosX < MINX) {
        o->oPosX = MAXX;
    }
    if (o->oPosZ > MAXX) {
        o->oPosZ = MINX;
    }
    if (o->oPosZ < MINX) {
        o->oPosZ = MAXX;
    }
}
// spawn around mario, float slowly across the screen
void sleepcloud(void) {
    f32 dist;
    s16 angle;
    switch (o->oAction) {
        case 0:
            o->oForwardVel = random_float() * 10.f + 10.f;
            // generate point around mario to move towards, point needs to be within 0x2000 angle
            // range of marios faceangle
            o->oMoveAngleYaw = gMarioState->faceAngle[1] + 0x8000;
            o->oPosY = gMarioState->pos[1] + random_float() * 150.f + 100.f;
            dist = random_float() * 500.f + 2500.f;
            angle = gMarioState->faceAngle[1] + (random_u16() % 0x1FFF) - 0x1000;
            o->oPosX = gMarioState->pos[0] + sins(angle) * dist;
            o->oPosZ = gMarioState->pos[2] + coss(angle) * dist;
            o->oAnimState = (dist / o->oForwardVel) * 1.8f;
            o->oAction = 1;
            cur_obj_scale(random_float() * .75f + .5f);
            o->oFaceAngleYaw = random_u16();
            break;
        case 1:
            if (o->oTimer > o->oAnimState) {
                o->oOpacity = approach_s16_symmetric(o->oOpacity, 0, 2);
                if (!o->oOpacity) {
                    obj_mark_for_deletion(o);
                }
            } else {
                o->oOpacity = approach_s16_symmetric(o->oOpacity, 192, 2);
            }
            break;
    }
    cur_obj_move_xz_using_fvel_and_yaw();
    o->oPosY += sins(o->oTimer * 0x780) * 4.f;
}
// despawn him if you dont have enough stars or his star is already collected.
void dolphincode(void) {
    float magnitude = 10.0f;
    float distance = 0;
    if (o->oAction == 0) {
        if ((save_file_get_total_star_count(gCurrSaveFileNum - 1, 0, 0x18) < 12)
            || ((save_file_get_star_flags(gCurrSaveFileNum - 1, gCurrCourseNum - 1) & 0x02))) {
            obj_mark_for_deletion(o);
            return;
        }
        if (o->header.gfx.unk38.animFrame == 2) {
            o->oVelY = 20.f;
        }
        o->oPosY += o->oVelY;
        if (!o->oFreePointer1) {
            o->oFreePointer1 = spawn_object(o, 0, bhvHitbox);
            o->oFreePointer2 = spawn_object(o, 0, bhvHitbox);
            o->oFreePointer3 = spawn_object(o, 0, bhvHitbox);
            o->oFreePointer4 = spawn_object(o, 0, bhvHitboxNoReset);
        }
        if (!o->oSubAction) {
            if (o->oDistanceToMario < 550.f) {
                if (talkToMarioNoRotation(8)) {
                    o->oSubAction = 1;
                }
            }
        }

        if ((o->oFreePointer4->oInteractStatus) && (o->oTimer > 5)) {
            o->oAction = 1;
        }
        o->oFreePointer4->oInteractStatus = 0;
    }
    move_obj_with_physics(1);
    o->oFreePointer4->oInteractType = INTERACT_BREAKABLE;
    o->oFreePointer4->hitboxRadius = 70.f;
    o->oFreePointer4->hitboxHeight = 150.f;
    offsetChildByFloat(o->oFreePointer1, o, 0.0f, 100.f);
    offsetChildByFloat(o->oFreePointer2, o, 0.0f, 10.f);
    offsetChildByFloat(o->oFreePointer3, o, 0.0f, -90.f);
    offsetChildByFloat(o->oFreePointer4, o, -100.0f, -270.f);
    if (o->oAction == 1) {
        o->header.gfx.unk38.animFrame = 5;
        gMarioState->faceAngle[1] = o->oMoveAngleYaw;
        offsetChildByFloat(o->oFreePointer4, o, 0.0f, -300.f);
        gMarioState->pos[0] = o->oFreePointer4->oPosX;
        // gMarioState->pos[1] = o->oFreePointer4->oPosY;
        gMarioState->pos[2] = o->oFreePointer4->oPosZ;
        if (gMarioState->action & ACT_FLAG_SWIMMING) {
            o->oAction = 2;
        } else {
            gMarioState->action = ACT_HOLDING_BOWSER;
            magnitude = gMarioState->intendedMag * .5f
                        * coss(abs_angle_diff(gMarioState->intendedYaw, o->oFaceAngleYaw));
            if (magnitude < -5.f) {
                play_sound(SOUND_MOVING_TERRAIN_SLIDE, gDefaultSoundArgs);
            }
            if (magnitude > 0) {
                magnitude = 0;
            }
            gMarioState->pos[0] += sins(o->oMoveAngleYaw) * magnitude;
            gMarioState->pos[2] += coss(o->oMoveAngleYaw) * magnitude;

            o->oMoveAngleYaw = atan2s(-gMarioState->pos[2] + o->oPosZ, -gMarioState->pos[0] + o->oPosX);
            o->oPosX += sins(gMarioState->faceAngle[1]) * magnitude;
            o->oPosZ += coss(gMarioState->faceAngle[1]) * magnitude;
            o->oPosY = find_floor_height(o->oPosX, o->oPosY + 200.f, o->oPosZ);

            distance = o->oPosY - gMarioState->pos[1];
            o->oFaceAnglePitch = -atan2s(distance, -300.f) - 0x4000;

            gMarioState->pos[1] = find_floor_height(gMarioState->pos[0], gMarioState->pos[1] + 200.0f,
                                                    gMarioState->pos[2]);

            if (gMarioState->controller->buttonPressed & B_BUTTON) {
                o->oAction = 0;
                gMarioState->action = ACT_RELEASING_BOWSER;
            }
        }
    } else if (o->oAction == 2) {
        o->oForwardVel = -20.0f;
        cur_obj_init_animation(2);
        if ((o->oPosY + 400.f) < find_water_level(o->oPosX, o->oPosZ)) {
            o->oAction = 3;
        }
    } else if (o->oAction == 3) {
        // talk to mario, give star
        o->oVelY = 4.0f;
        o->oPosY = find_water_level(o->oPosX, o->oPosZ) - 350.f;
        cur_obj_init_animation(1);
        o->oForwardVel = 0.0f;
        o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, 0, 0x200);
        if (talkToMario(0)) {
            o->oAction = 4;
        }
    } else if (o->oAction == 4) {
        if (!o->oTimer) {
            bhv_spawn_star_no_level_exit(1);
        }
        o->oVelY = 2.0f;
        o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, 0x4000, 0x200);
        if (o->oTimer > 30) {
            o->oForwardVel = approach_f32(o->oForwardVel, 30.f, 1.0f, 1.0f);
        }
        if (o->oTimer > 200) {
            obj_mark_for_deletion(o);
        }
    }
}

void swimDolphins(void) {
    o->oForwardVel = 40.f;
}

void raftcode(void) {
    if (!o->oTimer) {
        if (save_file_get_star_flags(gCurrSaveFileNum - 1, gCurrCourseNum - 1) & 0x04) {
            o->oFreePointer1 = spawn_object(o, MODEL_TOAD, bhvToadMessage);
            obj_mark_for_deletion(o);
            o->oFreePointer1->oBehParams = 15 << 24;
            o->oFreePointer1->oPosX = -666.f;
            o->oFreePointer1->oPosY = -432.f;
            o->oFreePointer1->oPosZ = -1015.f;
        }
    }
    if ((save_file_get_total_star_count(gCurrSaveFileNum - 1, 0, 0x18) < 20)) {
        obj_mark_for_deletion(o);
        return;
    }
    if (!o->oFreePointer1) {
        o->oFreePointer1 = spawn_object(o, MODEL_TOAD, bhvToadMessage);
        o->oFreePointer1->oBehParams = 83 << 24;
        o->oFreePointer1->oPosY += 55.f;
        o->oFreePointer1->oPosX += 200.f;
    }
    load_object_collision_model();
}

#define waitmario 0
#define onjetski 1

#define splashy o->oBobombBuddyPosXCopy
void jetskiCode(void) {
    float x, y, z;
    struct Surface *floor;
    // delay visual position by a frame

    obj_update_gfx_pos_and_angle(gCurrentObject);
    switch (o->oAction) {
        case waitmario:
            if (cur_obj_is_mario_on_platform()) {
                o->oAction = 1;
                m->usedObj = o;
                m->action = ACT_RIDE_JETSKI;
            }
            load_object_collision_model();
            o->oForwardVel *= 0;
            break;
        case onjetski:
            x = o->oPosX;
            y = o->oPosY;
            z = o->oPosZ;
            o->oVelX += sins(gMarioState->intendedYaw) * gMarioState->intendedMag / 16.f;
            o->oVelZ += coss(gMarioState->intendedYaw) * gMarioState->intendedMag / 16.f;
            // get forward angle from X and Z component
            o->oForwardVel = sqrtf(o->oVelX * o->oVelX + o->oVelZ * o->oVelZ);
            if (o->oForwardVel > 0.1f) {
                o->oMoveAngleYaw =
                    approach_s16_symmetric(o->oMoveAngleYaw, atan2s(o->oVelZ, o->oVelX), 0x800);
            }
            if (gMarioState->intendedMag > 10.f) {

                if (abs_angle_diff(o->oMoveAngleYaw, gMarioState->intendedYaw) > 0x080) {
                    o->oMoveAngleYaw =
                        approach_s16_symmetric(o->oMoveAngleYaw, gMarioState->intendedYaw, 0x080);
                }
            }
            if (gMarioState->controller->buttonDown & B_BUTTON) {
                o->oForwardVel -= 3.0f;
                if (o->oForwardVel < -0.f) {
                    o->oForwardVel = 0.f;
                }
            }
            o->oForwardVel *= 0.98f;
            cur_obj_compute_vel_xz();
            gMarioState->pos[0] = o->oPosX;
            gMarioState->pos[1] = o->oPosY + 100.f;
            gMarioState->pos[2] = o->oPosZ;
            gMarioState->vel[1] = -75.f;
            gMarioState->faceAngle[1] = o->oMoveAngleYaw;
            m->forwardVel = o->oForwardVel;
            if (gMarioState->controller->buttonPressed & (Z_TRIG)) {
                gMarioState->action = ACT_DIVE;
                gMarioState->vel[1] = 35.f;
                gMarioState->forwardVel = -15.f;
                o->oAction = 0;
            }

            move_obj_with_physics(1);
            if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
                m->action = ACT_DIVE;
                obj_mark_for_deletion(o);
                spawn_mist_particles_with_sound(SOUND_OBJ_DEFAULT_DEATH);
                return;
            }
            find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
            if (!floor) {
                o->oPosX = x;
                o->oPosY = y;
                o->oPosZ = z;
            }
            splashy += o->oForwardVel;
            if (splashy > 100.f) {
                spawn_object(o, MODEL_IDLE_WATER_WAVE, bhvObjectWaterWave);
                cur_obj_play_sound_2(SOUND_OBJ_WALKING_WATER);
                cur_obj_play_sound_2(SOUND_ENV_METAL_BOX_PUSH);
                splashy -= 100.f;
            }
            break;
    }
    if (o->oPosY < find_water_level(o->oPosX, o->oPosZ)) {
        o->oVelY -= o->oPosY - find_water_level(o->oPosX, o->oPosZ);
    }
    o->oForwardVel *= 0.99f;
}

void pirateshipcode(void) {
    struct Object *object;
    if ((save_file_get_total_star_count(gCurrSaveFileNum - 1, 0, 0x18) < 32)
        || ((save_file_get_star_flags(gCurrSaveFileNum - 1, gCurrCourseNum - 1) & 0x08))) {
        obj_mark_for_deletion(o);
        if (o->oFreePointer1) {
            obj_mark_for_deletion(o->oFreePointer1);
        }
        if ((save_file_get_star_flags(gCurrSaveFileNum - 1, gCurrCourseNum - 1) & 0x08)) {
            object = spawn_object(o, 0x3a, bhvPirateTalk);
            object->oPosX = 560.f;
            object->oPosY = -432.f;
            object->oPosZ = -1015.f;
            object->oBehParams2ndByte = 38;
        }
        return;
    } else {
        if (!o->oFreePointer1) {
            o->oFreePointer1 = spawn_object(o, 0x3a, bhvPirate);
            offsetChildByFloat(o->oFreePointer1, o, 55.0f, -80.f);
        }
        if (o->oTimer == 100) {
            o->oTimer = 0;
            object = spawn_object(o, MODEL_BOWLING_BALL, bhvCannonBall);
            offsetChildByFloat(object, o, 300.f, 550.f);
            object->oForwardVel = lateral_dist_between_objects(object, gMarioObject) / 50.0f;
            object->oVelY = 110.f;
            object->oMoveAngleYaw = approach_s16_symmetric(
                o->oMoveAngleYaw,
                atan2s(gMarioObject->oPosZ - object->oPosZ, gMarioObject->oPosX - object->oPosX),
                0x1000);
            cur_obj_play_sound_1(SOUND_OBJ_POUNDING_CANNON);
        }
        load_object_collision_model();
    }
}

void cannonball(void) {
    if (o->oTimer < 30) {
        move_obj_with_physics(0);
    } else {
        move_obj_with_physics(1);
    }
    if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
        obj_mark_for_deletion(o);
        spawn_mist_particles_with_sound(SOUND_OBJ_DEFAULT_DEATH);
    }
}
void butler(void) {
    if (mario_ready_to_speak() && (o->oInteractStatus == INT_STATUS_INTERACTED)) {
        o->oAction++;
    }
    if (o->oAction) {
        if (talkToMarioNoRotation(o->oBehParams2ndByte)) {
            o->oAction = 0;
        }
    }
}
void piratecode(void) {
    // waitmariotalk
    // talk (mark X afterwards if no X exists), stop cannon from shooting after
    // waitmarioaway
    struct Object *a;
    rotateTowardsMario(0x100);
    switch (o->oAction) {
        case 0:
            if (o->oDistanceToMario < 700) {
                if (mario_ready_to_speak()) {
                    o->oAction++;
                }
            }
            break;
        case 1:
            if (talkToMario(166)) {
                o->oAction++;
                if (!cur_obj_nearest_object_with_behavior(bhvPirateCross)) {
                    a = spawn_object(o, 0x3b, bhvPirateCross);
                    a->oPosX = -750.f;
                    a->oPosZ = -2836.f;
                    a->oPosY = -844.f;
                }
            }
            break;
        case 2:
            if (o->oDistanceToMario > 700) {
                o->oAction = 0;
            }
            break;
    }
}

void bhv_cross(void) {
    cur_obj_align_gfx_with_floor();
    if (!o->oAction) {
        if (lateral_dist_between_objects(o, gMarioState->marioObj) < 500.f) {
            if (gMarioState->action == ACT_GROUND_POUND_LAND) {
                o->oAction = 1;
                bhv_spawn_star_no_level_exit(3);
                cur_obj_set_model(0);
            }
        }
    }
}

void noseguycode(void) {
    switch (o->oAction) {
        case 0:
            cur_obj_init_animation(0);
            if (!o->oTimer) {
                o->oSubAction = random_u16() & 0x3f;
            }
            if (o->oTimer > 80 + o->oSubAction) {
                o->oAction++;
            }
            break;
        case 1:
            if (o->oTimer == 12) {
                o->oHiddenBlueCoinSwitch = spawn_object(o, 0, bhvNoseguyRock);
                o->oHiddenBlueCoinSwitch->oHiddenBlueCoinSwitch = o;
            }
            if (o->oTimer == 37) {
                o->oHiddenBlueCoinSwitch->oAction = 1;
            }
            cur_obj_init_animation(1);
            if (o->oTimer == 66) {
                o->oAction = 0;
            }
            break;
    }
}

// also die if on death floor
void noseguyrockcode(void) {
    struct Surface *floor;
    switch (o->oAction) {
        case 0:
            cur_obj_set_pos_relative(o->oHiddenBlueCoinSwitch, -120.f, 180.0f, -10.0f);
            if (!o->oTimer) {
                spawn_mist_particles_variable(0, -40.f, 46.0f);
                cur_obj_play_sound_1(SOUND_OBJ_DEFAULT_DEATH);
            } else {
                cur_obj_set_model(0x36);
            }
            // wait
            break;
        case 1:
            if (!o->oTimer) {
                o->oForwardVel = 40.f;
                cur_obj_play_sound_2(SOUND_OBJ_MONTY_MOLE_ATTACK);
            }
            if (o->oTimer < 4) {
                o->oVelY = 0.0f;
            }
            // go
            find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
            move_obj_with_physics(1);
            o->oFaceAnglePitch += o->oForwardVel * 100.f;
            if (floor) {
                if (floor->normal.y < 0.95f) {

                    o->oMoveAngleYaw = approach_s16_symmetric(
                        o->oMoveAngleYaw, atan2s(floor->normal.z, floor->normal.x), 0x200);
                }
                if ((floor->type == SURFACE_DEATH_PLANE) && (o->oMoveFlags & OBJ_MOVE_ON_GROUND)) {
                    goto rockdeath;
                }
            }
            if (o->oTimer > 10) {
                if (cur_obj_lateral_dist_to_home() < 10.f) {
                rockdeath:
                    obj_mark_for_deletion(o);
                    spawn_mist_particles_variable(0, -40.f, 46.0f);
                }
            }
            vec3f_copy(&o->oHomeX, &o->oPosX);

            break;
    }
}

struct Collision *fliptilecolls[] = { fliptiles_collision0, fliptiles_collision1, fliptiles_collision2,
                                      fliptiles_collision3

};
void fliptilecode(void) {
    u32 *collisionData = segmented_to_virtual(fliptilecolls[o->oBehParams2ndByte]);

    o->collisionData = collisionData;

    o->oAnimState = o->oBehParams2ndByte;
    if (!o->oAction) {
        if (o->oSubAction) {
            if (((gMarioState->action & 0x03000000) == 0x03000000)
                || ((gMarioState->action & 0x03000000) == 0x01000000)) {
                if ((gMarioState->action != ACT_LAVA_BOOST)
                    && (gMarioState->action != ACT_FORWARD_ROLLOUT)) {
                    if (gMarioState->vel[1] > 10.f) {
                        o->oAction = 1;
                    }
                }
            }
        } else {
            if (gMarioState->pos[1] == gMarioState->floorHeight) {
                o->oSubAction = 1;
            }
        }
        load_object_collision_model();
    } else {
        o->oFaceAngleRoll += 0x800;
        if (o->oTimer > 14) {
            o->oAction = 0;
        }
    }
}
extern s16 newcam_yaw;
extern u16 newcam_distance_target;
extern f32 cameradist;
extern s16 s8DirModeYawOffset;
void rockchasecode(void) {
    struct Surface *floor;
    gMarioState->controller->buttonDown |= (L_CBUTTONS | R_CBUTTONS);
    gCurrentArea->camera->nextYaw = 0x8000;
    newcam_yaw = 0x8000;
    newcam_distance_target = 2507;
    o->oVelY -= 1.5f;

    if (gCurrentObject->oVelY < -70.0f) {
        gCurrentObject->oVelY = -70.0f;
    }
    o->oHomeY = o->oPosY;
    gCurrentObject->oPosY += gCurrentObject->oVelY;
    gCurrentObject->oMoveFlags &= ~OBJ_MOVE_ON_GROUND;
    if ((gCurrentObject->oPosY < find_floor_height(o->oPosX, o->oPosY + 100.f, o->oPosZ))) {
        o->oPosY = find_floor_height(o->oPosX, o->oPosY + 100.f, o->oPosZ);
        o->oVelY = 0;
        gCurrentObject->oMoveFlags |= OBJ_MOVE_ON_GROUND;
        o->oTimer = 0;
    } else {
        if (o->oTimer < 2) {
            o->oVelY = o->oPosY - o->oHomeY;
        }
    }
    o->oPosX += o->oForwardVel * sins(o->oMoveAngleYaw);
    o->oPosZ += o->oForwardVel * coss(o->oMoveAngleYaw);
    o->oFaceAnglePitch += o->oForwardVel * 15.f;
    find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
    if (floor) {
        if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
            o->oForwardVel -= floor->normal.x * 6.0f;
            if (o->oForwardVel > 55.f) {
                o->oForwardVel = 55.f;
            }
        }
        if (floor->normal.y < 0.95f) {

            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw,
                                                      atan2s(floor->normal.z, floor->normal.x), 0x200);
        }
    }
}

void quetzalcode(void) {
    o->oForwardVel = 60.f;
    o->oMoveAngleYaw += 0x50;
    cur_obj_move_xz_using_fvel_and_yaw();
    if (!o->oHiddenBlueCoinSwitch) {
        o->oHiddenBlueCoinSwitch = spawn_object(o, MODEL_STAR, bhvStar);
        o->oHiddenBlueCoinSwitch->oBehParams = 0x05000000;
    }
    if (o->oHiddenBlueCoinSwitch
        && (o->oHiddenBlueCoinSwitch->behavior == segmented_to_virtual(bhvStar))) {
        o->oHiddenBlueCoinSwitch->oPosX = o->oPosX + sins(o->oMoveAngleYaw) * -1150.f;
        o->oHiddenBlueCoinSwitch->oPosZ = o->oPosZ + coss(o->oMoveAngleYaw) * -1150.f;
        o->oHiddenBlueCoinSwitch->oPosY = o->oPosY + 50.f;
        o->oHiddenBlueCoinSwitch->hitboxDownOffset = -25.f;
        o->oHiddenBlueCoinSwitch->hitboxHeight = 100.f;
        o->oHiddenBlueCoinSwitch->hitboxRadius = 160.f;
    }
}

u8 rendershop = 0;
s8 analogset = 0;
#define textheight2 12
#define textheight 10

struct itemEntry {
    u16 price;
    u8 *name;
};

void convertNumberToSm64String(int number, u8 string[]) {
    int k = 0;
    string[4] = 0;
    while (number > 0) {
        string[4 - k] = number % 10;
        number = number / 10;
        k++;
    }
}

u8 SM64String(u8 letter) {
    if ((letter > 0x2f) && (letter < 0x3a)) {
        return letter - 0x30;
    }
    if ((letter > 0x60) && (letter < 0x7b)) {
        return letter - 0x3d;
    }
    if ((letter > 0x40) && (letter < 0x5b)) {
        return letter - 0x37;
    }
    if (letter == 0x21) {
        return 0xf2;
    }
    if (letter == 0x3f) {
        return 0xf4;
    }
    if (letter == 0x20) {
        return 0x9e;
    }
    if (letter == 0x3a) {
        return 0xe6;
    }
    if (letter == 0x2e) {
        return 0x3f;
    }
    if (letter == 0x27) {
        return 0x3e;
    }
    if (letter == 0x28) {
        return 0xe1;
    }
    if (letter == 0x29) {
        return 0xe3;
    }
    if (letter == 0x21) {
        return 0xf2;
    }
    if (letter == 0x3c) {
        return 0x52;
    }
    if (letter == 0x3e) {
        return 0x53;
    }
    if (letter == 0x7e) {
        return 0xf7;
    }

    if (letter == 0x00) {
        return 0xff;
    }
    return 0xff;
}

struct itemEntry itemList[] = {
    // permanent items
    { 3, "Open Cannon" },
    { 10, "Unlock Wing Cap" },
    { 5, "Unlock Staryu" },
    { 5, "Unlock Weezing" },
    { 5, "Unlock Tangela" },
    { 5, "Unlock Haunter" },
    { 5, "Unlock Onix" },
    { 5, "Unlock Primeape" },
    { 5, "Unlock Golem" },
    { 5, "Unlock Articuno" },
    { 5, "Unlock Magnemite" },
    { 5, "Unlock Gyarados" },
    { 5, "Unlock Hypno" },
    // change pokemon
    { 0, "Change Partner" },

};
extern void print_generic_string2(s16 x, s16 y, const u8 *str);
int itemListlength = sizeof(itemList) / sizeof(struct itemEntry);
int blackmarketselection;

#define menuX 50
#define menuY 0xb9
#define menuoffset 0x11
u16 pokedialog;
extern u32 getPokeID(u16 selection);
void renderAllItems(u8 a) {
    int i, j, k;
    u8 ranktext[7] = { 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0xff };
    for (i = 0; i < itemListlength; i++) {
        ranktext[0] = 0XFA;
        print_generic_string2(menuX + a, menuY - menuoffset - textheight * i - a, itemList[i].name);
        k = 0;
        if (i == 0) {
            if (gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[2]) {
                k = 1;
            }
        } else if (i == 1) {
            if (save_file_get_flags() & SAVE_FLAG_HAVE_WING_CAP) {
                k = 1;
            }
        } else if (i < itemListlength - 1) {
            if (gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[0] & getPokeID(i)) {
                k = 1;
            }
            pokedialog = 0;
        }
        if (!k) {
            convertNumberToSm64String(itemList[i].price, ranktext + 1); // normalize number
            print_generic_string(menuX + a + 100, menuY - menuoffset - textheight * i - a, ranktext);
        } else {
            print_generic_string2(menuX + a + 100, menuY - menuoffset - textheight * i - a, "BOUGHT");
        }
        ranktext[1] = 0x9e;
        ranktext[2] = 0x9e;
        ranktext[3] = 0x9e;
        ranktext[4] = 0x9e;
        ranktext[5] = 0x9e;
    }
}
extern int spawnID;
u32 getPokeID(u16 selection) {
    // spawnID = selection - 2;
    switch (selection) {
        case 2:
            pokedialog = 159;
            return 1 << 0;
            break;
        case 3:
            pokedialog = 160;
            return 1 << 1;
            break;
        case 4:
            pokedialog = 161;
            return 1 << 2;
            break;
        case 5:
            pokedialog = 162;
            return 1 << 3;
            break;
        case 6:
            pokedialog = 163;
            return 1 << 4;
            break;

        case 7:
            pokedialog = 164;
            return 1 << 5;

            break;
        case 8:
            pokedialog = 165;
            return 1 << 6;

            break;
        case 9:
            pokedialog = 170;
            return 1 << 7;

            break;
        case 10:
            pokedialog = 171;
            return 1 << 8;

            break;
        case 11:
            pokedialog = 168;
            return 1 << 9;

            break;
        case 12:
            pokedialog = 172;
            return 1 << 10;
            break;
    }
}
// add other pokemon
// add currently available stars
// mark already unlocked things somehow
u8 pickpoke = 0;
s8 yoshiselected = 0; // pokeselected
u16 stardust = 999;
void print_text_fmt_int(s32 x, s32 y, const char *str, s32 n);
void render_menu() {
    struct Object *cannonClosed;
    s16 buddyText, cutscene;
    s32 j, ok;
    int arrowmax = itemListlength;
    stardust = gMarioState->numStars - gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[1];
    pokedialog = 0;
    create_dl_ortho_matrix();
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);

    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    print_generic_string2(menuX + 1, menuY - 1, "BUY ITEM");
    print_generic_string2(menuX + 91, menuY - 1, "MONEY");
    renderAllItems(1);

    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    print_generic_string2(menuX, menuY, "BUY ITEM");
    print_generic_string2(menuX + 90, menuY, "MONEY");
    renderAllItems(0);
    print_text_fmt_int(180, 184, "%d-",
                       gMarioState->numStars - gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[1]);
    gSPDisplayList(gDisplayListHead++, dl_ia_text_end);

    if (gMarioState->controller->rawStickY > 20) {
        if (!analogset) {
            analogset = 1;
            blackmarketselection--;
            play_sound(SOUND_MENU_CHANGE_SELECT, gDefaultSoundArgs);
        }
    } else if (gMarioState->controller->rawStickY < -20) {
        if (!analogset) {
            analogset = -1;
            blackmarketselection++;
            play_sound(SOUND_MENU_CHANGE_SELECT, gDefaultSoundArgs);
        }
    } else {
        analogset = 0;
    }
    if (blackmarketselection > (arrowmax - 1)) {
        blackmarketselection = 0;
    } else if (blackmarketselection == -1) {
        blackmarketselection = arrowmax - 1;
    }
    create_dl_translation_matrix(MENU_MTX_PUSH, menuX - 10,
                                 menuY - menuoffset - (blackmarketselection * textheight), 0);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    gSPDisplayList(gDisplayListHead++, dl_draw_triangle);
    gSPPopMatrix(gDisplayListHead++, G_MTX_MODELVIEW);

    if (gMarioState->controller->buttonPressed & B_BUTTON) {
        // warp player
        rendershop = -1;
    }
    if (gMarioState->controller->buttonPressed & A_BUTTON) {
        if (stardust >= itemList[blackmarketselection].price) {
            switch (blackmarketselection) {
                case 0:
                    if (!gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[2]) {
                        gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[2] = 1;
                        cannonClosed = cur_obj_nearest_object_with_behavior(bhvCannonClosed);
                        // cutscene = cutscene_object(CUTSCENE_PREPARE_CANNON, cannonClosed);
                        rendershop = 0;
                        gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[1] += 3;
                        play_sound(SOUND_MENU_STAR_SOUND, gDefaultSoundArgs);
                    } else {
                        play_sound(SOUND_MENU_CAMERA_BUZZ, gDefaultSoundArgs);
                    }
                    break;
                case 1:
                    if (save_file_get_flags() & SAVE_FLAG_HAVE_WING_CAP) {
                        play_sound(SOUND_MENU_CAMERA_BUZZ, gDefaultSoundArgs);
                    } else {
                        save_file_set_flags(SAVE_FLAG_HAVE_WING_CAP);
                        rendershop = 0;
                        gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[1] += 10;
                        play_sound(SOUND_MENU_STAR_SOUND, gDefaultSoundArgs);
                    }
                    break;
                default:
                    if (gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[0]
                        & getPokeID(blackmarketselection)) {
                        play_sound(SOUND_MENU_CAMERA_BUZZ, gDefaultSoundArgs);
                        pokedialog = 0;
                    } else {
                        gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[0] |=
                            getPokeID(blackmarketselection);
                        spawnID = blackmarketselection - 2;
                        rendershop = 0;
                        gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[1] += 5;
                        play_sound(SOUND_MENU_STAR_SOUND, gDefaultSoundArgs);
                    }
                    break;
                case 13:
                    if (!gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[0]) {
                        play_sound(SOUND_MENU_CAMERA_BUZZ, gDefaultSoundArgs);
                    } else {
                        rendershop = -1;
                        pickpoke = 1;
                        ok = 0;
                        for (j = 0; (j < 11) && !ok; j++) {
                            if (gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[0]
                                & (1 << ((yoshiselected) % 11))) {
                                ok = 1;
                            } else {
                                yoshiselected++;
                                if (yoshiselected > 10) {
                                    yoshiselected = 0;
                                }
                            }
                        }
                    }
                    break;
            }
        } else {
            play_sound(SOUND_MENU_CAMERA_BUZZ, gDefaultSoundArgs);
        }
    }
}

int x = 0;
int y = 0;
int analogsety = 0;
int analogsetx = 0;
extern int spawnID;
#define namemenuX 0x50
#define namemenuY 0xa1

struct itemEntry pokeList[] = {
    // permanent items
    { 0, " Staryu" },   { 0, "Weezing" },  { 0, "Tangela" }, { 0, "Haunter" },
    { 0, " Onix" },     { 0, "Primeape" }, { 0, " Golem" },  { 0, "Articuno" },
    { 0, "Magnemite" }, { 0, "Gyarados" }, { 0, " Hypno" },

};
renderYoshiMenu(u8 offset) {

    print_generic_string2(namemenuX + offset, namemenuY - offset, "Select Pokemon");

    print_generic_string2(namemenuX + offset + 92, namemenuY - offset, pokeList[yoshiselected].name);

    print_generic_string2(namemenuX + offset + 80, namemenuY - offset, "<           >");
}
void select_menu() {
    int j;
    int ok = 0;
    create_dl_ortho_matrix();
    gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
    gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
    renderYoshiMenu(1);
    gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
    renderYoshiMenu(0);

    if (gMarioState->controller->rawStickX > 20) {
        if (!analogsetx) {
            analogsetx = 1;
            yoshiselected++;
            if (yoshiselected > 10) {
                yoshiselected = 0;
            }
            play_sound(SOUND_MENU_CHANGE_SELECT, gDefaultSoundArgs);
            for (j = 0; (j < 11) && !ok; j++) {
                if (gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[0]
                    & (1 << ((yoshiselected) % 11))) {
                    ok = 1;
                } else {
                    yoshiselected++;
                    if (yoshiselected > 10) {
                        yoshiselected = 0;
                    }
                }
            }
        }
    } else if (gMarioState->controller->rawStickX < -20) {
        if (!analogsetx) {
            analogsetx = -1;
            yoshiselected--;
            if (yoshiselected == -1) {
                yoshiselected = 10;
            }
            for (j = 0; (j < 11) && !ok; j++) {
                if (gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[0]
                    & (1 << ((yoshiselected) % 11))) {
                    ok = 1;
                } else {
                    yoshiselected--;
                    if (yoshiselected == -1) {
                        yoshiselected = 10;
                    }
                }
            }
            play_sound(SOUND_MENU_CHANGE_SELECT, gDefaultSoundArgs);
        }
    } else {
        analogsetx = 0;
    }
    /* if (yoshiselected > (10)) {
         yoshiselected = 0;
     } else if (yoshiselected == -1) {
         yoshiselected = 10;
     }*/

    if (gMarioState->controller->buttonPressed & (A_BUTTON | START_BUTTON | B_BUTTON)) {
        pickpoke = 0;
        rendershop = 0;
        spawnID = yoshiselected;
    }
}

void panthershop(void) {
    switch (o->oAction) {
        case 0:
            // waitfor mario close
            if ((o->oDistanceToMario < 500.f) && ((o->oPosY + 200.f) > gMarioState->pos[1])
                && ((u16) o->oAngleToMario > 0x1000) && ((u16) o->oAngleToMario < 0x4000)) {
                o->oAction++;
            }
            break;
        case 1:
            if (talkToMario(169)) {
                o->oAction++;
                rendershop = 1;
                pickpoke = 0;
                blackmarketselection = 0;
            }
            // display text box
            break;
        case 2:
            // show shop menu
            if ((rendershop != 1) && !pickpoke) {
                o->oAction++;
            }
            break;
        case 3:
            // show last text
            if (pokedialog) {
                if (talkToMario(pokedialog)) {
                    o->oAction++;
                    pokedialog = 0;
                }

            } else {
                if (talkToMario(167)) {
                    o->oAction++;
                }
            }
            break;
        case 4:
            // wait mario far
            if ((o->oDistanceToMario < 500.f) && ((o->oPosY + 200.f) > gMarioState->pos[1])
                && ((u16) o->oAngleToMario > 0x1000) && ((u16) o->oAngleToMario < 0x4000)) {
            } else {
                o->oAction = 0;
            }
            break;
    }
}

extern Gfx ccm_dl_wata_mesh[];
extern Gfx ccm_dl_Wtaerhigh_mesh[];
extern Gfx ccm_dl_water_mesh[];
void killwater(void) {
    int i;
    Gfx *a /*= segmented_to_virtual(ccm_dl_wata_mesh)*/;
    // a[0].words.w0 = 0xdf000000;
    a = segmented_to_virtual(ccm_dl_Wtaerhigh_mesh);
    a[0].words.w0 = 0xdf000000;
    a = segmented_to_virtual(ccm_dl_water_mesh);
    a[0].words.w0 = 0xdf000000;
    /*for (i = 0; i < 20; i++) {
        gEnvironmentRegions[i] = -11000;
    }*/
    for (i = 0; i < *gEnvironmentRegions; i++) {
        gEnvironmentRegions[i * 6 + 6] = -11000;
    }
    obj_mark_for_deletion(o);
}
// bparam1 is star ID
extern Gfx ccm_dl_waterfountain_mesh[];
void desertfountain(void) {
    Gfx *a = segmented_to_virtual(ccm_dl_waterfountain_mesh);
    switch (o->oAction) {
        case 0:
            o->oOpacity = a[0].words.w0;
            a[0].words.w0 = 0xdf000000;
            o->oAction++;
            break;
        case 1:
            if (cur_obj_dist_to_nearest_object_with_behavior(bhvGrindel) < 300.f) {
                if (cur_obj_nearest_object_with_behavior(bhvGrindel)->oVelY < 0.f) {

                    o->oAction++;
                    cur_obj_play_sound_2(SOUND_ENV_WATER_DRAIN);
                    cur_obj_play_sound_2(SOUND_GENERAL_WALL_EXPLOSION);
                    spawn_mist_particles_variable(0, 0, 46.f);
                    spawn_triangle_break_particles(30, 138, 3.0f, 4);
                }
            }
            break;
        case 2:
            if (o->oTimer == 10) {
                a[0].words.w0 = o->oOpacity;
            }
            if (o->oTimer > 20) {
                spawn_default_star(gMarioState->pos[0], gMarioState->pos[1] + 200.0f,
                                   gMarioState->pos[2]);
                obj_mark_for_deletion(o);
            }
            break;
    }
}

void sleepstarspawn(void) {
    if (gMarioState->action == ACT_SLEEPING) {
        if (o->oDistanceToMario < 2000.f) {
            spawn_default_star(gMarioState->pos[0], gMarioState->pos[1] + 200.0f, gMarioState->pos[2]);
            obj_mark_for_deletion(o);
        }
    }
}
#define blargY 20.f
#define movetimer 40
void bigblarrgg(void) {
    o->header.gfx.scale[0] = (o->oBehParams2ndByte + 100.f) / 100.f;
    o->header.gfx.scale[1] = (o->oBehParams2ndByte + 100.f) / 100.f;
    o->header.gfx.scale[2] = (o->oBehParams2ndByte + 100.f) / 100.f;
    if (!o->oOpacity) {
        o->oOpacity = o;
        o->oPosY -= o->header.gfx.scale[1] * blargY * (movetimer + 1);
    }
    switch (o->oAction) {
        case 0:
            if (o->oTimer > movetimer) {
                o->oAction = 1;
            }
            break;
        case 1:
            o->oPosY += 20.f;
            if (o->oTimer > movetimer) {
                o->oAction = 2;
            }
            break;
        case 2:
            if (o->oDistanceToMario < 2000.f) {

                if (o->header.gfx.unk38.animFrame == 79) {
                    o->oSubAction++;
                }
                if (o->oSubAction == 2) {
                    o->oAction = 3;
                }
            }
            break;
        case 3:
            o->oPosY -= 20.f;
            if (o->oTimer > movetimer) {
                o->oAction = 0;
            }
            break;
    }
    load_object_collision_model();
}

void waterforce(void) {
    if (absf(o->oPosX - gMarioState->pos[0]) < 500.f) {
        if (o->oPosZ > gMarioState->pos[2]) {
            if (o->oPosY > gMarioState->pos[1]) {
                gMarioState->pos[2] -= 60.f;
            }
        }
    }
}

extern Gfx mat_mirage_floorSide_001_v2_v2[];
extern Gfx mat_mirage_ground_001_v2_v2[];
extern Gfx mat_mirage_stone_001_v2_v2[];
extern Gfx mat_mirage_triangularStone_001_v2_v2[];
extern Gfx mat_mirage_roofOrnament_002_v2_v2[];
extern Gfx mat_mirage_sm64_material_005[];
extern Gfx mat_mirage_sm64_material_014_v2_v2[];
extern Gfx mat_mirage_sm64_material_002[];
extern Gfx mat_mirage_sm64_material_003[];
extern Gfx mat_mirage_sm64_material_004[];
extern Gfx mat_mirage_roofOrnament_003_v2_v2[];
extern Gfx mat_mirage_sm64_material_006[];
extern Gfx mat_mirage_sm64_material_007[];
void setTransparency(int t) {
    o->oOpacity = t;
}

void toadmummy(void) {
    Vec3f backup;
    vec3f_copy(backup, &o->oPosX);
    switch (o->oAction) {
        case 0:
            cur_obj_init_animation(0);
            o->header.gfx.unk38.animFrame = 0;
            if (o->oDistanceToMario < 1500.f) {
                o->oAction++;
            }
            break;
        case 1:
            if (o->oTimer > 39) {
                o->oAction++;
            }
            break;
        case 2:
            cur_obj_init_animation(1);
            o->oForwardVel = approach_f32_symmetric(
                o->oForwardVel, (coss(o->oMoveAngleYaw - o->oAngleToMario) + 1.f) * 2.f, 2.0f);
            rotateTowardsMario(0x200);
            break;
    }
    cur_obj_update_floor_height_and_get_floor();
    cur_obj_move_standard(-78);
    if ((o->oFloorHeight + 300.f) < o->oPosY) {
        o->oPosX = backup[0];
        o->oPosZ = backup[2];
    }
}
int mirageID = 0;
void mirage(void) {
    o->oDrawingDistance = 100000.f;
    switch (o->oAction) {
        case 0:
            cur_obj_set_model(0);
            if (mirageID == o->oBehParams2ndByte) {
                o->oAction = 1;
            }
            break;
        case 1:
            o->oBobombBuddyPosXCopy = 100000.f;
            if (!(o->oBehParams & 0xff)) {
                cur_obj_set_model(0x37);
            }
            if (o->oTimer < 85) {
                setTransparency(o->oTimer * 3);
            } else {
                o->oAction = 2;
                setTransparency(255);
            }
            break;
        case 2:
            if (o->oBobombBuddyPosXCopy > o->oDistanceToMario) {
                o->oBobombBuddyPosXCopy = o->oDistanceToMario;
            } else if ((o->oBobombBuddyPosXCopy + 1000.f) < o->oDistanceToMario) {
                level_trigger_warp(m, WARP_OP_WARP_FLOOR);
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x14, 0xff, 0xa0, 0);
                sSourceWarpNodeId = 0x0B;
            }
            if (o->oDistanceToMario < 7000.f) {
                o->oAction = 3;
            }
            break;
        case 3:
            if (o->oTimer < 51) {
                setTransparency(255 - o->oTimer * 5);
            } else {
                obj_mark_for_deletion(o);
                mirageID++;
            }
            break;
    }
}

void offsetChildByFloatwithParallel(struct Object *child, struct Object *parent, float yOffset,
                                    float horizOffset, float paraOffset) {
    child->oHomeY = parent->oPosY + yOffset;
    child->oHomeX = parent->oPosX + horizOffset * sins(parent->oMoveAngleYaw)
                    + paraOffset * sins((parent->oMoveAngleYaw + 0x4000) & 0xffff);
    child->oHomeZ = parent->oPosZ + horizOffset * coss(parent->oMoveAngleYaw)
                    + paraOffset * coss((parent->oMoveAngleYaw + 0x4000) & 0xffff);
}

void spawn_wind_particles(s16 pitch, s16 yaw);
void huffnpuff(void) {
    struct Object *obj;
    float dist;
    if (!o->oHiddenBlueCoinSwitch) {
        o->oHiddenBlueCoinSwitch = spawn_object(o, 0x3A, bhvHuffPuffBaby);
        o->oHiddenBlueCoinSwitch->oHiddenBlueCoinSwitch = o;
        o->oHiddenBlueCoinSwitch->oBehParams2ndByte = 0;
        o->oHiddenBlueCoinSwitch->oOpacity = random_u16();
        o->oHiddenBlueCoinSwitch = spawn_object(o, 0x3A, bhvHuffPuffBaby);
        o->oHiddenBlueCoinSwitch->oHiddenBlueCoinSwitch = o;
        o->oHiddenBlueCoinSwitch->oBehParams2ndByte = 1;
        o->oHiddenBlueCoinSwitch->oOpacity = random_u16();
        o->oHiddenBlueCoinSwitch = spawn_object(o, 0x3A, bhvHuffPuffBaby);
        o->oHiddenBlueCoinSwitch->oHiddenBlueCoinSwitch = o;
        o->oHiddenBlueCoinSwitch->oBehParams2ndByte = 2;
        o->oHiddenBlueCoinSwitch->oOpacity = random_u16();
    }
    switch (o->oAction) {
        case 0:
            // talktomario
            cur_obj_init_animation(0);
            if (talkToMario(158)) {
                o->oAction = 1;
                o->oNumLootCoins = 150 + random_u16() & 0xFF;
                sequence_player_unlower(SEQ_PLAYER_LEVEL, 60);
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
                o->oHealth = 0;
            }
            break;
        case 1:
            // move around the arena
            cur_obj_init_animation(0);
            o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, 0, 0x400);
            o->oFaceAngleRoll = approach_s16_symmetric(o->oFaceAngleRoll, 0, 0x400);
            o->oFaceAngleYaw += 0x0040 + o->oHealth * 0x40;
            o->oMoveAngleYaw = o->oFaceAngleYaw;
            o->oHomeX = sins(o->oFaceAngleYaw) * -1600.f;
            o->oHomeZ = coss(o->oFaceAngleYaw) * -1600.f;
            o->oHomeY = 250.f;
            if (o->oTimer > o->oNumLootCoins) {
                o->oAction++;
                o->oNumLootCoins = 60 + (random_u16() & 0x7F) - o->oHealth * 20;
            }
            break;
        case 2:
            // blow air at mario
            cur_obj_init_animation(1);
            if (o->oTimer > 10) {
                spawn_wind_particles2(0, o->oFaceAngleYaw);
                play_sound(SOUND_ENV_WIND2, gMarioState->marioObj->header.gfx.cameraToObject);
                if (abs_angle_diff(o->oFaceAngleYaw, obj_angle_to_object(o, gMarioState->marioObj))
                    < 0x1400) {
                    gMarioState->pos[0] += sins(o->oFaceAngleYaw) * 20.f + o->oHealth * 5.f;
                    gMarioState->pos[2] += coss(o->oFaceAngleYaw) * 20.f + o->oHealth * 5.f;
                }
            }
            if (o->oTimer > 80) {
                o->oAction = 1;
            }
            break;
        case 3:
            // get knocked back, shake, back to normal, triggers if hammer thrown at it
            cur_obj_init_animation(0);
            o->oVelX = sins(o->oMoveAngleYaw) * o->oForwardVel;
            o->oVelZ = coss(o->oMoveAngleYaw) * o->oForwardVel;
            o->oFaceAngleRoll += o->oAngleVelRoll;
            o->oFaceAnglePitch += o->oAngleVelPitch;
            if (o->oTimer > 40) {
                if (o->oHealth > 2) {
                    o->oAction = 4;
                } else {
                    o->oAction = 1;
                    o->oFaceAngleYaw += 0x2000;
                }
            }
            break;
        case 4:
            // talk one more time, die, give star
            cur_obj_init_animation(0);
            o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, 0, 0x400);
            o->oFaceAngleRoll = approach_s16_symmetric(o->oFaceAngleRoll, 0, 0x400);
            if (!o->oSubAction) {
                if (talkToMario(157)) {
                    o->oSubAction = 1;
                    o->oTimer = 0;
                    stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
                    play_music(0, 0, 0);
                }
            } else {
                if (o->oTimer == 2) {
                    cur_obj_set_model(0);
                    spawn_mist_particles_with_sound(SOUND_OBJ_CHUCKYA_DEATH);
                }
                if (o->oTimer == 5) {
                    obj_mark_for_deletion(o);
                    spawn_default_star(0.0f, 200.0f, 0.0f);
                }
            }
            break;
    }
    if (o->oAction < 3) {
        if (obj = cur_obj_find_nearest_object_with_behavior(bhvBetaHoldableObject, &dist)) {
            if (dist < 500.f) {
                if (obj->oForwardVel > 20) {
                    cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
                    o->oAction = 3;
                    o->oHealth++;
                    o->oForwardVel = -80.f;
                    o->oAngleVelPitch = random_u16() & 0xFff - 0x800;
                    o->oAngleVelRoll = random_u16() & 0xfff - 0x800;
                }
            }
        }
    }
    if (o->oAction) {
        o->oVelX += ((o->oHomeX - o->oPosX) * 0.007f);
        o->oVelY += ((o->oHomeY - o->oPosY) * 0.007f) + (sins(o->oOpacity * 256) * 1.f);
        o->oVelZ += ((o->oHomeZ - o->oPosZ) * 0.007f);
        o->oVelX *= 0.92f;
        o->oVelY *= 0.92f;
        o->oVelZ *= 0.92f;
        o->oOpacity += random_u16() & 3;
    }
    cur_obj_move_using_vel();
}

void huffnpuffbaby(void) {
    switch (o->oAction) {
        case 0:
            // talktomario
            switch (o->oBehParams2ndByte) {
                case 0:
                    o->oBobombBuddyPosXCopy = 550.f; // y offset
                    o->oBobombBuddyPosYCopy = 100.f; // lateral offset
                    o->oBobombBuddyPosZCopy = 300.f; // parallel offset
                    break;
                case 1:
                    o->oBobombBuddyPosXCopy = 20.f;   // y offset
                    o->oBobombBuddyPosYCopy = 125.f;  // lateral offset
                    o->oBobombBuddyPosZCopy = -700.f; // parallel offset
                    break;
                case 2:
                    o->oBobombBuddyPosXCopy = -10.f; // y offset
                    o->oBobombBuddyPosYCopy = 125.f; // lateral offset
                    o->oBobombBuddyPosZCopy = 900.f; // parallel offset
                    break;
            }
            if (!o->oTimer) {
                offsetChildByFloatwithParallel(o, o->oHiddenBlueCoinSwitch, o->oBobombBuddyPosXCopy,
                                               o->oBobombBuddyPosYCopy, o->oBobombBuddyPosZCopy);
                o->oPosX = o->oHomeX;
                o->oPosY = o->oHomeY;
                o->oPosZ = o->oHomeZ;
                o->oVelX = 0.f;
                o->oVelY = 0.f;
                o->oVelZ = 0.f;
            }
            if (o->oHiddenBlueCoinSwitch->oAction) {
                o->oAction++;
                o->oSubAction = 150 + random_u16() & 0xFF;
            }
            break;
        case 1:
            // get in position before attack
            switch (o->oBehParams2ndByte) {
                case 0:
                    o->oBobombBuddyPosYCopy = 1500.f; // lateral offset
                    o->oBobombBuddyPosZCopy = 1250.f; // parallel offset
                    break;
                case 1:
                    o->oBobombBuddyPosYCopy = 750.f;   // lateral offset
                    o->oBobombBuddyPosZCopy = -1000.f; // parallel offset
                    break;
                case 2:
                    o->oBobombBuddyPosYCopy = 550.f; // lateral offset
                    o->oBobombBuddyPosZCopy = 600.f; // parallel offset
                    break;
            }
            if (o->oTimer > 20) {
                rotateTowardsMario(0x800);
            }
            o->oBobombBuddyPosXCopy =
                gMarioState->pos[1] - o->oHiddenBlueCoinSwitch->oPosY + 100.f; // y offset
            if (o->oTimer > o->oNumLootCoins) {
                o->oAction++;
                o->oNumLootCoins = 150 + random_u16() & 0xFF;
            }
            break;
        case 2:
            switch (o->oBehParams2ndByte) {
                case 0:
                    o->oBobombBuddyPosYCopy = 750.f;   // lateral offset
                    o->oBobombBuddyPosZCopy = -1200.f; // parallel offset
                    break;
                case 1:
                    o->oBobombBuddyPosYCopy = 1500.f; // lateral offset
                    o->oBobombBuddyPosZCopy = 1000.f; // parallel offset
                    break;
                case 2:
                    o->oBobombBuddyPosYCopy = 1100.f; // lateral offset
                    o->oBobombBuddyPosZCopy = -600.f; // parallel offset
                    break;
            }
            if (o->oTimer > 20) {
                rotateTowardsMario(0x800);
            }
            o->oBobombBuddyPosXCopy =
                gMarioState->pos[1] - o->oHiddenBlueCoinSwitch->oPosY + 100.f; // y offset
            if (o->oTimer > o->oNumLootCoins) {
                o->oAction--;
                o->oNumLootCoins = 150 + random_u16() & 0xFF;
            }
            break;
    }
    offsetChildByFloatwithParallel(o, o->oHiddenBlueCoinSwitch, o->oBobombBuddyPosXCopy,
                                   o->oBobombBuddyPosYCopy, o->oBobombBuddyPosZCopy);
    o->oVelX += ((o->oHomeX - o->oPosX) * 0.003f);
    o->oVelY += ((o->oHomeY - o->oPosY) * 0.003f) + (sins(o->oOpacity * 256) * 1.f);
    o->oVelZ += ((o->oHomeZ - o->oPosZ) * 0.003f);
    o->oVelX *= 0.92f;
    o->oVelY *= 0.92f;
    o->oVelZ *= 0.92f;
    o->oOpacity += random_u16() & 3;
    cur_obj_move_using_vel();
    o->oFaceAngleYaw = o->oHiddenBlueCoinSwitch->oFaceAngleYaw;
    if ((gCurrentObject->oPosY < find_floor_height(o->oPosX, o->oPosY + 70.f, o->oPosZ))) {
        o->oPosY = find_floor_height(o->oPosX, o->oPosY + 70.f, o->oPosZ);
    }
    if (o->oHiddenBlueCoinSwitch->oAction == 4) {
        spawn_mist_particles_variable(0, 0, 92.0f);
        obj_mark_for_deletion(o);
    }
}
#define STOPTIMER 10
void crystalpillar(void) {
    switch (o->oAction) {
        case 0:
            if (!o->oTimer) {
                o->oMoveAngleYaw = obj_angle_to_object(o, gMarioState->marioObj);
                o->oVelY = 34.5f;
            }
            if (o->oTimer > STOPTIMER) {
                o->oVelY = approach_f32_symmetric(o->oVelY, 0.f, 3.45f);
            }
            if (o->oTimer > STOPTIMER + 10) {
                o->oAction = 1;
                o->oForwardVel = 25.f;
            }
            break;
        case 1:
            cur_obj_play_sound_1(SOUND_ENV_METAL_BOX_PUSH);
            if (f32_find_wall_collision(&o->oPosX, &o->oPosY, &o->oPosZ, 20.f, 60.f)) {
                spawn_mist_particles();
                spawn_triangle_break_particles(30, 138, 3.0f, 4);
                cur_obj_play_sound_2(SOUND_OBJ_POUNDING1);
                obj_mark_for_deletion(o);
            }
            break;
    }
    cur_obj_compute_vel_xz();
    cur_obj_move_using_vel();
    o->oFaceAngleYaw += 0x600;
};

#define goalrot o->oBobombFuseTimer
#define goalX o->oBobombBuddyPosXCopy
#define goalY o->oBobombBuddyPosYCopy
#define goalZ o->oBobombBuddyPosZCopy
#define moveTimer o->oBobombExpBubGfxExpRateX
void pharaohcode(void) {
    struct Object *spawn = 0;
    switch (o->oAction) {
        case 0:
            // wait mario
            o->oGraphYOffset = -40.f;
            o->oHealth = 0;
            goalrot = 0x4000;
            cur_obj_init_animation(0);
            if (o->oDistanceToMario < 3000.f) {
                if (gMarioState->pos[1] < o->oHomeY - 100.f) {
                    o->oAction++;
                }
            }
            break;
        case 1:
            o->oVelX = 0;
            o->oVelZ = 0;
            o->oVelY = 0;
            cur_obj_init_animation(0);
            if (talkToMario(36)) {
                o->oAction++;
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
                goalrot = 0;
                moveTimer = random_u16() & 0x3f + 20;
            }
            // talk mario
            break;
        case 2:
            cur_obj_init_animation(0);
            if (moveTimer) {
                moveTimer--;
            } else {
                goalrot = goalrot + (random_u16() & 0x3FFF - 0x2000);
                moveTimer = random_u16() & 0x3f + 20;
            }
            if (o->oTimer > (120 - o->oHealth * 40)) {
                o->oAction = 3;
            }
            // fly idly
            break;
        case 3:
            cur_obj_init_animation(1);
            if (!o->oTimer) {
                o->oSubAction = random_u16() & 1;
            }
            if (o->header.gfx.unk38.animFrame == 21) {
                spawn = spawn_object(o, 0x3c, bhvCrystalpillar);
                spawn->oPosX = o->oPosX + sins(o->oMoveAngleYaw - 0x3800) * 300.f;
                spawn->oPosZ = o->oPosZ + coss(o->oMoveAngleYaw - 0x3800) * 300.f;
            } else if (o->header.gfx.unk38.animFrame == 42) {
                spawn = spawn_object(o, 0x3c, bhvCrystalpillar);
                spawn->oPosX = o->oPosX + sins(o->oMoveAngleYaw + 0x3800) * 300.f;
                spawn->oPosZ = o->oPosZ + coss(o->oMoveAngleYaw + 0x3800) * 300.f;
            }
            if (spawn) {
                // put into ground, make it come out of the floor
                spawn->oPosY = o->oHomeY - 1000.f;
                cur_obj_play_sound_2(SOUND_GENERAL_SWISH_AIR_2);
            }
            goalrot += o->oSubAction * 0x80 - 0x40;
            if (o->oTimer > 127 + o->oHealth * 128) {
                o->oAction = 5;
                cur_obj_play_sound_2(SOUND_OBJ_UNKNOWN6);
            }
            // swing left/right
            break;
        case 5:
            cur_obj_init_animation(3);
            // exhausted, fall to floor
            if (o->oVelY > -10.f) {
                o->oVelY -= 1.f;
                goalX = o->oHomeX + sins(goalrot) * 750.f;
                goalY = o->oHomeY + sins(o->oOpacity * 256) * 50.f;
                goalZ = o->oHomeZ + coss(goalrot) * 750.f;
            }
            o->oPosX = approach_f32_symmetric(o->oPosX, goalX, 10.f);
            o->oPosZ = approach_f32_symmetric(o->oPosZ, goalZ, 10.f);
            if (o->oTimer < 140) {
                if (o->header.gfx.unk38.animFrame > 48) {
                    o->header.gfx.unk38.animFrame = 19;
                }
            }
            if (o->oTimer > 159) {
                o->oAction = 2;
            }
            if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
                o->oHealth++;
                o->oAction = 6;
                o->oMoveAngleYaw = o->oAngleToMario;
                o->oForwardVel = -50.f;
                o->oVelY = 10.f;
                cur_obj_compute_vel_xz();
                cur_obj_play_sound_2(SOUND_OBJ_POKEY_DEATH);
            }
            break;
        case 6:
            cur_obj_init_animation(2);
            if (f32_find_wall_collision(&o->oPosX, &o->oPosY, &o->oPosZ, 20.f, 60.f)) {
                o->oSubAction++;
                o->oForwardVel = 0.f;
                cur_obj_compute_vel_xz();
                if (o->oHealth == 3) {
                    spawn_mist_particles();
                    spawn_triangle_break_particles(30, 138, 3.0f, 4);
                }
            }
            if (!o->oSubAction) {
                if (o->header.gfx.unk38.animFrame > 18) {
                    o->header.gfx.unk38.animFrame = 18;
                }
            }
            if (o->header.gfx.unk38.animFrame == 20) {
                // cur_obj_play_sound_2(SOUND_OBJ_STOMPED);
                create_sound_spawner(SOUND_GENERAL_BREAK_BOX);
                spawn_triangle_break_particles(20, 138, 3.0f, 4);
            }
            if (o->oHealth >= 3) {
                if (o->oSubAction > 3) {
                    play_music(SEQ_PLAYER_LEVEL, 0, 0);
                    stop_background_music(SEQUENCE_ARGS(4, SEQ_EVENT_BOSS));
                    spawn_default_star(o->oHomeX, o->oHomeY - 200.f, o->oHomeZ);
                    obj_mark_for_deletion(o);
                }
            }
            if (o->header.gfx.unk38.animFrame > 50) {
                o->oAction = 2;
            }
            // damaged, get shot backwards
            break;
    }
    if (o->oAction == 2 || o->oAction == 3 || o->oAction == 0) {
        o->oOpacity++;
        goalX = o->oHomeX + sins(goalrot) * 1100.f;
        goalY = o->oHomeY + sins(o->oOpacity * (0x1000 / 40)) * 50.f;
        goalZ = o->oHomeZ + coss(goalrot) * 1100.f;
        o->oVelX = (goalX - o->oPosX) * 0.02f;
        o->oVelX *= 0.95f;
        o->oVelY = (goalY - o->oPosY) * 0.02f;
        o->oVelY *= 0.95f;
        o->oVelZ = (goalZ - o->oPosZ) * 0.02f;
        o->oVelZ *= 0.95f;
    }
    o->oPosX += o->oVelX;
    o->oPosY += o->oVelY;
    o->oPosZ += o->oVelZ;
    if ((gCurrentObject->oPosY < find_floor_height(o->oPosX, o->oPosY + 70.f, o->oPosZ))) {
        o->oPosY = find_floor_height(o->oPosX, o->oPosY + 70.f, o->oPosZ);
        o->oVelY = 0.f;
    }
    if (o->oAction != 6 && o->oAction != 5) {
        rotateTowardsMario(0x800);
    }
    o->oInteractStatus = 0;
}

void lilblarrgg(void) {
    switch (o->oAction) {
        case 0:
            // wait
            cur_obj_init_animation(0);
            o->header.gfx.unk38.animFrame = 0;
            o->oMoveAngleYaw = o->oAngleToMario;
            if (o->oDistanceToMario < 1000.f) {
                o->oAction = 1;
                o->oForwardVel = 30.f;
                o->oIntangibleTimer = -1;
                cur_obj_play_sound_2(SOUND_OBJ_EEL);
            }
            break;
        case 1:
            // attack
            o->oIntangibleTimer = 0;
            if (cur_obj_check_if_at_animation_end()) {
                o->oAction = 2;
            }
            cur_obj_move_xz_using_fvel_and_yaw();
            cur_obj_update_floor_height();
            o->oPosY = o->oFloorHeight;
            break;
        case 2:
            o->oIntangibleTimer = -1;
            vec3f_copy(&o->oPosX, &o->oHomeX);
            o->oForwardVel = 0;
            // go back to wait if mario far
            if (o->oDistanceToMario > 2000.f) {
                o->oAction = 0;
            }
            break;
    }
}

// if fell var, turn around
// if fell in water, explode
// roll in initial direction
void barrelrolling(void) {
    struct Surface *floor;
    if (!o->oOpacity) {
        if (((o->oPosY - gMarioState->pos[1]) < 750.f) && (o->oDistanceToMario < 3000.f)) {
            o->oOpacity = 1;
        }
    } else {
        if (o->oForwardVel < 20.f) {
            o->oForwardVel += 0.5f;
        }
        if (!(o->oMoveFlags & OBJ_MOVE_ON_GROUND)) {
            o->oAction = 1;
        } else {
            o->oAction = 0;
        }
        if (o->oAction) {
            if (o->oTimer == 6) {
                o->oMoveAngleYaw += 0x8000;
                o->oForwardVel = -o->oForwardVel;
            }
            if (o->oTimer > 2) {
                o->oForwardVel *= 0.95f;
            }
        }
        if (o->oPosY < find_water_level(o->oPosX, o->oPosZ)) {
            obj_mark_for_deletion(o);
            spawn_mist_particles_variable(0, 0, 46.f);
            spawn_triangle_break_particles(30, 138, 3.0f, 4);
        }
        o->oVelY -= 4.f;
        cur_obj_compute_vel_xz();
        cur_obj_move_using_vel();
        o->oFloorHeight = find_floor(o->oPosX, o->oPosY + 50.f, o->oPosZ, &floor) + 192.f;
        if (o->oPosY < o->oFloorHeight) {
            o->oPosY = o->oFloorHeight;
            o->oMoveFlags |= OBJ_MOVE_ON_GROUND;
            o->oVelY = 0;
        } else {
            o->oMoveFlags &= ~OBJ_MOVE_ON_GROUND;
        }
#define ROTATESCALE 60.f
        if (o->oMoveAngleYaw & 0x8000) {
            if (o->oBehParams2ndByte) {
                o->oFaceAnglePitch += o->oForwardVel * ROTATESCALE;
            } else {
                o->oFaceAnglePitch -= o->oForwardVel * ROTATESCALE;
            }
        } else {
            if (o->oBehParams2ndByte) {
                o->oFaceAnglePitch -= o->oForwardVel * ROTATESCALE;
            } else {
                o->oFaceAnglePitch += o->oForwardVel * ROTATESCALE;
            }
        }
        load_object_collision_model();
    }
}
extern const Trajectory bbh_area_1_spline_kooparacepath[];
extern const Trajectory bbh_area_3_spline_kooparacepathreal[];
int pointercount = 8;
int mariowaypoint = 0;

#define point OBJECT_FIELD_S32(0x3D)
#define waypoint o->point
#define laps OBJECT_FIELD_S32(0x1E)

int mariolaps = 0;
void surfyboi(void) {
    f32 x, z, y;
    x = ((s16 *) segmented_to_virtual(bbh_area_3_spline_kooparacepathreal))[1 + waypoint];
    z = ((s16 *) segmented_to_virtual(bbh_area_3_spline_kooparacepathreal))[3 + waypoint];
    y = ((s16 *) segmented_to_virtual(bbh_area_3_spline_kooparacepathreal))[2 + waypoint];
    switch (o->oAction) {
        case 0:
            cur_obj_init_animation(7);
            // wait for approach
            if (!o->oHiddenBlueCoinSwitch) {
                o->oHiddenBlueCoinSwitch = spawn_object(o, MODEL_KOOPA_SHELL, bhvSurfShell);
                offsetChildByFloat(o->oHiddenBlueCoinSwitch, o, 0.0f, -300.f);
            }
            if (o->oBehParams2ndByte) {
                o->oAction = 4;
                o->oGraphYOffset = 50.f;
                cur_obj_init_animation(12);
                gHudDisplay.flags |= HUD_DISPLAY_FLAG_TIMER;
                sTimerRunning = 1;
            }
            if (o->oSubAction) {
                switch (askMario(48, 1)) {
                    case 0:
                        break;
                    case 1:
                        o->oAction = 2;
                        break;
                    case 2:
                        o->oAction = 1;
                        break;
                }
            } else {
                if (o->oDistanceToMario < 300) {
                    o->oSubAction = 1;
                }
            }
            break;
        case 1:
            // call coward
            if (talkToMario(49)) {
                o->oAction = 9;
            }
            break;
        case 2:
            // explain rules
            if (talkToMario(50)) {
                o->oAction = 3;
                o->oMoveAngleYaw = atan2s(z - o->oPosZ, x - o->oPosX);
                o->oVelY = 40.f;
                o->oForwardVel = 20.f;
                mariolaps = 0;
                mariowaypoint = 0;
                sequence_player_unlower(SEQ_PLAYER_LEVEL, 60);
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_RACE), 0);
            }
            break;
        case 3:
            cur_obj_init_animation(12);
            // jump on shell and into water
            if (o->oTimer == 14) {
                o->oAction = 4;
                o->oPosY -= 50.f;
                o->oGraphYOffset = 50.f;
                // warp to the subarea
                level_trigger_warp(m, WARP_OP_WARP_FLOOR);
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x14, 0x7f, 0x7f, 0xff);
                sSourceWarpNodeId = 0x1B;
            }
            break;
        case 4:
            // race towards next racepoint
            if (!(o->oTimer & 7)) {
                spawn_object(o, MODEL_IDLE_WATER_WAVE, bhvObjectWaterWave);
            }
            o->oFaceAngleYaw =
                approach_s16_symmetric(o->oFaceAngleYaw, o->oMoveAngleYaw - 0x4000, 0x400);

            o->oForwardVel = approach_f32_symmetric(
                o->oForwardVel, 90.f + (((mariowaypoint - 1) * 8) - waypoint) * 2.f - waypoint * 0.5f,
                1.0f); // todo: rubberbanding
            if (o->oBehParams2ndByte) {
                o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw,
                                                          atan2s(z - o->oPosZ, x - o->oPosX), 0x0400);
                if (!mariolaps) {
                    if (gMarioState->action & ACT_FLAG_SWIMMING) {

                        level_trigger_warp(m, WARP_OP_WARP_FLOOR);
                    }
                }
            }
            if (sqrtf((x - o->oPosX) * (x - o->oPosX) + (z - o->oPosZ) * (z - o->oPosZ)) < 200.f) {
                waypoint += 4;
                if (waypoint == 56) {
                    waypoint = 0;
                    o->laps++;
                    if (o->laps == 1) {
                        o->oAction = 10;
                        o->oMoveAngleYaw = -0x8000;
                        o->oPosY += 50.f;
                        o->oGraphYOffset = 0.f;
                        o->oVelY = 50.f;
                        o->oForwardVel = 48.f;
                    }
                }
            }
            break;
        case 5:
            // wait at end of race
            o->oVelY = 0.f;
            cur_obj_init_animation(7);
            if (o->oDistanceToMario < 300) {
                o->oAction = o->oBehParams2ndByte;
            }
            break;
        case 6:
            // taunt for losing
            if (talkToMario(51)) {
                o->oAction = 8;
                level_trigger_warp(m, WARP_OP_WARP_FLOOR);
            }
            break;
        case 7:
            // get surprised for winning
            if (talkToMario(52)) {
                o->oAction = 8;
                spawn_default_star(gMarioState->pos[0], gMarioState->pos[1] + 200.0f,
                                   gMarioState->pos[2]);
            }
            break;
        case 8:
            // gave star, race over, go home mario
            break;
        case 9:
            // wait for actions to reset to 0
            if (o->oDistanceToMario > 700) {
                o->oAction = 0;
            }
            break;
        case 10:
            // jump onto ship
            if (o->oTimer == 25) {
                o->oForwardVel = 0.f;
                o->oAction = 5;
            }
            if (mariolaps >= 1) {
                o->oBehParams2ndByte = 7;
            } else {
                o->oBehParams2ndByte = 6;
            }
            break;
    }
    cur_obj_update_floor_and_walls();
    cur_obj_move_standard(-78);
    if (o->oAction == 4) {
        obj_copy_pos_and_angle(o->oHiddenBlueCoinSwitch, o);
    } else {
        o->oFaceAngleYaw = o->oMoveAngleYaw;
    }
    if ((o->oAction == 4) || (o->oAction == 10) || (o->oAction == 5)) {
        /*   print_text_fmt_int(8, 0x10, "LAPS %d", mariolaps);
           print_text_fmt_int(8, 0x1e, "Koopa %d", o->laps);*/
    }
}

// increase mariolaps whenever this hits 3

void wayyyy(void) {
    if ((o->oDistanceToMario < 1500.f) && (o->oBehParams == mariowaypoint)) {
        mariowaypoint++;
        if (mariowaypoint == 7) {
            mariolaps++;
            sTimerRunning = 0;
            // play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gDefaultSoundArgs);
            play_music(SEQ_PLAYER_LEVEL, SEQ_EVENT_RACE, 0);
            // kill jetski
            if (cur_obj_nearest_object_with_behavior(bhvJetski2)) {
                spawn_object(cur_obj_nearest_object_with_behavior(bhvJetski2), 0,
                             bhvMistCircParticleSpawner);
                cur_obj_nearest_object_with_behavior(bhvJetski2)->activeFlags = 0;
                gMarioState->action = ACT_DIVE;
                gMarioState->vel[1] = 35.f;
                gMarioState->forwardVel = -15.f;
            }
        }
    }
}

// 6x96 I4 sheet of animframes
u8 animFrames[6 * 3 * 32] = {
    0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 0x00,
    0x00, 0x00, 0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 0x01, 0x11,
    0x11, 0x00, 0x00, 0x00, 0x02, 0x22, 0x22, 0x02, 0x22, 0x22, 0x02, 0x22, 0x22, 0x02, 0x22, 0x22,
    0x02, 0x22, 0x22, 0x00, 0x00, 0x00, 0x03, 0x33, 0x33, 0x03, 0x33, 0x33, 0x03, 0x33, 0x33, 0x03,
    0x33, 0x33, 0x03, 0x33, 0x33, 0x00, 0x00, 0x00, 0x04, 0x44, 0x44, 0x04, 0x44, 0x44, 0x04, 0x44,
    0x44, 0x04, 0x44, 0x44, 0x04, 0x44, 0x44, 0x00, 0x00, 0x00, 0x05, 0x55, 0x55, 0x05, 0x55, 0x55,
    0x05, 0x55, 0x55, 0x05, 0x55, 0x55, 0x05, 0x55, 0x55, 0x00, 0x00, 0x00, 0x06, 0x66, 0x66, 0x06,
    0x66, 0x66, 0x06, 0x66, 0x66, 0x06, 0x66, 0x66, 0x06, 0x66, 0x66, 0x00, 0x00, 0x00, 0x07, 0x77,
    0x77, 0x07, 0x77, 0x77, 0x07, 0x77, 0x77, 0x07, 0x77, 0x77, 0x07, 0x77, 0x77, 0x00, 0x00, 0x00,
    0x08, 0x88, 0x88, 0x08, 0x88, 0x88, 0x08, 0x88, 0x88, 0x08, 0x88, 0x88, 0x08, 0x88, 0x88, 0x00,
    0x00, 0x00, 0x09, 0x99, 0x99, 0x09, 0x99, 0x99, 0x09, 0x99, 0x99, 0x09, 0x99, 0x99, 0x09, 0x99,
    0x99, 0x00, 0x00, 0x00, 0x0b, 0xbb, 0xbb, 0x0b, 0xbb, 0xbb, 0x0b, 0xbb, 0xbb, 0x0b, 0xbb, 0xbb,
    0x0b, 0xbb, 0xbb, 0x00, 0x00, 0x00, 0x0c, 0xcc, 0xcc, 0x0c, 0xcc, 0xcc, 0x0c, 0xcc, 0xcc, 0x0c,
    0xcc, 0xcc, 0x0c, 0xcc, 0xcc, 0x00, 0x00, 0x00, 0x0d, 0xdd, 0xdd, 0x0d, 0xdd, 0xdd, 0x0d, 0xdd,
    0xdd, 0x0d, 0xdd, 0xdd, 0x0d, 0xdd, 0xdd, 0x00, 0x00, 0x00, 0x0e, 0xee, 0xee, 0x0e, 0xee, 0xee,
    0x0e, 0xee, 0xee, 0x0e, 0xee, 0xee, 0x0e, 0xee, 0xee, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x0f,
    0xff, 0xff, 0x0f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x0f, 0xff,
    0xff, 0x0f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x00, 0x00, 0x00,
    0x0f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x00,
    0x00, 0x00, 0x0e, 0xee, 0xee, 0x0e, 0xee, 0xee, 0x0e, 0xee, 0xee, 0x0e, 0xee, 0xee, 0x0e, 0xee,
    0xee, 0x00, 0x00, 0x00, 0x0d, 0xdd, 0xdd, 0x0d, 0xdd, 0xdd, 0x0d, 0xdd, 0xdd, 0x0d, 0xdd, 0xdd,
    0x0d, 0xdd, 0xdd, 0x00, 0x00, 0x00, 0x0c, 0xcc, 0xcc, 0x0c, 0xcc, 0xcc, 0x0c, 0xcc, 0xcc, 0x0c,
    0xcc, 0xcc, 0x0c, 0xcc, 0xcc, 0x00, 0x00, 0x00, 0x0b, 0xbb, 0xbb, 0x0b, 0xbb, 0xbb, 0x0b, 0xbb,
    0xbb, 0x0b, 0xbb, 0xbb, 0x0b, 0xbb, 0xbb, 0x00, 0x00, 0x00, 0x09, 0x99, 0x99, 0x09, 0x99, 0x99,
    0x09, 0x99, 0x99, 0x09, 0x99, 0x99, 0x09, 0x99, 0x99, 0x00, 0x00, 0x00, 0x08, 0x88, 0x88, 0x08,
    0x88, 0x88, 0x08, 0x88, 0x88, 0x08, 0x88, 0x88, 0x08, 0x88, 0x88, 0x00, 0x00, 0x00, 0x07, 0x77,
    0x77, 0x07, 0x77, 0x77, 0x07, 0x77, 0x77, 0x07, 0x77, 0x77, 0x07, 0x77, 0x77, 0x00, 0x00, 0x00,
    0x06, 0x66, 0x66, 0x06, 0x66, 0x66, 0x06, 0x66, 0x66, 0x06, 0x66, 0x66, 0x06, 0x66, 0x66, 0x00,
    0x00, 0x00, 0x05, 0x55, 0x55, 0x05, 0x55, 0x55, 0x05, 0x55, 0x55, 0x05, 0x55, 0x55, 0x05, 0x55,
    0x55, 0x00, 0x00, 0x00, 0x04, 0x44, 0x44, 0x04, 0x44, 0x44, 0x04, 0x44, 0x44, 0x04, 0x44, 0x44,
    0x04, 0x44, 0x44, 0x00, 0x00, 0x00, 0x03, 0x33, 0x33, 0x03, 0x33, 0x33, 0x03, 0x33, 0x33, 0x03,
    0x33, 0x33, 0x03, 0x33, 0x33, 0x00, 0x00, 0x00, 0x02, 0x22, 0x22, 0x02, 0x22, 0x22, 0x02, 0x22,
    0x22, 0x02, 0x22, 0x22, 0x02, 0x22, 0x22, 0x00, 0x00, 0x00, 0x01, 0x11, 0x11, 0x01, 0x11, 0x11,
    0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

};
#define STARCOUNTMAX 16
s16 starInfo[3][STARCOUNTMAX];
void generateNightSky(u8 *texture) {
    u32 i;
    u32 j, k;
    for (i = 0; i < STARCOUNTMAX; i++) {
        if (starInfo[2][i] == -1) {
            if (!(random_u16() & 7)) {
                starInfo[0][i] = random_u16() & 0x3F;
                starInfo[1][i] = random_u16() & 0x3F;
                starInfo[2][i] = 0;
            }
        } else {
            starInfo[2][i]++;
            if (starInfo[2][i] == 32) {
                starInfo[2][i] = -1;
            }
        }
    }
    for (i = 0; i < 64 * 64 / 8; i++) {
        ((u32 *) (texture))[i] = 0;
    }
    for (i = 0; i < STARCOUNTMAX; i++) {
        if (starInfo[2][i] != -1) {
            for (k = 0; k < 6; k++) {
                texture[(starInfo[0][i] + (starInfo[1][i] + k) * 32) % 2048] =
                    animFrames[(starInfo[2][i]) * 18 + k * 3];
                texture[(starInfo[0][i] + (starInfo[1][i] + k) * 32 + 1) % 2048] =
                    animFrames[(starInfo[2][i]) * 18 + k * 3 + 1];
                texture[(starInfo[0][i] + (starInfo[1][i] + k) * 32 + 2) % 2048] =
                    animFrames[(starInfo[2][i]) * 18 + k * 3 + 2];
            }
        }
    }
}

extern u8 bitfs_dl_Unbenannt_i4[];
extern u8 bitdw_dl_Unbenannt_i4[];
extern Gfx mat_hmc_dl_TIKIWATER_layer7[];
extern Vtx hmc_dl_Tikiwatwat_mesh_layer_7_vtx_0[825];
u16 watervertcount2 = sizeof(hmc_dl_Tikiwatwat_mesh_layer_7_vtx_0) / 0x10;
u16 waterphase = 0;
void textureanim(void) {
    int i;
    int j;
    Gfx *b;
    Vtx *a = segmented_to_virtual(hmc_dl_Tikiwatwat_mesh_layer_7_vtx_0);
    Gfx *scrollMaterial = segmented_to_virtual(mat_hmc_dl_TIKIWATER_layer7);
    u8 *nightSky = segmented_to_virtual(bitdw_dl_Unbenannt_i4);
    int old;
    switch (o->oBehParams2ndByte) {
        case 0:
#define SCROLLBITFLAG _SHIFTL(0xFFF, 12, 12)
#define SCROLLBITFLAG2 _SHIFTL(0xFFF, 0, 12)
            old = (scrollMaterial[21].words.w0 & SCROLLBITFLAG) >> 12;
            scrollMaterial[21].words.w0 =
                ((scrollMaterial[21].words.w0 & (~SCROLLBITFLAG)) | _SHIFTL(old + 1, 12, 12));

            old = (scrollMaterial[13].words.w0 & SCROLLBITFLAG) >> 12;
            scrollMaterial[13].words.w0 =
                ((scrollMaterial[13].words.w0 & (~SCROLLBITFLAG)) | _SHIFTL(old - 1, 12, 12));

            old = (scrollMaterial[13].words.w0 & SCROLLBITFLAG2) >> 0;
            scrollMaterial[13].words.w0 =
                ((scrollMaterial[13].words.w0 & (~SCROLLBITFLAG2)) | _SHIFTL(old + 1, 0, 12));
            waterphase += 0x200;
            if (!o->oTimer) {
                for (i = 0; i < watervertcount2; i++) {
                    a[i].n.flag = a[i].n.ob[1];
                }
            }
#define SCROLLSIZE 8
#define WAVEHEIGHTMAX (30.f)
            for (i = 0; i < watervertcount2; i++) {
                a[i].n.ob[1] = a[i].n.flag
                               + sins(a[i].n.ob[0] * SCROLLSIZE + waterphase) * WAVEHEIGHTMAX
                               + sins(a[i].n.ob[2] * SCROLLSIZE + waterphase + 0x2000) * WAVEHEIGHTMAX;
            }
            break;
        case 1:
            if (gCurrLevelNum == LEVEL_BITDW) {
                generateNightSky(nightSky);
            } else {
                nightSky = segmented_to_virtual(bitfs_dl_Unbenannt_i4);
                generateNightSky(nightSky);
            }
            break;
    }
}

// bhvExplosion
void bombthing(void) {
    if (cur_obj_dist_to_nearest_object_with_behavior(bhvExplosion) < 700.f) {
        create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
        obj_explode_and_spawn_coins(80.0f, 0);
    }
}

#define DOWNMOVEMENT 255.f
void warpPipeOWCode(void) {
    // bparam4: starrequirement
    if (!o->oTimer) {
        if (gCurrLevelNum == LEVEL_CASTLE_GROUNDS) {
            if ((gMarioState->numStars + 5) < (o->oBehParams & 0xFF)) {
                o->oPosY -= DOWNMOVEMENT;
                o->oIntangibleTimer = -1;
            } else if (gMarioState->numStars < (o->oBehParams & 0xFF)) {
                o->oPosY += DOWNMOVEMENT * ((gMarioState->numStars - (o->oBehParams & 0xFF))) / 5.f;
                o->oIntangibleTimer = -1;
            }
        }
    }
    // add bouncey animation
    if (gCurrLevelNum == LEVEL_CASTLE_GROUNDS) {
        if (!o->oIntangibleTimer) {
            switch (o->oOpacity) {
                case 0:
                    if (!o->oHiddenBlueCoinSwitch) {
                        o->oHiddenBlueCoinSwitch = spawn_object(o, MODEL_NUMBER, bhvStaticObject);
                        o->oHiddenBlueCoinSwitch->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
                        o->oHiddenBlueCoinSwitch->oAnimState = (o->oBehParams2ndByte - 16) % 10;
                        if ((o->oBehParams2ndByte - 16) > 9) {
                            o->oBooParentBigBoo = spawn_object(o, MODEL_NUMBER, bhvStaticObject);
                            o->oBooParentBigBoo->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
                            o->oBooParentBigBoo->oAnimState = 1;
                        }
                        obj_scale(o->oHiddenBlueCoinSwitch, 0);
                    }
                    obj_scale(o->oHiddenBlueCoinSwitch,
                              approach_f32_symmetric(o->oHiddenBlueCoinSwitch->header.gfx.scale[0], 0.f,
                                                     0.05f));

                    if (o->oDistanceToMario < 500.f) {
                        o->oOpacity = 1;
                    }
                    break;
                case 1:

                    o->oBobombBuddyPosYCopy = approach_f32_asymptotic(
                        o->oBobombBuddyPosYCopy, 1.f - o->oHiddenBlueCoinSwitch->header.gfx.scale[0],
                        .15f);
                    o->oBobombBuddyPosYCopy *= .9f;
                    obj_scale(o->oHiddenBlueCoinSwitch,
                              o->oHiddenBlueCoinSwitch->header.gfx.scale[0] + o->oBobombBuddyPosYCopy);

                    if (o->oDistanceToMario > 500.f) {
                        o->oOpacity = 0;
                    }
                    break;
            }
        }
        if (o->oHiddenBlueCoinSwitch) {
            o->oHiddenBlueCoinSwitch->oPosY =
                o->oPosY - 50.f + o->oHiddenBlueCoinSwitch->header.gfx.scale[0] * 350.f;
            if ((o->oBehParams2ndByte - 16) > 9) {
                o->oHiddenBlueCoinSwitch->oPosX =
                    o->oPosX
                    + sins(newcam_yaw + 0x4000) * 30.f * o->oHiddenBlueCoinSwitch->header.gfx.scale[0];
                o->oHiddenBlueCoinSwitch->oPosZ =
                    o->oPosZ
                    + coss(newcam_yaw + 0x4000) * 30.f * o->oHiddenBlueCoinSwitch->header.gfx.scale[0];
            }
            if (o->oBooParentBigBoo) {
                obj_scale(o->oBooParentBigBoo, o->oBooParentBigBoo->header.gfx.scale[0]);
                o->oBooParentBigBoo->oPosY = o->oHiddenBlueCoinSwitch->oPosY;
                o->oBooParentBigBoo->oPosX = o->oPosX - (o->oHiddenBlueCoinSwitch->oPosX - o->oPosX);
                o->oBooParentBigBoo->oPosZ = o->oPosZ - (o->oHiddenBlueCoinSwitch->oPosZ - o->oPosZ);
            }
        }
    }
}

void toadlawyer(void) {
    s32 i;
    if (save_file_get_total_star_count(gCurrSaveFileNum - 1, 0, 0x18) < 50) {
        obj_mark_for_deletion(o);
        return;
    }
    cur_obj_scale(1.5f);
    switch (o->oAction) {
        case 0:
            // wait mario close
            if (o->oDistanceToMario < 400.f) {
                o->oAction = 1;
            }
            break;
        case 1:
            // talk, ask if want to enter
            switch (askMario(146, 0)) {
                case 0:
                    break;
                case 1:
                    o->oAction = 2; // warp too
                                    // level_trigger_warp(m, WARP_OP_CREDITS_END);
                    level_trigger_warp(m, WARP_OP_WARP_FLOOR);
                    play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x14, 0xff, 0xff, 0xff);
                    sSourceWarpNodeId = 0xCF;
                    break;
                case 2:
                    o->oAction = 3;
                    break;
            }
            break;
        case 2:
            // go to end credits, warp
            break;
        case 3:
            // wait mario far
            if (o->oDistanceToMario > 600.f) {
                o->oAction = 0;
            }
            break;
    }
}

void tutorialGuy(void) {
    s32 ok, j;
    switch (o->oAction) {
        case 0:
            // waitfor mario close
            if ((o->oDistanceToMario < 500.f)) {
                o->oAction++;
            }
            break;
        case 1:
            if (gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[0]) {
                if (talkToMario(4)) {
                    o->oAction++;
                    pickpoke = 1;
                    blackmarketselection = 0;
                    ok = 0;
                    for (j = 0; (j < 11) && !ok; j++) {
                        if (gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[0]
                            & (1 << ((yoshiselected) % 11))) {
                            ok = 1;
                        } else {
                            yoshiselected++;
                            if (yoshiselected > 10) {
                                yoshiselected = 0;
                            }
                        }
                    }
                }
            } else {
                if (talkToMario(3)) {
                    o->oAction = 4;
                }
            }
            // display text box
            break;
        case 2:
            // show shop menu
            if (!pickpoke) {
                o->oAction++;
            }
            break;
        case 3:
            // show last text
            // if (yoshiselected) {
            if (talkToMario(5)) {
                o->oAction++;
                level_trigger_warp(m, WARP_OP_WARP_FLOOR);
                play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 0x14, 0xCf, 0xCf, 0xff);
                sSourceWarpNodeId = 0xC0 + yoshiselected;
            }

            /* } else {
                 o->oAction++;
             }*/
            break;
        case 4:
            // wait mario far
            if ((o->oDistanceToMario < 700.f)) {
            } else {
                o->oAction = 0;
            }
            break;
    }
}

struct Object *find_obj_with_bparam2(u32 bParam) {
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvCourtActor);
    struct Object *obj;
    struct ObjectNode *listHead;

    listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr) {
            if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
                if ((obj->oBehParams2ndByte) == bParam) {
                    return obj;
                }
            }
        }
        obj = (struct Object *) obj->header.next;
    }
    return 0;
}

extern const struct Animation *const waluigi_anims[];
extern const struct Animation *const courtDK_anims[];
extern const struct Animation *const toadlawyertw_anims[];
extern const struct Animation *const wariocourt_anims[];
extern const struct Animation *const chain_chomp_seg6_anims_06025178[];
extern const struct Animation *const piranha_plant_seg6_anims_0601C31C[];
extern const struct Animation *const whomp_seg6_anims_06020A04[];
void *animDatas[] = { toadlawyertw_anims, courtDK_anims, wariocourt_anims, waluigi_anims,
                      chain_chomp_seg6_anims_06025178 };

extern s16 newcam_yaw_target;
extern s16 newcam_yaw;
extern u8 newcam_centering;
extern u16 newcam_distance;
extern f32 newcam_pos_target[3];
#define DKBREGH SOUND_PEACH_MARIO
#define TOADWHOA SOUND_PEACH_POWER_OF_THE_STARS
#define TOADYEAH SOUND_PEACH_THANKS_TO_YOU
#define WALUOWIE SOUND_PEACH_THANK_YOU_MARIO
#define WALUHAHA SOUND_PEACH_SOMETHING_SPECIAL
#define WARIOHURT SOUND_PEACH_BAKE_A_CAKE
#define WARIOLAUGH SOUND_PEACH_FOR_MARIO
struct CourtCut {
    u16 dialogID;
    u16 animID;
    s8 rightAnswer; //-1 for non question dialogs, play puzzle solved jingle or marios WOOOAOAAAAWWW
                    // sound depending on wether right or wrong
    u32 soundbits;
    u8 characterID; // 0,1,2,3 for the other actors, 255 for mario
    u8 extradelay;  // 0,1,2,3 for the other actors, 255 for mario
};
struct CourtCut introScene[] = {
    { 173, 0, -1, DKBREGH, 1, 0 },
    { 174, 0, -1, WARIOLAUGH, 2, 0 },
    { 175, 0, -1, WALUHAHA, 3, 0 },
    { 176, 0, -1, TOADYEAH, 0, 0 },
    { 177, MARIO_ANIM_CREDITS_WAVING, -1, SOUND_MARIO_MAMA_MIA, 255, 0 },
    { 178, 0, -1, DKBREGH, 1, 0 },
    { 179, 0, -1, TOADYEAH, 0, 0 },
    { 180, MARIO_ANIM_CREDITS_PEACE_SIGN, -1, SOUND_MARIO_YAHOO, 255, 0 },
    { 181, 0, -1, DKBREGH, 1, 0 },
    { 182, 0, -1, WARIOHURT, 2, 0 },
    { 183, 0, -1, WALUHAHA, 3, 0 },
    { 184, MARIO_ANIM_SOFT_BACK_KB, -1, SOUND_MARIO_OOOF, 255, 0 },
    { 185, 0, -1, WARIOLAUGH, 2, 0 },
    { 186, 0, 8, DKBREGH, 1, 0 },
    { 187, 0, -1, DKBREGH, 1, 35 },
    { 188, 0, -1, SOUND_GENERAL_CHAIN_CHOMP2, 4, 0 },
    { 189, 0, -1, WARIOHURT, 2, 0 },
    { 190, 0, -1, SOUND_GENERAL_CHAIN_CHOMP2, 4, 0 },
    { 191, 0, -1, WALUHAHA, 3, 0 },
    { 177, MARIO_ANIM_SOFT_BACK_KB, -1, SOUND_MARIO_MAMA_MIA, 255, 0 },
    { 192, 0, -1, WARIOLAUGH, 2, 0 },
    { 193, 0, -1, SOUND_GENERAL_CHAIN_CHOMP2, 4, 0 },
    { 195, 0, -1, DKBREGH, 1, 0 },
    { 194, 0, -1, WARIOHURT, 2, 0 },
    { 196, 0, -1, SOUND_GENERAL_CHAIN_CHOMP2, 4, 0 },
    { 197, 0, -1, DKBREGH, 1, 0 },
    { 198, 0, 2, TOADWHOA, 0, 0 },
    { 205, 0, -1, TOADYEAH, 0, 0 },
    { 206, MARIO_ANIM_SUMMON_STAR, -1, SOUND_MARIO_HERE_WE_GO, 255, 0 },
    { 207, 1, -1, WARIOHURT, 2, 0 },
    { 208, 0, -1, WALUHAHA, 3, 0 },
    { 209, 2, -1, DKBREGH, 1, 0 },
    { 210, 1, -1, WARIOHURT, 2, 0 },
    { 211, 1, -1, WALUOWIE, 3, 0 },
    { 212, MARIO_ANIM_ELECTROCUTION, -1, SOUND_MARIO_ON_FIRE, 255, 0 },
    { 213, 0, -1, WARIOLAUGH, 2, 0 },
    { 214, MARIO_ANIM_GROUND_BONK, -1, SOUND_MARIO_WAAAOOOW, 255, 0 },
    { 215, 0, -1, TOADYEAH, 0, 0 },
    { 216, 0, -1, DKBREGH, 1, 0 },
    { 217, 0, -1, WARIOLAUGH, 2, 0 },
    { 184, MARIO_ANIM_SOFT_BACK_KB, -1, SOUND_MARIO_OOOF, 255, 0 },
    { 218, 2, 8, DKBREGH, 1, 0 },
    { 221, 0, -1, DKBREGH, 1, 35 },
    { 219, 0, -1, SOUND_OBJ2_PIRANHA_PLANT_BITE, 4, 0 },
    { 220, 0, -1, DKBREGH, 1, 0 },
    { 222, 0, -1, WARIOLAUGH, 2, 0 },
    { 223, 0, -1, SOUND_OBJ2_PIRANHA_PLANT_BITE, 4, 0 },
    { 224, 0, -1, WARIOLAUGH, 2, 0 },
    { 225, 0, -1, SOUND_OBJ2_PIRANHA_PLANT_BITE, 4, 0 },
    { 177, MARIO_ANIM_SOFT_BACK_KB, -1, SOUND_MARIO_MAMA_MIA, 255, 0 },
    { 226, 0, -1, WALUHAHA, 3, 0 },
    { 227, 2, -1, DKBREGH, 1, 0 },
    { 228, 0, -1, TOADYEAH, 0, 0 },
    { 229, 0, -1, SOUND_OBJ2_PIRANHA_PLANT_BITE, 4, 0 },
    { 230, 0, 3, TOADWHOA, 0, 0 },
    { 231, 0, -1, TOADYEAH, 0, 0 },
    { 180, MARIO_ANIM_CREDITS_PEACE_SIGN, -1, SOUND_MARIO_YAHOO, 255, 0 },
    { 233, 2, -1, DKBREGH, 1, 0 },
    { 210, 1, -1, WARIOHURT, 2, 0 },
    { 211, 1, -1, WALUOWIE, 3, 0 },
    { 237, 0, -1, TOADYEAH, 0, 0 },
    { 238, 0, -1, DKBREGH, 1, 0 },
    { 239, 0, -1, WARIOLAUGH, 2, 0 },
    { 240, 0, -1, WALUHAHA, 3, 0 },
    { 241, 0, 8, DKBREGH, 1, 0 },
    { 242, 0, -1, DKBREGH, 1, 35 },
    { 243, 0, -1, SOUND_OBJ2_WHOMP_SOUND_SHORT, 4, 0 },
    { 245, 0, -1, WARIOLAUGH, 2, 0 },
    { 244, 0, -1, DKBREGH, 1, 0 },
    { 246, 0, -1, WARIOLAUGH, 2, 0 },
    { 247, 0, -1, SOUND_OBJ2_WHOMP_SOUND_SHORT, 4, 0 },
    { 248, 0, -1, WARIOLAUGH, 2, 0 },
    { 249, 0, -1, SOUND_OBJ2_WHOMP_SOUND_SHORT, 4, 0 },
    { 248, 0, -1, WARIOLAUGH, 2, 0 },
    { 249, 0, -1, SOUND_OBJ2_WHOMP_SOUND_SHORT, 4, 0 },
    { 250, 0, -1, WARIOHURT, 2, 0 },
    { 251, 0, -1, SOUND_OBJ2_WHOMP_SOUND_SHORT, 4, 0 },
    { 252, 1, -1, WARIOHURT, 2, 0 },
    { 253, 0, -1, SOUND_OBJ2_WHOMP_SOUND_SHORT, 4, 0 },
    { 177, MARIO_ANIM_SOFT_BACK_KB, -1, SOUND_MARIO_MAMA_MIA, 255, 0 },
    { 254, 1, -1, WARIOHURT, 2, 0 },
    { 212, MARIO_ANIM_ELECTROCUTION, -1, SOUND_MARIO_ON_FIRE, 255, 0 },
    { 255, 0, -1, DKBREGH, 1, 0 },
    { 256, 1, -1, WARIOHURT, 2, 0 },
    { 257, 0, -1, SOUND_OBJ2_WHOMP_SOUND_SHORT, 4, 0 },
    { 258, 0, -1, WARIOLAUGH, 2, 0 },
    { 259, 0, -1, DKBREGH, 1, 0 },
    { 260, 0, 4, TOADWHOA, 0, 0 },
    { 261, 0, -1, TOADYEAH, 0, 0 },
    { 180, MARIO_ANIM_CREDITS_PEACE_SIGN, -1, SOUND_MARIO_YAHOO, 255, 0 },
    { 262, 2, -1, DKBREGH, 1, 0 },
    { 263, 0, -1, SOUND_OBJ2_WHOMP_SOUND_SHORT, 4, 0 },
    { 264, 2, -1, DKBREGH, 1, 0 },
    { 254, 1, -1, WARIOHURT, 2, 0 },
    { 206, MARIO_ANIM_SUMMON_STAR, -1, SOUND_MARIO_HERE_WE_GO, 255, 0 },
    { 269, 1, -1, WALUOWIE, 3, 0 },
    { 270, 2, -1, DKBREGH, 1, 0 },
    { 254, 1, -1, WARIOHURT, 2, 0 },
    { 271, 0, -1, TOADYEAH, 0, 0 },
    { 272, 2, -1, DKBREGH, 1, 0 },
    { 273, 1, -1, WARIOHURT, 2, 0 },
    { 274, 2, 10, WALUOWIE, 3, 0 },

    { 198, 2, -1, SOUND_MARIO_YAHOO_WAHA_YIPPEE, 3, 255 },

    // failstate 3
    { 265, 0, -1, TOADYEAH, 0, 0 },
    { 266, 2, -1, DKBREGH, 1, 0 },
    { 267, 0, -1, SOUND_OBJ2_WHOMP_SOUND_SHORT, 4, 0 },
    { 268, 0, 9, TOADWHOA, 0, 0 },
    { 198, 0, -1, TOADWHOA, 0, 255 },
    { 198, 0, -1, TOADWHOA, 0, 0 },
    { 198, 0, -1, TOADWHOA, 0, 0 },
    { 198, 0, -1, TOADWHOA, 0, 0 },
    { 198, 0, -1, TOADWHOA, 0, 0 },
    { 198, 0, -1, TOADWHOA, 0, 0 },
    // failstate 2
    { 232, 0, -1, TOADYEAH, 0, 0 },
    { 200, MARIO_ANIM_MISSING_CAP, -1, SOUND_MARIO_HAHA, 255, 0 },
    { 234, 0, -1, WALUOWIE, 3, 0 },
    { 235, 0, -1, DKBREGH, 1, 0 },
    { 236, 0, 9, TOADWHOA, 0, 0 },
    { 204, 0, -1, TOADWHOA, 0, 255 },
    { 198, 0, -1, TOADWHOA, 0, 0 },
    { 198, 0, -1, TOADWHOA, 0, 0 },
    { 198, 0, -1, TOADWHOA, 0, 0 },
    { 198, 0, -1, TOADWHOA, 0, 0 },
    // failstate 1
    { 199, 0, -1, TOADYEAH, 0, 0 },
    { 200, MARIO_ANIM_MISSING_CAP, -1, SOUND_MARIO_HAHA, 255, 0 },
    { 201, 0, -1, WALUOWIE, 3, 0 },
    { 202, 0, -1, DKBREGH, 1, 0 },
    { 203, 0, -1, DKBREGH, 1, 0 },
    { 204, 0, 9, TOADWHOA, 0, 0 },
    { 204, 0, 9, TOADWHOA, 0, 255 },
    { 198, 0, -1, TOADWHOA, 0, 0 },
    { 198, 0, -1, TOADWHOA, 0, 0 },
    { 198, 0, -1, TOADWHOA, 0, 0 },
};
u16 sceneLength = sizeof(introScene) / sizeof(struct CourtCut);
extern s16 gDialogID;
extern s16 newcam_pitch;
extern s8 gLastDialogResponse;
extern s8 gDialogBoxState;
extern s8 gDialogBoxType;
extern s8 gDialogLineNum;
#define WAITTIME 20
void courtActor(void) {
    struct Object *focus;
    o->oAnimations = animDatas[o->oBehParams2ndByte];
    if (!o->oTimer) {
        gMarioState->actionState = MARIO_ANIM_FIRST_PERSON;
        o->oOpacity = 0;
        cur_obj_init_animation(0);
        o->oSubAction = 0;
    } else {
        cur_obj_init_animation(o->oOpacity);
        if (o->oBehParams2ndByte == 3 && o->oOpacity == 2) {
            o->oBubbaUnkFC++;
            if (o->oBubbaUnkFC == 60) {
                spawn_default_star(gMarioState->pos[0], gMarioState->pos[1] + 100.f,
                                   gMarioState->pos[2]);
                gMarioState->action = ACT_IDLE;
            }
        }
    }
    if (!o->oBehParams2ndByte) {
        // control scene;
        /*  print_text_fmt_int(20, 20, "%d", gDialogBoxState);
          print_text_fmt_int(20, 40, "%d", WAITTIME + introScene[o->oSubAction].extradelay);
          print_text_fmt_int(20, 60, "%d", o->oTimer);
        print_text_fmt_int(20, 80, "%d", gDialogLineNum);*/
        if (gDialogBoxState == 0) {
            if (o->oTimer > (WAITTIME + introScene[o->oSubAction].extradelay)) {
                if (!o->unused1) {
                    o->unused1 = 1;
                    gDialogBoxType = 0;
                    gDialogID = introScene[o->oSubAction].dialogID;
                    if (introScene[o->oSubAction].soundbits) {
                        play_sound(introScene[o->oSubAction].soundbits, gDefaultSoundArgs);
                    }
                    if ((introScene[o->oSubAction].rightAnswer == 3)
                        || (introScene[o->oSubAction].rightAnswer == 2)
                        || (introScene[o->oSubAction].rightAnswer == 4)) {
                        gLastDialogResponse = 1;
                    } else {
                    }
                }
            } else if ((introScene[o->oSubAction - 1].rightAnswer == 8)
                       && (o->oTimer == (WAITTIME - 14 + introScene[o->oSubAction].extradelay))) {
                play_transition(WARP_TRANSITION_FADE_FROM_COLOR, 14, 255, 255, 255);
                if (o->oSubAction < 25) {
                    find_obj_with_bparam2(4)->header.gfx.sharedChild =
                        gLoadedGraphNodes[MODEL_CHAIN_CHOMP];
                    animDatas[4] = chain_chomp_seg6_anims_06025178;
                    find_obj_with_bparam2(4)->oGraphYOffset += 50.f;
                    obj_scale(find_obj_with_bparam2(4), .7f);
                } else if (o->oSubAction < 55) {
                    find_obj_with_bparam2(4)->header.gfx.sharedChild =
                        gLoadedGraphNodes[MODEL_PIRANHA_PLANT];
                    animDatas[4] = piranha_plant_seg6_anims_0601C31C;
                    find_obj_with_bparam2(4)->oGraphYOffset -= 50.f;
                } else if (o->oSubAction < 100) {
                    find_obj_with_bparam2(4)->header.gfx.sharedChild = gLoadedGraphNodes[MODEL_WHOMP];
                    animDatas[4] = whomp_seg6_anims_06020A04;
                }
            } else if (introScene[o->oSubAction - 1].rightAnswer == 9) {
                level_trigger_warp(m, WARP_OP_DEATH);
            }
        } else if (gDialogBoxState == 3) {
            if (o->unused1) {
                if (introScene[o->oSubAction].rightAnswer == 8) {
                    play_transition(WARP_TRANSITION_FADE_INTO_COLOR, 14, 255, 255, 255);
                }
                o->unused1 = 0;
                o->oTimer = 1;
                if (introScene[o->oSubAction].rightAnswer == 2) {
                    if (gDialogLineNum == 2) {
                        play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gDefaultSoundArgs);
                        o->oSubAction++;
                    } else {
                        play_sound(SOUND_MENU_LET_GO_MARIO_FACE, gDefaultSoundArgs);
                        o->oSubAction = sceneLength - 10;
                    }
                } else if (introScene[o->oSubAction].rightAnswer == 3) {
                    if (gDialogLineNum == 1) {
                        play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gDefaultSoundArgs);
                        o->oSubAction++;
                    } else {
                        play_sound(SOUND_MENU_LET_GO_MARIO_FACE, gDefaultSoundArgs);
                        o->oSubAction = sceneLength - 20;
                    }
                } else if (introScene[o->oSubAction].rightAnswer == 4) {
                    if (gDialogLineNum == 2) {
                        play_sound(SOUND_GENERAL2_RIGHT_ANSWER, gDefaultSoundArgs);
                        o->oSubAction++;
                    } else {
                        play_sound(SOUND_MENU_LET_GO_MARIO_FACE, gDefaultSoundArgs);
                        o->oSubAction = sceneLength - 30;
                    }
                } else {
                    o->oSubAction++;
                }
            }
        }
    }
    focus = find_obj_with_bparam2(introScene[o->oSubAction].characterID);
    if (!focus) {
        focus = gMarioObject;
        gMarioState->actionState = introScene[o->oSubAction].animID;
    } else {
        focus->oOpacity = introScene[o->oSubAction].animID;
    }
    newcam_pos_target[0] = focus->oPosX;
    newcam_pos_target[1] = focus->oPosY + 150.f;
    newcam_pos_target[2] = focus->oPosZ;
    newcam_yaw_target = focus->oFaceAngleYaw;
    newcam_yaw = focus->oFaceAngleYaw;
    newcam_pitch = 0;
    newcam_centering = 1;
    newcam_distance = 350;
}

void bhv_explode(void) {
    if (cur_obj_dist_to_nearest_object_with_behavior(bhvExplosion) < 400.f) {
        create_sound_spawner(SOUND_GENERAL_WALL_EXPLOSION);
        o->oNumLootCoins = 2;
        obj_explode_and_spawn_coins(80.0f, 1);
    }
}

Gfx pipecolors[] = {
    gsDPSetPrimColor(255, 255, 00, 0x84, 255, 255),
    gsDPSetEnvColor(0x29, 255, 0, 255),
    gsSPEndDisplayList(),
    gsSPEndDisplayList(),

    gsDPSetPrimColor(0, 0, 0x00, 0x72, 0x04, 255),
    gsDPSetEnvColor(0x83, 0x47, 0x00, 255),
    gsSPEndDisplayList(),
    gsSPEndDisplayList(),

    gsDPSetPrimColor(0, 0, 0x00, 0xc0, 0x03, 255),
    gsDPSetEnvColor(0, 1, 255, 255),
    gsSPEndDisplayList(),
    gsSPEndDisplayList(),

    gsDPSetPrimColor(0, 0, 0xef, 255, 0, 255),
    gsDPSetEnvColor(255, 0x6a, 0, 255),
    gsSPEndDisplayList(),
    gsSPEndDisplayList(),

    gsDPSetPrimColor(0, 0, 0x82, 0xc2, 255, 255),
    gsDPSetEnvColor(0, 0x11, 255, 255),
    gsSPEndDisplayList(),
    gsSPEndDisplayList(),

    gsDPSetPrimColor(0, 0, 0, 0x68, 255, 255),
    gsDPSetEnvColor(0xd3, 0, 255, 255),
    gsSPEndDisplayList(),
    gsSPEndDisplayList(),

    gsDPSetPrimColor(0, 0, 0xff, 0, 14, 255),
    gsDPSetEnvColor(0x36, 0, 0, 255),
    gsSPEndDisplayList(),
    gsSPEndDisplayList(),

    gsDPSetPrimColor(0, 0, 0, 8, 34, 255),
    gsDPSetEnvColor(19, 0, 0xa3, 255),
    gsSPEndDisplayList(),
    gsSPEndDisplayList(),

    gsDPSetPrimColor(0, 0, 0x8b, 0, 255, 255),
    gsDPSetEnvColor(0xa3, 0x5b, 0, 255),
    gsSPEndDisplayList(),
    gsSPEndDisplayList(),

    gsDPSetPrimColor(0, 0, 0x81, 0x63, 0x3e, 255),
    gsDPSetEnvColor(0, 3, 0xb1, 255),
    gsSPEndDisplayList(),
    gsSPEndDisplayList(),
};
extern struct GraphNodeObject *gCurGraphNodeObject;
Gfx *geo_pipecolor(s32 callContext, struct GraphNode *b, Mat4 *mtx) {
    Gfx *gfx = NULL;
    struct Object *obj = (struct Object *) gCurGraphNodeObject;
    struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) b;
    if (callContext == GEO_CONTEXT_RENDER) {
        gfx = &pipecolors[(obj->oBehParams2ndByte - 0x11) * 4];
        asGenerated->fnNode.node.flags = (asGenerated->fnNode.node.flags & 0xFF) | (1 << 8);
    }
    return gfx;
}

#define O_VEL_INDEX 0x09
#define UNCLIMBABLE_FLOOR_NORMAL 0.25f
#define CLIP_Y (78.f)

/* oMoveFlags */
#define OBJ_MOVE_LANDED                (1 <<  0) // 0x0001
#define OBJ_MOVE_ON_GROUND             (1 <<  1) // 0x0002  // mutually exclusive to OBJ_MOVE_LANDED
#define OBJ_MOVE_LEFT_GROUND           (1 <<  2) // 0x0004
#define OBJ_MOVE_ENTERED_WATER         (1 <<  3) // 0x0008
#define OBJ_MOVE_AT_WATER_SURFACE      (1 <<  4) // 0x0010
#define OBJ_MOVE_EXIT_WATER      (1 <<  5) // 0x0020
#define OBJ_MOVE_IN_AIR                (1 <<  7) // 0x0080
#define OBJ_MOVE_HIT_WALL              (1 <<  9) // 0x0200
#define OBJ_MOVE_HIT_OOB              (1 << 10) // 0x0400
#define OBJ_MOVE_HAS_BOUNCED                    (1 << 13) // 0x2000
#define OBJ_MOVE_IN_WATER         (1 << 5) // 0x1000
void PerformActorMove(s32 bAllowWalkoff) {
    struct Surface *IntendedFloor;
    f32 IntendedFloorHeight;
    f32 DeltaFloorHeight;
    s32 bRanPastEdge;
    s32 i;
    f32 cos;
    f32 PrevX = o->oPosX;
    f32 PrevZ = o->oPosZ;
    f32 WaterLevel;
    f32 sin;
    // Compute current velocity and intended movement
    o->oVelX = o->oForwardVel * sins(o->oMoveAngleYaw);
    o->oVelZ = o->oForwardVel * coss(o->oMoveAngleYaw);
    o->oVelY += o->oGravity;
    o->oVelY = MAX(o->oVelY, -78.f);
    for (i = 0; i < 3; i++) {
        o->OBJECT_FIELD_F32(O_POS_INDEX + i) =
            o->OBJECT_FIELD_F32(O_POS_INDEX + i) + o->OBJECT_FIELD_F32(O_VEL_INDEX + i);
    }
    o->oMoveFlags &= ~OBJ_MOVE_HIT_WALL;
    if (cur_obj_resolve_wall_collisions()) {
        o->oMoveFlags |= OBJ_MOVE_HIT_WALL;
    }
    // Check whether we are moving to a legal position
    IntendedFloorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &IntendedFloor);
    DeltaFloorHeight = IntendedFloorHeight - o->oFloorHeight;
    o->oMoveFlags &= ~OBJ_MOVE_HIT_OOB;
    bRanPastEdge = (DeltaFloorHeight < 5.0f && !bAllowWalkoff)
                       && (DeltaFloorHeight < -CLIP_Y && (o->oMoveFlags & OBJ_MOVE_ON_GROUND));
    if (!IntendedFloor || IntendedFloorHeight < -32766.0f
        || IntendedFloor->normal.y < UNCLIMBABLE_FLOOR_NORMAL || bRanPastEdge) {
        o->oMoveFlags |= OBJ_MOVE_HIT_OOB;
        o->oPosX = PrevX;
        o->oPosZ = PrevZ;
    }
    o->oFloorHeight = IntendedFloorHeight;
    // Update grounded movement flags!
    o->oMoveFlags &= ~(OBJ_MOVE_HAS_BOUNCED | OBJ_MOVE_EXIT_WATER | OBJ_MOVE_LEFT_GROUND);
    if (o->oPosY < o->oFloorHeight) {
        if (o->oMoveFlags & (OBJ_MOVE_LANDED | OBJ_MOVE_ON_GROUND)) {
            o->oMoveFlags &= ~OBJ_MOVE_LANDED;
            o->oMoveFlags |= OBJ_MOVE_ON_GROUND;
        } else {
            o->oMoveFlags |= OBJ_MOVE_LANDED;
        }
        o->oPosY = o->oFloorHeight;
        if (o->oVelY < 0.0f) {
            o->oVelY *= o->oBounciness;
            if (o->oVelY > 5.0f) {
                o->oMoveFlags |= OBJ_MOVE_HAS_BOUNCED;
            }
        }
    } else {
        o->oMoveFlags &= ~OBJ_MOVE_LANDED;
        if (o->oMoveFlags & OBJ_MOVE_ON_GROUND) {
            o->oMoveFlags &= ~OBJ_MOVE_ON_GROUND;
            o->oMoveFlags |= OBJ_MOVE_LEFT_GROUND;
        } else {
            o->oMoveFlags |= OBJ_MOVE_IN_AIR;
        }
    }
    // update water movement flags!
    WaterLevel = find_water_level(o->oPosX, o->oPosZ);
    if (o->oPosY <= WaterLevel) {
        if (o->oMoveFlags & (OBJ_MOVE_ENTERED_WATER | OBJ_MOVE_IN_WATER)) {
            o->oMoveFlags &= ~OBJ_MOVE_ENTERED_WATER;
            o->oMoveFlags |= OBJ_MOVE_IN_WATER;
        } else {
            o->oMoveFlags |= OBJ_MOVE_ENTERED_WATER;
        }
        o->oVelY += o->oBuoyancy;
        o->oPosY += o->oBuoyancy;
        o->oVelY *= 0.93f;
    } else {
        o->oMoveFlags &= ~OBJ_MOVE_ENTERED_WATER;
        if (o->oMoveFlags & (OBJ_MOVE_IN_WATER)) {
            o->oMoveFlags &= ~OBJ_MOVE_IN_WATER;
            o->oMoveFlags |= OBJ_MOVE_EXIT_WATER;
        }
    }
    if (o->oMoveFlags & (OBJ_MOVE_ON_GROUND | OBJ_MOVE_MASK_IN_WATER)) {
        o->oForwardVel *= o->oFriction;
    }
}

void ResetInteraction(void) {
    o->oInteractStatus = 0;
}
void retropiranha(void) {
    if (!o->oHiddenBlueCoinSwitch) {
        o->oHiddenBlueCoinSwitch = spawn_object(o, 0, bhvEmptyHitbox);
        o->oHiddenBlueCoinSwitch->hitboxDownOffset = 100.f;
        o->oHiddenBlueCoinSwitch->hitboxRadius = 100.f;
        o->oHiddenBlueCoinSwitch->hitboxHeight = 200.f;
    }
    switch (o->oAction) {
        case 0:
            // wait then grow
            o->oAnimState = 0;
            o->oHiddenBlueCoinSwitch->oIntangibleTimer = -1;
            if (!o->oSubAction) {
                cur_obj_scale(0.25f);
                if (o->oDistanceToMario < sqr(750.f)) {
                    o->oSubAction = 1;
                }
            } else {
                cur_obj_scale(o->header.gfx.scale[0] + 0.05f);
                if (o->header.gfx.scale[0] >= 1.f) {
                    o->oAction = 1;
                }
            }
            break;
        case 1:
            // chomp
            o->oHiddenBlueCoinSwitch->oIntangibleTimer = 0;
            o->oHiddenBlueCoinSwitch->oInteractStatus = 0;
            o->oHiddenBlueCoinSwitch->oInteractType = INTERACT_DAMAGE;
            o->oHiddenBlueCoinSwitch->oDamageOrCoinValue = 2;
            o->oHiddenBlueCoinSwitch->oPosX = o->oPosX + sins(o->oFaceAngleYaw) * 175.f;
            o->oHiddenBlueCoinSwitch->oPosY = o->oPosY + 167.f;
            o->oHiddenBlueCoinSwitch->oPosZ = o->oPosZ + coss(o->oFaceAngleYaw) * 175.f;
            o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 0x0200);
            o->oAnimState = ((o->oTimer + 3) >> 2) & 1;
            if (!(o->oTimer & 7))
                cur_obj_play_sound_1(SOUND_OBJ2_PIRANHA_PLANT_BITE);
            if (o->oDistanceToMario > sqr(850.f)) {
                o->oAction = 2;
                o->oAnimState = 0;
            }
            break;
        case 2:
            // shrink
            o->oHiddenBlueCoinSwitch->oIntangibleTimer = -1;
            cur_obj_scale(o->header.gfx.scale[0] - 0.05f);
            if (o->header.gfx.scale[0] <= .3f) {
                o->oAction = 0;
            }
            break;
    }
}
extern const Trajectory thi_area_4_spline_LinePlatformPath1[];
extern const Trajectory thi_area_4_spline_LinePlatformPath2[];
extern const Trajectory thi_area_4_spline_LinePlatformPath3[];
#define SegmentedToVirtual(a) segmented_to_virtual(a)
#define PlaySFX(a) cur_obj_play_sound_1(a)
#define Solidify() load_object_collision_model()
#define cur_obj_move_using_vel() cur_obj_move_using_vel()
#define bParam1 (*((u8 *) &o->oBehParams))
#define bParam2 (*(((u8 *) &o->oBehParams)+1))
#define bParam3 (*(((u8 *) &o->oBehParams)+2))
#define bParam4 (*(((u8 *) &o->oBehParams)+3))
#define ObjbParam1(obj) (*((u8 *) &obj->oBehParams))
#define ObjbParam2(obj) (*(((u8 *) &obj->oBehParams)+1))
#define ObjbParam3(obj) (*(((u8 *) &obj->oBehParams)+2))
#define ObjbParam4(obj) (*(((u8 *) &obj->oBehParams)+3))
#define /*0x0F4*/ oObjPointer0 OBJECT_FIELD_OBJ(0x1B)
#define /*0x0F8*/ oObjPointer1 OBJECT_FIELD_OBJ(0x1C)
#define /*0x0FC*/ oObjPointer2 OBJECT_FIELD_OBJ(0x1D)
#define /*0x100*/ oObjPointer3 OBJECT_FIELD_OBJ(0x1E)
#define /*0x104*/ oObjPointer4 OBJECT_FIELD_OBJ(0x1F)
#define /*0x108*/ oObjPointer5 OBJECT_FIELD_OBJ(0x20)
#define /*0x10C*/ oObjPointer6 OBJECT_FIELD_OBJ(0x21)
#define /*0x10C*/ oObjPointer7 OBJECT_FIELD_OBJ(0x22)
Trajectory *trajectoryList[3] = { &thi_area_4_spline_LinePlatformPath1,
                                  &thi_area_4_spline_LinePlatformPath2 };

void lineplatform(void) {
    s16 *curPath = SegmentedToVirtual(trajectoryList[bParam2]);
    f32 x, z, y;
    switch (o->oAction) {
        case 0:
            if (cur_obj_is_mario_on_platform()) {
                o->oAction++;
                o->oBobombBuddyRole = o->oMoveAngleYaw;
                o->oOpacity += 4;
            }
            break;
        case 1:
            PlaySFX(SOUND_ENV_ELEVATOR1);
            o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 45.f, 2.f);
            x = curPath[1 + o->oOpacity] - o->oPosX;
            y = curPath[2 + o->oOpacity] - o->oPosY;
            z = curPath[3 + o->oOpacity] - o->oPosZ;
            o->oMoveAngleYaw = atan2s(z, x);
            if (sqrtf(z * z + x * x) < o->oForwardVel + 5.f) {
                o->oFaceAngleYaw = atan2s(z, x);
            }
            if (!o->oTimer) {
                o->oFaceAngleYaw = o->oMoveAngleYaw;
            }
            o->oMoveAnglePitch = -atan2s(sqrtf(z * z + x * x), y);
            if (sqrtf(x * x + y * y + z * z) < o->oForwardVel) {
                o->oOpacity += 4;
            }
            if (curPath[o->oOpacity] == -1) {
                o->oAction++;
            }
            break;
        case 2:
            o->oVelY -= 2.f;
            if (o->oVelY < -75.f) {
                o->oVelY = -75.f;
            }
            if (o->oTimer > 400) {
                o->oAction = 4;
            }
            if (o->oTimer > 20.f) {
                if (absf(o->oPosY - curPath[2 + o->oOpacity - 4]) < 75.f) {
                    o->oAction++;
                    o->oForwardVel = -o->oVelY;
                    goto keepGOING;
                }
            }
            break;
        case 3:
        keepGOING:
            PlaySFX(SOUND_ENV_ELEVATOR1);
            o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 45.f, 2.f);
            x = curPath[1 + o->oOpacity - 4] - o->oPosX;
            y = curPath[2 + o->oOpacity - 4] - o->oPosY;
            z = curPath[3 + o->oOpacity - 4] - o->oPosZ;
            o->oMoveAngleYaw = atan2s(z, x);
            if (sqrtf(z * z + x * x) < o->oForwardVel + 5.f) {
                o->oFaceAngleYaw = atan2s(z, x);
            }
            if (!o->oTimer) {
                o->oFaceAngleYaw = o->oMoveAngleYaw;
            }
            o->oMoveAnglePitch = -atan2s(sqrtf(z * z + x * x), y);
            if (sqrtf(x * x + y * y + z * z) < o->oForwardVel) {
                o->oOpacity -= 4;
            }
            if (o->oOpacity == 0) {
                o->oAction++;
            }
            break;
        case 4:
            o->oForwardVel = 0;
            o->oMoveAngleYaw = o->oBobombBuddyRole;
            o->oFaceAngleYaw = o->oMoveAngleYaw;
            o->oMoveAnglePitch = 0;
            o->oAction = 0;
            o->oPosX = o->oHomeX;
            o->oPosY = o->oHomeY;
            o->oPosZ = o->oHomeZ;
            o->oOpacity = 0;
            break;
    }
    o->oAngleVelYaw = (s16) (o->oMoveAngleYaw - o->oFaceAngleYaw);
    o->oFaceAngleYaw = o->oMoveAngleYaw;
    if (o->oAction != 2) {
        o->oVelY = sins(-o->oMoveAnglePitch) * o->oForwardVel;
        o->oVelX = coss(-o->oMoveAnglePitch) * sins(o->oMoveAngleYaw) * o->oForwardVel;
        o->oVelZ = coss(-o->oMoveAnglePitch) * coss(o->oMoveAngleYaw) * o->oForwardVel;
    }
    cur_obj_move_using_vel();
    Solidify();
}

void wallsword(void) {
    switch (o->oAction) {
        case 0:
            if (sqr(o->oDistanceToMario) < sqr(1500.f)) {
                o->oAction++;
            }
            break;
        case 1:
    if (o->oTimer % 2 == 0) {
        o->oPosY += 10.f;
    } else {
        o->oPosY -= 10.f;
    }
            if (o->oTimer > 20) {
                o->oAction++;
            }
            break;
        case 2:
            if (o->oTimer > 8) {
                o->oIntangibleTimer = 0;
            }
            o->oAngleVelYaw = approach_s16_symmetric(o->oAngleVelYaw, 0x1300, 0x80);
            o->oFaceAngleYaw += o->oAngleVelYaw;
            o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 40.f, 1.f);
            break;
    }
    o->oInteractStatus = 0;
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x100);
    if (o->oMoveFlags & (OBJ_MOVE_HIT_WALL | OBJ_MOVE_HIT_OOB)) {
        spawn_mist_particles_with_sound(SOUND_OBJ_DEFAULT_DEATH);
    }
    PerformActorMove(1);
}

void rotatetunnel(void) {
    if (bParam2) {
        o->oAngleVelRoll = 0x080;
    } else {
        o->oAngleVelRoll = -0x080;
    }
    o->oFaceAngleRoll += o->oAngleVelRoll;
    if (absf(o->oPosX - gMarioState->pos[0]) < 1175) {
        Solidify();
    }
}

u8 blockUp = 0;

extern u8 PreviousRoom;
extern u8 CurrentRoom;
u32 checkFakeOut(f32 diffiCulty) {
    return ((random_u16() % 255) < diffiCulty);
}

void shyguysays(void) {
    f32 difficulty = (gMarioState->pos[0] + 8650.f) / 26900.f * 255.f;
    switch (o->oAction) {
        case 0:
            // wait for mario to approach
            cur_obj_init_animation(0);
            if (CurrentRoom == 5) {
                if (gMarioState->pos[0] > -8650.f) {
                    o->oAction = 1;
                }
            }
            break;
        case 1:
            // talk
            cur_obj_init_animation(0);
            if (talkToMario2(107, 4)) {
                o->oAction = 2;
                o->oHealth = 0;
            }
            o->oOpacity = 50;
            break;
        case 2:
            // float in front of mario and put flags
            o->oVelX += (gMarioState->pos[0] + 1000.f - o->oPosX) / 100.f;
            o->oVelZ += (gMarioState->pos[2] - o->oPosZ) / 100.f;
            o->oVelX *= 0.97f;
            o->oVelZ *= 0.97f;
#define MAXSPEED 60.f
            if (o->oVelX < -MAXSPEED) {
                o->oVelX = -MAXSPEED;
            } else if (o->oVelX > MAXSPEED) {
                o->oVelX = MAXSPEED;
            }
            if (o->oVelZ < -MAXSPEED) {
                o->oVelZ = -MAXSPEED;
            } else if (o->oVelZ > MAXSPEED) {
                o->oVelZ = MAXSPEED;
            }
            cur_obj_move_using_vel();
            if (o->oOpacity) {
                o->oOpacity--;
            }
            switch (o->oSubAction) {
                case 0:
                    cur_obj_init_animation(0);
                    if (!o->oOpacity) {
                        o->oSubAction = (random_u16() & 1) + 1;
                        o->oHealth = 0;
                    }
                    break;
                case 1:
                    cur_obj_init_animation(1);
                    if (o->header.gfx.unk38.animFrame == 18) {
                        if (checkFakeOut(difficulty - o->oHealth)) {
                            o->oSubAction = 3;
                        }
                    }
                    if (o->header.gfx.unk38.animFrame == 20) {
                        blockUp = 0;
                        PlaySFX(SOUND_OBJ_GOOMBA_ALERT);
                    }
                    if (cur_obj_check_if_at_animation_end()) {
                        o->oSubAction = 0;
                        o->oOpacity = random_u16() % 40 + 40 - difficulty / 10.f;
                    }
                    break;
                case 2:
                    cur_obj_init_animation(2);
                    if (o->header.gfx.unk38.animFrame == 18) {
                        if (checkFakeOut(difficulty - o->oHealth)) {
                            o->oSubAction = 4;
                        }
                    }
                    if (o->header.gfx.unk38.animFrame == 20) {
                        blockUp = 1;
                        PlaySFX(SOUND_OBJ_GOOMBA_ALERT);
                    }
                    if (cur_obj_check_if_at_animation_end()) {
                        o->oSubAction = 0;
                        o->oOpacity = random_u16() % 40 + 40 - difficulty / 10.f;
                    }
                    break;
                case 3:
                    o->header.gfx.unk38.animFrame -= 2;
                    if (o->header.gfx.unk38.animFrame < 3) {
                        o->oSubAction = 2;
                        o->oHealth += 20;
                    }
                    break;
                case 4:
                    o->header.gfx.unk38.animFrame -= 2;
                    if (o->header.gfx.unk38.animFrame < 3) {
                        o->oSubAction = 1;
                        o->oHealth += 20;
                    }
                    break;
            }
            if (gMarioState->pos[0] > 14786.f) {
                o->oAction = 3;
            }
            if (CurrentRoom != 5) {
                o->oVelX = 0;
                o->oVelZ = 0;
                o->oPosX = o->oHomeX;
                o->oPosZ = o->oHomeZ;
                o->oAction = 0;
            }
            break;
        case 3:
            cur_obj_init_animation(0);
            o->oPosX = approach_f32_asymptotic(o->oPosX, 16200.f, 0.05f);
            o->oPosZ = approach_f32_asymptotic(o->oPosZ, -1368.f, 0.05f);
            // wait at end
            if (CurrentRoom == 5) {
                if (gMarioState->pos[0] > 15086.f) {
                    o->oAction = 4;
                }
            }
            break;
        case 4:
            // talk at end
            if (talkToMario2(108, 4)) {
                o->oAction = 5;
            }
            break;
        case 5:
            // idle at end
            break;
    }
    o->oFaceAngleYaw = o->oAngleToMario;
}

void shyguyblock(void) {
    o->oAction = (blockUp == bParam2);
#define SWITCHTIMER 24
    if (!o->oAction) {
        if (o->oTimer == SWITCHTIMER) {
            o->oAnimState = 1 + bParam2 * 2;
        }
    } else {
        o->oAnimState = bParam2 * 2;
    }
    if (!(o->oAnimState & 1)) {
        Solidify();
    }
}

void shyguybed(void) {
    switch (o->oAction) {
        case 0:
            if (cur_obj_is_mario_on_platform()) {
                o->oAction = 1;
                o->oVelY = -20.f;
            }
            if (cur_obj_is_mario_ground_pounding_platform()) {
                o->oAction = 1;
                o->oVelY = -35.f;
            }
            break;
        case 1:
            if (o->oVelY > 0.f) {
                if (o->header.gfx.scale[1] < 1.f) {
                    set_mario_action(m, ACT_TRIPLE_JUMP, 0);
                }
            }
            if (!cur_obj_is_mario_on_platform()) {
                o->oAction = 0;
                set_mario_action(m, ACT_TRIPLE_JUMP, 0);
            }
            break;
    }
    o->header.gfx.scale[1] -= o->oVelY / 40.f;
    if (o->header.gfx.scale[1] < 0.f) {
        o->header.gfx.scale[1] = 0.f;
        o->oVelY = o->oVelY * -0.5f;
    }
    o->oVelY += (o->header.gfx.scale[1] - 1.f) * 3.5f;
    o->oVelY *= 0.93f;
    Solidify();
}
struct DynaPolyInfo {
    f32 Speed;
    s16 InitialCoordinate;
    s16 Padding;
};
// mark fixed vertices with valpha = 0!
void DynaPolyCollisionUpdate(Vtx *VisualVTX, s32 VertCount, f32 ImpactSize, f32 ImpactStrength,
                             f32 Snappiness, f32 Resistance, struct DynaPolyInfo *VertSpeedArray) {
    s16 *coll = o->collisionData;
    f32 RelativeX = gMarioState->pos[0] - o->oPosX;
    f32 RelativeZ = gMarioState->pos[2] - o->oPosZ;
    f32 x, y;
    s32 i;
    f32 Strength;

    if (cur_obj_is_mario_on_platform()) {
         Strength =
            cur_obj_is_mario_ground_pounding_platform() ? ImpactStrength * 2.f : ImpactStrength;
        for (i = 0; i < VertCount; i++) {
            if (VisualVTX[i].v.cn[3]) {
                x = RelativeX - VisualVTX[i].v.ob[0];
                y = RelativeZ - VisualVTX[i].v.ob[2];
                x = sqrtf(x * x + y * y);
                if (x < ImpactSize) {
                    VertSpeedArray[i].Speed -= Strength * (ImpactSize - x) / ImpactSize;
                }
            }
        }
    }
    for (i = 0; i < VertCount; i++) {
        if (VisualVTX[i].v.cn[3]) {
            VisualVTX[i].v.ob[1] += VertSpeedArray[i].Speed;
            VertSpeedArray[i].Speed +=
                (-(f32) VisualVTX[i].v.ob[1] + VertSpeedArray[i].InitialCoordinate)
                * (Snappiness
                   * ((sqrtf(absi(VisualVTX[i].v.ob[0]) + absi(VisualVTX[i].v.ob[2]))) / 14.f));
            VertSpeedArray[i].Speed -= 1.f;
            VertSpeedArray[i].Speed *= Resistance;
            coll[VisualVTX[i].v.flag * 3 + 3] = VisualVTX[i].v.ob[0];
            coll[VisualVTX[i].v.flag * 3 + 4] = VisualVTX[i].v.ob[1];
            coll[VisualVTX[i].v.flag * 3 + 5] = VisualVTX[i].v.ob[2];
        }
    }
    Solidify();
}

void DynaPolyCollisionInit(Vtx *VisualVTX, s32 VertCount, f32 ImpactSize, f32 ImpactStrength,
                           f32 Snappiness, f32 Resistance, struct DynaPolyInfo *VertSpeedArray) {
    s16 *coll = o->collisionData;
    s32 i, k;
    for (i = 0; i < VertCount; i++) {
        VertSpeedArray[i].Speed = 0;
        VertSpeedArray[i].InitialCoordinate = VisualVTX[i].v.ob[1];
        for (k = 0; k < VertCount; k++) {
            if (coll[k * 3 + 3] == VisualVTX[i].v.ob[0]) {
                if (coll[k * 3 + 4] == VisualVTX[i].v.ob[1]) {
                    if (coll[k * 3 + 5] == VisualVTX[i].v.ob[2]) {
                        VisualVTX[i].v.flag = k;
                    }
                }
            }
        }
    }
    s32 runCount = 255;
    for (; runCount > 0; runCount--) {
        DynaPolyCollisionUpdate(VisualVTX, VertCount, ImpactSize, ImpactStrength, Snappiness,
                                Resistance, VertSpeedArray);
    }
}
struct DynaPolyInfo vertSpeeds[10];
#define ROPEBRIDGE_VERTLIST ropebridge_Plane_031_mesh_layer_4_vtx_0
#define ROPEBRIDGE_VERTCOUNT (sizeof(ropebridge_Plane_031_mesh_layer_4_vtx_0) / 0x10)
#define ROPEBRIDGE_IMPACTSIZE 200.f
#define ROPEBRIDGE_IMPACTSTRENGTH 2.f
#define ROPEBRIDGE_SNAPPINESS 0.02f
#define ROPEBRIDGE_RESISTANCE 0.93f
void Ropebridge_Init(void) {
    DynaPolyCollisionInit(SegmentedToVirtual(ROPEBRIDGE_VERTLIST), ROPEBRIDGE_VERTCOUNT,
                          ROPEBRIDGE_IMPACTSIZE, ROPEBRIDGE_IMPACTSTRENGTH, ROPEBRIDGE_SNAPPINESS,
                          ROPEBRIDGE_RESISTANCE, vertSpeeds);
}
void Ropebridge(void) {
    DynaPolyCollisionUpdate(SegmentedToVirtual(ROPEBRIDGE_VERTLIST), ROPEBRIDGE_VERTCOUNT,
                            ROPEBRIDGE_IMPACTSIZE, ROPEBRIDGE_IMPACTSTRENGTH, ROPEBRIDGE_SNAPPINESS,
                            ROPEBRIDGE_RESISTANCE, vertSpeeds);
}


void pushbehavior(f32 xwall, f32 zwall, f32 ywall) {
    f32 x, y, z;
    u16 moveVec;
    f32 floorY;
    x = o->oPosX;
    y = o->oPosY;
    z = o->oPosZ;
#undef PUSHSPEED
#define PUSHSPEED 3.f
    /*xwall -= (PUSHSPEED-1.f);
    zwall -= (PUSHSPEED-1.f);*/
    xwall -= 1.f;
    zwall -= 1.f;
    if ((gMarioState->wall) && (gMarioState->wall->object == o)) {
        if (gMarioState->flags & MARIO_FLAG_PUSHING_WALL) {
            // play sound
            moveVec = (gMarioState->faceAngle[1] + 0x2000) & 0xC000;
            o->oPosX += sins(moveVec) * PUSHSPEED;
            o->oPosZ += coss(moveVec) * PUSHSPEED;
            m->pos[0] += sins(moveVec) * PUSHSPEED;
            m->pos[2] += coss(moveVec) * PUSHSPEED;
            floorY = find_floor_height(o->oPosX + xwall, y + ywall, o->oPosZ + zwall);
            if (absf(floorY - o->oPosY) > 10.f) {
                o->oPosX = x;
                o->oPosZ = z;
                goto nosound;
            }
            floorY = find_floor_height(o->oPosX + xwall, y + ywall, o->oPosZ - zwall);
            if (absf(floorY - o->oPosY) > 10.f) {
                o->oPosX = x;
                o->oPosZ = z;
                goto nosound;
            }
            floorY = find_floor_height(o->oPosX - xwall, y + ywall, o->oPosZ + zwall);
            if (absf(floorY - o->oPosY) > 10.f) {
                o->oPosX = x;
                o->oPosZ = z;
                goto nosound;
            }
            floorY = find_floor_height(o->oPosX - xwall, y + ywall, o->oPosZ - zwall);
            if (absf(floorY - o->oPosY) > 10.f) {
                o->oPosX = x;
                o->oPosZ = z;
                goto nosound;
            }
            PlaySFX(SOUND_ENV_METAL_BOX_PUSH);
        nosound:
        ;
        }
    }

    Solidify();
}

void pushthingy2(void) {
    o->oOpacity = 255 - (o->oPosZ - o->oHomeZ) * 0.6f;
    pushbehavior(186.f, 50.f, 186.f);
}

void pushthingy(void) {

    pushbehavior(200.f, 200.f, 1500.f);
}
static float const E = 2.718281828459f;
static float slow_logf(float x) {
    float p = 0.0f;
    float r = 0.0f, c = -1.0f;
    int i;

    if (x == 0.0f) {
        return -9999999999999999999999999999999999999999999999999999999.f;
    }
    while (x < 0.5f) {
        x *= E;
        ++p;
    }

    x -= 1.0f;
    for (i = 1; i < 8; ++i) {
        c *= -x;
        r += c / i;
    }
    return r - p;
}
static float slow_expf(float x) {
    float r = 1.0f, c = 1.0f;
    int i;
    x = -x;
    for (i = 1; i < 8; ++i) {
        c *= x / i;
        r += c;
    }
    return 1.0f / r;
}
float slow_powf(float base, float exponent) {
    if (base <= 0.0f) {
        return 0.0f;
    }
    return slow_expf(exponent * slow_logf(base));
}
#define scaleX o->header.gfx.scale[0]
#define scaleY o->header.gfx.scale[1]
#define scaleZ o->header.gfx.scale[2]
void jellyblock(void) {
    f32 PrevX = scaleX;
    f32 PrevZ = scaleZ;
    f32 x, y, z;
    f32 normalizing = 1.f;
    u16 moveVec;
    f32 floorY;
    x = o->oPosX;
    y = o->oPosY;
    z = o->oPosZ;
    if (cur_obj_is_mario_ground_pounding_platform()) {
        if (!o->oSubAction) {
            o->oOpacity = 12;
            PlaySFX(SOUND_OBJ_SPINY_UNK59);
        }
        o->oSubAction = 1;
        o->oAnimState = 2;
    } else {
        o->oSubAction = 0;
    }
    if (o->oOpacity > 0) {
        o->oOpacity--;
        if (o->oOpacity > 7) {
            o->oBobombBuddyPosYCopy = -0.075f;
            o->header.gfx.unk38.animFrame += 5;
        }
    }
    if (!o->oOpacity) {
        o->oAnimState = 0;
    }
    if (!(o->oBehParams & 0x0FF)) {
        if ((gMarioState->wall) && (gMarioState->wall->object == o)) {
            if (gMarioState->flags & MARIO_FLAG_PUSHING_WALL) {
                moveVec = (gMarioState->faceAngle[1] + 0x2000) & 0xC000;
#define PUSHSPEED 8.f
                o->oPosX += sins(moveVec) * PUSHSPEED * (scaleZ - 0.2f);
                o->oPosZ += coss(moveVec) * PUSHSPEED * (scaleX - 0.2f);
                m->pos[0] += sins(moveVec) * PUSHSPEED * (scaleZ - 0.2f);
                m->pos[2] += coss(moveVec) * PUSHSPEED * (scaleX - 0.2f);
                o->header.gfx.unk38.animFrame += 2;
                o->oAnimState = 1;
            }
        }
#define JELLYSIZE 175.f
        floorY = find_floor_height(x, y + 10.f, z);
        if (absf(floorY - o->oPosY) > scaleY * JELLYSIZE) {
            o->oPosX = x;
            o->oPosZ = z;
        }
        floorY = find_floor_height(x + JELLYSIZE * scaleZ, y + 10.f, z);
        if (absf(floorY - o->oPosY) > 10.f) {
            o->oBobombBuddyPosZCopy = (x - o->oPosX) / JELLYSIZE;
            o->oPosX = x;
        }
        floorY = find_floor_height(x - JELLYSIZE * scaleZ, y + 10.f, z);
        if (absf(floorY - o->oPosY) > 10.f) {
            o->oBobombBuddyPosZCopy = (x - o->oPosX) / JELLYSIZE;
            o->oPosX = x;
        }
        floorY = find_floor_height(x, y + 10.f, z + JELLYSIZE * scaleX);
        if (absf(floorY - o->oPosY) > 10.f) {
            o->oBobombBuddyPosXCopy = (z - o->oPosZ) / JELLYSIZE;
            o->oPosZ = z;
        }
        floorY = find_floor_height(x, y + 10.f, z - JELLYSIZE * scaleX);
        if (absf(floorY - o->oPosY) > 10.f) {
            o->oBobombBuddyPosXCopy = (z - o->oPosZ) / JELLYSIZE;
            o->oPosZ = z;
        }
    }
#define SLOWSCALE 50.f
#define MINSCALE 0.75f
    if (scaleX < MINSCALE) {
        o->oBobombBuddyPosXCopy += (1.f - scaleX) / SLOWSCALE;
    }
    if (scaleY < MINSCALE) {
        o->oBobombBuddyPosYCopy += (1.f - scaleY) / SLOWSCALE;
    }
    if (scaleZ < MINSCALE) {
        o->oBobombBuddyPosZCopy += (1.f - scaleZ) / SLOWSCALE;
    }
    scaleX += o->oBobombBuddyPosXCopy;
    scaleY += o->oBobombBuddyPosYCopy;
    scaleZ += o->oBobombBuddyPosZCopy;
    o->oBobombBuddyPosXCopy = 0;
    o->oBobombBuddyPosYCopy = 0;
    o->oBobombBuddyPosZCopy = 0;
    normalizing = scaleX * scaleY * scaleZ;
    normalizing = slow_powf(normalizing, 0.33333333333f);
    scaleX /= normalizing;
    scaleY /= normalizing;
    scaleZ /= normalizing;
    // move the block if its now blocking
    if (PrevX != scaleX) {
        floorY = find_floor_height(x, y + 10.f, z + JELLYSIZE * scaleX);
        if (absf(floorY - o->oPosY) > 10.f) {
            o->oPosZ += (PrevX - scaleX) * JELLYSIZE;
        }
        floorY = find_floor_height(x, y + 10.f, z - JELLYSIZE * scaleX);
        if (absf(floorY - o->oPosY) > 10.f) {
            o->oPosZ -= (PrevX - scaleX) * JELLYSIZE;
        }
    }
    if (PrevZ < scaleZ) {
        floorY = find_floor_height(x + JELLYSIZE * scaleZ, y + 10.f, z);
        if (absf(floorY - o->oPosY) > 10.f) {
            o->oPosX += (PrevZ - scaleZ) * JELLYSIZE;
        }
        floorY = find_floor_height(x - JELLYSIZE * scaleZ, y + 10.f, z);
        if (absf(floorY - o->oPosY) > 10.f) {
            o->oPosX -= (PrevZ - scaleZ) * JELLYSIZE;
        }
    }
    Solidify();
}

void DoubleDoor(void) {
    if (!o->oOpacity) {
        o->oOpacity = o->oFaceAngleYaw;
        o->oHiddenBlueCoinSwitch = cur_obj_nearest_object_with_behavior(bhvFloorSwitchHiddenObjects);
    }
    if (!o->oAction) {
        // rotate back to normal
        o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oOpacity, 0x200);
        if (o->oHiddenBlueCoinSwitch->oAction) {
            PlaySFX(SOUND_GENERAL_OPEN_WOOD_DOOR);
            o->oAction = 1;
        }
        if (gMarioState->pos[0] < o->oPosX && gMarioState->pos[1] < o->oPosY + 500.f) {
            o->oAction = 1;
        }
    } else {
        // open up
        o->oFaceAngleYaw =
            approach_s16_symmetric(o->oFaceAngleYaw, o->oOpacity + (bParam4 << 8), 0x200);
        if (!o->oHiddenBlueCoinSwitch->oAction) {
            if (gMarioState->pos[0] < o->oPosX && gMarioState->pos[1] < o->oPosY + 500.f) {
            } else {
                PlaySFX(SOUND_GENERAL_OPEN_WOOD_DOOR);
                o->oAction = 0;
            }
        }
    }
    Solidify();
}

void SetBarrelColor(void) {
    o->oAnimState = bParam4;
}
void destroybarrelcode(void) {
    if (!o->oAction) {
        if (cur_obj_is_mario_ground_pounding_platform()) {
            o->oAction = 1;
            o->oTimer = 0;
        }
        if (cur_obj_is_mario_on_platform()) {
            o->oVelY += 0.01f;
        }
        o->oVelY *= 0.9f;
        o->header.gfx.scale[1] -= o->oVelY;
        o->header.gfx.scale[0] = sqrtf(1.f / o->header.gfx.scale[1]);
        o->header.gfx.scale[2] = o->header.gfx.scale[0];
        o->oVelY -= (1.f - o->header.gfx.scale[1]) * 0.2f;
    } else {
#define MINSUB 0.1167f
        o->header.gfx.scale[1] -= MINSUB;
        o->header.gfx.scale[0] = sqrtf(1.f / o->header.gfx.scale[1]);
        o->header.gfx.scale[2] = o->header.gfx.scale[0];
        if (o->header.gfx.scale[1] < (MINSUB * 4)) {
            mark_obj_for_deletion(o);
            spawn_mist_particles_variable(20, 0, 46.f);
            spawn_triangle_break_particles(15, MODEL_DIRT_ANIMATION, 3.0f, 4);
            switch (bParam2) {
                case 0:
                    spawn_object(o, MODEL_YELLOW_COIN, bhvSingleCoinGetsSpawned);
                    break;
                case 1:
                    spawn_object(o, 0, bhvThreeCoinsSpawn);
                    break;
                case 2:
                    spawn_object(o, MODEL_BLUE_COIN, bhvMrIBlueCoin);
                    break;
                case 3:
                    spawn_object(o, 0, bhvTenCoinsSpawn);
                    break;
            }
        }
    }
    Solidify();
}
void crumblebridge(void) {
    s32 i, j;
    struct Object *coin;
    // spawn 5x4 grid 500x312.5f distance
    if (bParam2) {
        // spawn the thing
        if (!o->oAction) { /*
             for (i = 0; i < 5; i++) {
                 for (j = 0; j < 4; j++) {
                     spawn_objectAtLocation(o, 0x45, bhvCrumbleBridge,
 #define XRANGE 312.5f
 #define ZRANGE 500.f
                                               o->oPosX - XRANGE * 1.5f + j * XRANGE, o->oPosY,
                                               o->oPosZ + ZRANGE * 1.5f - ZRANGE * i);
                 }
             }*/
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 4; j++) {
                    spawn_object_abs_with_rot(o,0, 0x45, bhvCrumbleBridge,
#define SQUARESIZE 312.5f
                                              o->oPosX - j * SQUARESIZE, o->oPosY,
                                              o->oPosZ - SQUARESIZE * i,0,0,0);
                }
            }
            o->oAction = 1;
        } else {
            if (!cur_obj_nearest_object_with_behavior(bhvCrumbleBridge)) {
                if (o->oOpacity < 15) {
                    if (o->oOpacity == 14) {
                        play_puzzle_jingle();
                    }
                    coin = spawn_object_relative(0, 0, 600.f, 0, gMarioState->marioObj,
                                                 MODEL_YELLOW_COIN, bhvSingleCoinGetsSpawned);
                    coin->oCoinUnk110 = -60.f;
                    o->oOpacity++;
                } else {
                    mark_obj_for_deletion(o);
                }
            }
        }
    } else {
        o->oRoom = 2;
        if (o->oAction) {
            if (o->oTimer > 3) {
                if (o->oAngleVelPitch < 0x400)
                    o->oAngleVelPitch += 0x80;
                if (o->oAngleVelRoll > -0x400 && o->oAngleVelRoll < 0x400)
                    o->oAngleVelRoll += o->oTumblingBridgeUnkF4; // acceleration?
                o->oGravity = -3.0f;
                cur_obj_rotate_move_angle_using_vel();
                cur_obj_move_using_fvel_and_gravity();
                if (o->oTimer > 80) {
                    obj_mark_for_deletion(o);
                }
            } else if (o->oTimer == 3) {
                PlaySFX(SOUND_GENERAL_PLATFORM);
            }
        } else {
            if (cur_obj_is_mario_on_platform()) {
                o->oAction = 1;
                o->oTumblingBridgeUnkF4 = random_sign() * 0x80;
            }
        }
        Solidify();
    }
}
#define Flame1 OBJECT_FIELD_OBJ(0x1B)
#define Flame2 OBJECT_FIELD_OBJ(0x1C)
#define Flame3 OBJECT_FIELD_OBJ(0x1D)
#define Flame4 OBJECT_FIELD_OBJ(0x1E)
#define Flame5 OBJECT_FIELD_OBJ(0x1F)
#define Flame6 OBJECT_FIELD_OBJ(0x20)
#define Flame7 OBJECT_FIELD_OBJ(0x21)
#define Flame8 OBJECT_FIELD_OBJ(0x22)

void ChandelierInit(void) {
    s32 i;
    o->oAngleVelPitch = 0x40;
    for (i = 0; i < 8; i++) {
        o->OBJECT_FIELD_OBJ(0x1B + i) = spawn_object(o, MODEL_BLUE_FLAME, bhvFlameMedium);
        o->OBJECT_FIELD_OBJ(0x1B + i)->oBehParams = 0x02000000;
    }
}


void OffsetChildByTransform(struct Object *source, struct Object *target, float left, float up,
                            float forward) {
    // Calculate the direction vectors for the source object
    float forwardX = sins(source->oFaceAngleYaw) * coss(source->oFaceAnglePitch);
    float forwardY = sins(-source->oFaceAnglePitch);
    float forwardZ = coss(source->oFaceAngleYaw) * coss(source->oFaceAnglePitch);

    float leftX = sins(source->oFaceAngleYaw + 0x4000) * coss(source->oFaceAngleRoll);
    float leftY = sins(source->oFaceAngleRoll); // Assuming no roll
    float leftZ = coss(source->oFaceAngleYaw + 0x4000) * coss(source->oFaceAngleRoll);

    float upX = sins(source->oFaceAngleYaw) * sins(source->oFaceAnglePitch);
    float upY = coss(-source->oFaceAnglePitch);
    float upZ = coss(source->oFaceAngleYaw) * sins(source->oFaceAnglePitch);

    // Apply the offsets to the target object
    target->oPosX = source->oPosX + forward * forwardX + left * leftX + up * upX;
    target->oPosY = source->oPosY + forward * forwardY + left * leftY + up * upY;
    target->oPosZ = source->oPosZ + forward * forwardZ + left * leftZ + up * upZ;
}
void chandelier(void) {
    s32 i;
#define CANDLERADIUS 703.f
    for (i = 0; i < 8; i++) {
        OffsetChildByTransform(o, o->OBJECT_FIELD_OBJ(0x1B + i), sins(0x2000 * i) * CANDLERADIUS,
                                    -1069.f, coss(0x2000 * i) * CANDLERADIUS);
    }
    o->oAngleVelPitch -= o->oFaceAnglePitch / 1024;
    o->oFaceAngleYaw += 0x0020;
    o->oAngleVelYaw = 0x0020;
    o->oFaceAnglePitch += o->oAngleVelPitch;
    Solidify();
}
struct DynaPolyInfo DynaPolyVertSpeeds[100];
#define CATCHNET_VERTLIST Catchnet_bignet_mesh_layer_4_vtx_0
#define CATCHNET_VERTCOUNT 22
#define CATCHNET_IMPACTSIZE 600.f
#define CATCHNET_IMPACTSTRENGTH 1.5f
#define CATCHNET_SNAPPINESS 0.02f
#define CATCHNET_RESISTANCE 0.93f
void Catchnet_Init(void) {
    DynaPolyCollisionInit(SegmentedToVirtual(CATCHNET_VERTLIST), CATCHNET_VERTCOUNT,
                          CATCHNET_IMPACTSIZE, CATCHNET_IMPACTSTRENGTH, CATCHNET_SNAPPINESS,
                          CATCHNET_RESISTANCE, DynaPolyVertSpeeds);
}
void Catchnet(void) {
    DynaPolyCollisionUpdate(SegmentedToVirtual(CATCHNET_VERTLIST), CATCHNET_VERTCOUNT,
                            CATCHNET_IMPACTSIZE, CATCHNET_IMPACTSTRENGTH, CATCHNET_SNAPPINESS,
                            CATCHNET_RESISTANCE, DynaPolyVertSpeeds);
}

void breakabletile(void) {
    if (cur_obj_is_mario_ground_pounding_platform()) {
        mark_obj_for_deletion(o);
        spawn_mist_particles_variable(20, 0, 46.f);
        spawn_triangle_break_particles(15, MODEL_DIRT_ANIMATION, 3.0f, 4);
    }
    Solidify();
}

extern s16 newcam_yaw;
extern f32 newcam_pos[3];
void booGuyPainting(void) {
    switch (o->oAction) {
        case 0:
            o->oOpacity = 255;
            o->oAction++;
            break;
        case 1:
            if (sqr(o->oDistanceToMario) < sqr(1250.f)) {
                if (abs_angle_diff(newcam_yaw + 0x8000,
                                   atan2s(o->oPosZ - newcam_pos[2],
                                          o->oPosX - newcam_pos[0]))
                    < 0x2000) {
                    o->oAction = 2;
                }
            }
            break;
        case 2:
            o->oOpacity -= 5;
            if (o->oOpacity == 0) {
                o->oAction++;
            }
            break;
        case 3:
            o->oHiddenBlueCoinSwitch = spawn_object(o, 0x3B, bhvBooGuy);
            o->oHiddenBlueCoinSwitch->oPosY -= 50.f;
            o->oHiddenBlueCoinSwitch->oAction = 1;
            o->oHiddenBlueCoinSwitch->oIntangibleTimer = 0;
            ObjbParam2(o->oHiddenBlueCoinSwitch) = 4;
            o->oAction++;
            break;
        case 4:
            if (o->oHiddenBlueCoinSwitch->oAction == 0) {
                o->oAction = 0;
                mark_obj_for_deletion(o->oHiddenBlueCoinSwitch);
            }
            if (o->oHiddenBlueCoinSwitch->oAction == 4) {
                mark_obj_for_deletion(o);
            }
            break;
    }
}


// start peeking
// peek
// stop peeking (anim stops here)
// throw mario up
void boobarrel(void) {
    switch (o->oAction) {
        case 0:
            cur_obj_init_animation(0); // startpeek
            if (cur_obj_check_if_at_animation_end()) {
                o->oAction++;
            }
            break;
        case 1:
            cur_obj_init_animation(1); // peeking
            if (sqr(o->oDistanceToMario) < sqr(1000.f)) {
                o->oAction++;
            }
            break;
        case 2:
            cur_obj_init_animation(2); // stoppeek
            if (sqr(o->oDistanceToMario) > sqr(1000.f)) {
                o->oAction = 0;
            }
            if (cur_obj_is_mario_on_platform()) {
                o->oAction++;
                m->action = ACT_THROWN_BACKWARD;
                play_sound(SOUND_MARIO_WAAAOOOW, gDefaultSoundArgs);
                PlaySFX(SOUND_OBJ_HEAVEHO_TOSSED);
                m->faceAngle[1] = o->oMoveAngleYaw;
                m->vel[1] = 65.f + (o->oBehParams & 0xff);
                m->forwardVel = -25.f;
            }
            break;
        case 3:
            cur_obj_init_animation(3); // shootup
            if (cur_obj_check_if_at_animation_end()) {
                o->oAction = 0;
            }
            break;
    }
    Solidify();
}
void ThePlank(void) {
            f32 Multiplier;
    s16 *coll = o->collisionData;
    s32 i, k;
    Vtx *VisualVTX = SegmentedToVirtual(ThePlank_AAAPlane_002_mesh_layer_1_vtx_0);
#define PLANKVERTS 24
    if (!bParam3) {
        for (i = 0; i < PLANKVERTS; i++) {
            for (k = 0; k < PLANKVERTS; k++) {
                if (coll[k * 3 + 3] == VisualVTX[i].v.ob[0]) {
                    if (coll[k * 3 + 4] == VisualVTX[i].v.ob[1]) {
                        if (coll[k * 3 + 5] == VisualVTX[i].v.ob[2]) {
                            VisualVTX[i].v.flag = k + (VisualVTX[i].v.ob[1] << 8);
                        }
                    }
                }
            }
        }
        bParam3 = 1;
    }
    if (cur_obj_is_mario_on_platform()) {
#define BASEDEFORM 0.00000566666f
        if (gMarioState->pos[2] < o->oPosZ) {
            o->oAction = 1;
            o->oBobombBuddyPosZCopy = 0.f;
            Multiplier = BASEDEFORM * (gMarioState->pos[2] - o->oPosZ) / -600.f;
            o->oBobombBuddyPosXCopy += Multiplier * (gMarioState->vel[1] - 20.f) / -20.f;
            if (cur_obj_is_mario_ground_pounding_platform()) {
                o->oBobombBuddyPosXCopy += Multiplier;
            }
        }
    } else {
        // retroactively detect if mario jumped... (yeah maybe this is not 100% consistent?)
        if (o->oAction && gMarioState->vel[1] > 0.f
            && gMarioState->action & ACT_FLAG_ALLOW_VERTICAL_WIND_ACTION
            && o->oBobombBuddyPosXCopy < 0.f) {
            o->oBobombBuddyPosZCopy =
                gMarioState->vel[1]
                + MIN(o->oBobombBuddyPosXCopy * -1000000.f * (gMarioState->pos[2] - o->oPosZ) / -600.f,
                      80.f);
        }
        if (o->oTimer < 10 && o->oBobombBuddyPosZCopy > 0.f) {
            gMarioState->vel[1] = o->oBobombBuddyPosZCopy;
        }
        o->oAction = 0;
    }

    o->oBobombBuddyPosXCopy *= 0.92f;
    o->oBobombBuddyPosYCopy += o->oBobombBuddyPosXCopy;
    o->oBobombBuddyPosXCopy -= o->oBobombBuddyPosYCopy * 0.05f;
    for (i = 0; i < PLANKVERTS; i++) {
        if (VisualVTX[i].v.ob[2] < 0) {
            VisualVTX[i].v.ob[1] = (VisualVTX[i].v.flag >> 8)
                                   - (o->oBobombBuddyPosYCopy * sqr(((f32) VisualVTX[i].v.ob[2])));

            coll[(VisualVTX[i].v.flag & 0xff) * 3 + 4] = VisualVTX[i].v.ob[1];
        }
    }
    Solidify();
}

Gfx *geo_render_captain_background(s32 callContext, UNUSED struct GraphNode *node,
                                   UNUSED Mat4 b) {
    struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) b;
    s32 i;
    f32 pos[3];
    if (callContext == GEO_CONTEXT_RENDER && CurrentRoom == 9) {
        Mtx *mtx = alloc_display_list(sizeof(*mtx));
        Gfx *dlist = alloc_display_list(4 * sizeof(Gfx));
        Gfx *Start = dlist;
        for (i = 0; i < 3; i++) {
            pos[i] = newcam_pos[i] * 0.99f;
        }
        guTranslate(mtx, pos[0], pos[1], pos[2]);
        gSPMatrix(dlist++, (mtx),
                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPDisplayList(dlist++, CaptainBG_CaptainBG_mesh);
        gSPEndDisplayList(dlist++);
        asGenerated->fnNode.node.flags = (asGenerated->fnNode.node.flags & 0xFF) | (0 << 8);
        return Start;
    }
    return 0;
}

Gfx DeadEnvColor[] = {
    sDPRGBColor(G_SETENVCOLOR, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx *Geo_KillEnvColor(s32 callContext, struct GraphNode *b, UNUSED Mat4 *mtx) {
    struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) b;
    Gfx *gfx = NULL;
    if (callContext == GEO_CONTEXT_RENDER) {
        gfx = &DeadEnvColor[0];
        asGenerated->fnNode.node.flags = (asGenerated->fnNode.node.flags & 0xFF) | (LAYER_OPAQUE << 8);
    }
    return gfx;
}
// play keyboard
// talk to mario
// space idly
// sping attack
// flame attack
// get hit->piano dash
// come out of piano
//
void shyguymovement() {
    u16 moveDir, targetAngle;
    targetAngle = atan2s(o->oBobombBuddyPosZCopy - o->oPosZ, o->oBobombBuddyPosXCopy - o->oPosX);
    o->oVelX += sins(targetAngle) * 2.f;
    o->oVelZ += coss(targetAngle) * 2.f;

    o->oForwardVel = sqrtf(o->oVelX * o->oVelX + o->oVelZ * o->oVelZ);
    moveDir = atan2s(o->oVelZ, o->oVelX);
    o->oFaceAngleYaw = approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 0x800);
    /*o->oForwardVel = approach_f32(o->oForwardVel,
                                  30.f * (coss(moveDir - o->oMoveAngleYaw) + 1.0f), 2.f, 3.f);*/
    o->oForwardVel *= 0.995f;
    o->oVelX = sins(moveDir) * o->oForwardVel;
    o->oVelZ = coss(moveDir) * o->oForwardVel;
    o->oPosY = approach_f32_symmetric(o->oPosY, o->oBobombBuddyPosYCopy, 11.f);
    o->oVelY = approach_f32_symmetric(o->oVelY, 0, 1.5f);
    cur_obj_move_using_vel();
}

void muteCptInstruments() {
    s32 i;
    for (i = 0; i < 16; i++) {
        if (i != 3) {
            if (gSequencePlayers[SEQ_PLAYER_ENV].channels[i]) {
                gSequencePlayers[SEQ_PLAYER_ENV].channels[i]->volume = 0;
            }
        }
    }
}

u16 cloakTimer = 0;
extern Vtx captainVerts[78] __attribute__((section(".data")));
void animateCloak() {
    s32 i;
    Vtx *mod = SegmentedToVirtual(shyguycaptain_BODY_mesh_layer_5_vtx_0);
    Vtx *read = SegmentedToVirtual(captainVerts);
    u16 dir;
    cloakTimer += 0x800;
    for (i = 0; i < sizeof(shyguycaptain_BODY_mesh_layer_5_vtx_0) / 0x10; i++) {
        if (!mod[i].v.cn[3]) {
            dir = atan2s(read[i].v.ob[2], read[i].v.ob[0]);
#define MINVERT 75.f
            mod[i].v.ob[0] = read[i].v.ob[0]
                             + sins(dir) * (MINVERT - read[i].v.ob[1]) * 0.1f
                                   * sins(cloakTimer + read[i].v.ob[0] * 256 + read[i].v.ob[2] * 128);
            mod[i].v.ob[2] = read[i].v.ob[2]
                             + coss(dir) * (MINVERT - read[i].v.ob[1]) * 0.1f
                                   * sins(cloakTimer + read[i].v.ob[0] * 256 + read[i].v.ob[2] * 128);
        }
    }
}
#define BGM_FADE_TIME 200
extern struct CutsceneJump *currentScene;
void shyguycpt(void) {
    f32 x, y, z;
    if (sqr(o->oDistanceToMario) < sqr(4000.f)) {
        animateCloak();
    }
    if (!o->oHiddenBlueCoinSwitch) {
        // not allowed to edit volume frame 0 - audio playback has not begun yet. this would cause a
        // race condition!
        if (gAreaUpdateCounter == 0)
            return;
        o->oHiddenBlueCoinSwitch =
            spawn_object_relative(0, 0, 0, 295.f, o, MODEL_MAD_PIANO, bhvMadPiano);
        o->oHiddenBlueCoinSwitch->oMoveAngleYaw += 0x8000;
        o->oPosY += 65.f;
        // quiet the level sequence immidiately when near the boss
        if ((sqr(o->oDistanceToMario) < sqr(3500.f)) && (gMarioState->pos[1] > o->oPosY - 1000.f)) {
            play_secondary_music(SEQ_EVENT_SHYGUYBOSS, 0x80, 127, 0);
            muteCptInstruments();
            o->oSubAction = 1;
        } else {
        }
    }
    cur_obj_update_floor_height();
    switch (o->oAction) {
        case 0:
            // sit in front of piano, play it
            o->oAnimState = 80;
            if (!currentScene) {
                switch (o->oSubAction) {
                    case 0:
                        if ((sqr(o->oDistanceToMario) < sqr(3500.f))
                            && (gMarioState->pos[1] > o->oPosY - 1000.f)) {
                            play_secondary_music(SEQ_EVENT_SHYGUYBOSS, 0x80, 127, BGM_FADE_TIME);
                            muteCptInstruments();
                            o->oSubAction = 1;
                            // keep channel 3, delete channel 0, 2, 4, 5, 7, 9
                        }
                        break;
                    case 1:
                        muteCptInstruments();
                        if (sqr(o->oDistanceToMario) > sqr(4000.f)) {
                            func_80321080(BGM_FADE_TIME);
                            o->oSubAction = 0;
                        }
                        break;
                }
                if ((sqr(o->oDistanceToMario) < sqr(1000.f))) {
                    o->oAction = 1;
                    o->oIntangibleTimer = -1;
                    func_80321080(10);
                }
            }
            cur_obj_init_animation(0);
            break;
        case 1:
            if (o->oSubAction) {
                if (!cur_obj_check_if_at_animation_end())
                    break;
                o->oAction = 2;
                o->oFlags &= ~OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
                o->oOpacity = 1;
                o->oHealth = 0;
            sequence_player_unlower(SEQ_PLAYER_LEVEL, 60);
                play_music(SEQ_EVENT_SHYGUYBOSS, 1, 0);
                break;
            }
            // MuteGhostshipSongExceptRain();
            //  turn around, talk to mario
            if (o->oTimer > 20) {
                cur_obj_init_animation(1);
            } else {
                o->header.gfx.unk38.animFrame = 0;
            }
            if (o->oTimer > 40) {
                o->oFlags |= OBJ_FLAG_SET_FACE_YAW_TO_MOVE_YAW;
                o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw,
                                                          obj_angle_to_object(o, gMarioObject), 0x240);
            } else {
                o->oMoveAngleYaw = o->oFaceAngleYaw;
            }
            if (o->oTimer < 70) {
              //  DialogState = 0; TODO: JUST REMOVED THIS WITH NO REPLACEMENT
            }
            if (o->header.gfx.unk38.animFrame > 67) {
                o->header.gfx.unk38.animFrame -= 16;
            }
            if (talkToMarioNoRotation2(111, 4)) {
                o->oSubAction = 1;
            }
            break;
        case 2:
            o->oIntangibleTimer = 0;
            // fight idle, space in front of mario
            cur_obj_init_animation(2);
            o->oBobombBuddyPosXCopy = sins(o->oAngleToMario + 0x8000) * 1200.f + gMarioState->pos[0];
            o->oBobombBuddyPosYCopy = o->oFloorHeight + 100.f;
            o->oBobombBuddyPosZCopy = coss(o->oAngleToMario + 0x8000) * 1200.f + gMarioState->pos[2];
            if (o->oBobombBuddyPosYCopy < o->oHomeY - 100.f) {
                o->oBobombBuddyPosYCopy = o->oHomeY + 200.f;
            }
            if (random_u16() > (0x10000 - (o->oTimer * 4 + o->oHealth * 0x20))) {
                if (o->oOpacity & 1) {
                    o->oAction = 4;
                    // SOUNDFI
                } else {
                    o->oAction = 5;
                }
            }
            o->oAnimState = approach_s16_symmetric(o->oAnimState, 110, 10);
            shyguymovement();
            break;
        case 4:
            // swing sword, start rotating at the end of the animation
            o->oAnimState = approach_s16_symmetric(o->oAnimState, 192, 10);
            switch (o->oSubAction) {
                case 0:
                    cur_obj_init_animation(3);
                    if (o->header.gfx.unk38.animFrame > 24) {
                        o->oMoveAngleYaw = o->oAngleToMario;
#define SHYGUYSPINSPEED 65.f
                        o->oVelX = SHYGUYSPINSPEED * sins(o->oMoveAngleYaw);
                        o->oVelZ = SHYGUYSPINSPEED * coss(o->oMoveAngleYaw);
                        o->oTimer = 0;
                        o->oSubAction++;
                        o->oObjPointer2 = spawn_object(o, 0, bhvHitbox);
                        o->oObjPointer2->hitboxHeight = 20.f;
                        o->oObjPointer2->hitboxRadius = 250.f;
                        o->oObjPointer2->oPosY += 60.f;
                        o->oObjPointer2->oDamageOrCoinValue = 2;
                        PlaySFX(SOUND_OBJ_MRI_SHOOT);
                    } else {
                        // shyguymovement();
                        o->oPosX = approach_f32_asymptotic(o->oPosX, o->oBobombBuddyPosXCopy, 0.1f);
                        o->oPosY = approach_f32_asymptotic(o->oPosY, o->oBobombBuddyPosYCopy, 0.1f);
                        o->oPosZ = approach_f32_asymptotic(o->oPosZ, o->oBobombBuddyPosZCopy, 0.1f);
                        if (o->oTimer == 10) {
                            PlaySFX(SOUND_OBJ_UNKNOWN2);
                        }
                    }
                    break;
                case 1:
                    if (!(o->oTimer % 12)) {
                        PlaySFX(SOUND_ACTION_SPIN);
                    }
                    obj_copy_pos_and_angle(o->oObjPointer2, o);
                    o->oObjPointer2->hitboxHeight = 20.f;
                    o->oObjPointer2->hitboxRadius = 250.f;
                    o->oObjPointer2->oPosY += 60.f;
                    o->oObjPointer2->oDamageOrCoinValue = 2;
#define TIMEFORATTACK 70
                    o->oAngleVelYaw = 0x1200;
                    if (o->oTimer < TIMEFORATTACK / 2) {
                        o->oPosY = approach_f32_asymptotic(o->oPosY, gMarioState->pos[1], 0.05f);
                    } else {
                        o->oVelY += 0.5f;
                    }
                    if (o->oTimer > TIMEFORATTACK - 10) {
                        o->oVelX *= 0.9f;
                        o->oVelY *= 0.9f;
                        o->oVelZ *= 0.9f;
                    }
                    if (o->oTimer > TIMEFORATTACK) {
                        o->oSubAction++;
                        mark_obj_for_deletion(o->oObjPointer2);
                        o->oObjPointer2 = 0;
                    }
                    o->header.gfx.unk38.animFrame = 27;
                    cur_obj_move_using_vel();
                    break;
                case 2:
                    o->oAngleVelYaw = approach_s16_symmetric(o->oAngleVelYaw, 0, 0x120);
                    if (!o->oAngleVelYaw) {
                        o->oSubAction++;
                    }
                    cur_obj_move_using_vel();
                    break;
                case 3:
                    if (cur_obj_check_if_at_animation_end()) {
                        cur_obj_move_using_vel();
                        cur_obj_init_animation(2);
                        o->oAction = 2;
                        o->oOpacity = 0;
                    }
                    break;
            }
            break;
        case 5:
            // swing sword a few times, spawn flame at the tip of his sword
            o->oAnimState = approach_s16_symmetric(o->oAnimState, 192, 10);
            o->oMoveAngleYaw = o->oAngleToMario;
            o->oFaceAngleYaw = o->oMoveAngleYaw;
            switch (o->oSubAction) {
                case 0:
                    o->oBobombBuddyPosXCopy =
                        sins(o->oAngleToMario + 0x8000) * 750.f + gMarioState->pos[0];
                    o->oBobombBuddyPosYCopy = o->oFloorHeight + 200.f;
                    o->oBobombBuddyPosZCopy =
                        coss(o->oAngleToMario + 0x8000) * 750.f + gMarioState->pos[2];
                    if (o->oBobombBuddyPosYCopy < o->oHomeY - 100.f) {
                        o->oBobombBuddyPosYCopy = o->oHomeY + 200.f;
                    }
                    o->oPosX = approach_f32_asymptotic(o->oPosX, o->oBobombBuddyPosXCopy, 0.15f);
                    o->oPosY = approach_f32_asymptotic(o->oPosY, o->oBobombBuddyPosYCopy, 0.15f);
                    o->oPosZ = approach_f32_asymptotic(o->oPosZ, o->oBobombBuddyPosZCopy, 0.15f);
                    x = o->oPosX - o->oBobombBuddyPosXCopy;
                    y = o->oPosY - o->oBobombBuddyPosYCopy;
                    z = o->oPosZ - o->oBobombBuddyPosZCopy;
                    if (sqrtf(x * x + y * y + z * z) < 250.f) {
                        o->oSubAction++;
                    }
                    break;
                case 1:
                    cur_obj_init_animation(4);
                    if (o->header.gfx.unk38.animFrame > 15) {
                        o->oSubAction++;
                        o->oBobombBuddyCannonStatus = 0;
                    }
                    break;
                case 2:
                    if ((o->header.gfx.unk38.animFrame == 45)) {
#define YOFF 55.f
#define ZOFF 200.f
                        struct Object *flame = spawn_object_relative(
                            0, 0, YOFF, ZOFF, o, MODEL_BLUE_FLAME, bhvBouncingFireballFlame);
                        obj_scale(flame, 5.f);
                        PlaySFX(SOUND_OBJ_FLAME_BLOWN);
                    }
                    if ((o->header.gfx.unk38.animFrame == 17)) {
#define YOFF 55.f
#define ZOFF 200.f
                        struct Object *flame = spawn_object_relative(
                            1, 0, YOFF, ZOFF, o, MODEL_BLUE_FLAME, bhvSmallPiranhaFlame);
                        flame->oForwardVel = 50.f;
                        flame->oMoveAnglePitch =
                            0x4000
                            - lateral_dist_between_objects(gMarioState->marioObj, o)
                                  * 6.f; // calc from lateral dist to mario
                        obj_scale(flame, 5.f);
                        PlaySFX(SOUND_OBJ_FLAME_BLOWN);
                    }
                    if (cur_obj_check_if_at_animation_end()) {
                        if ((4 - o->oHealth) < o->oBobombBuddyCannonStatus) {
                            o->oOpacity++;
                            cur_obj_init_animation(2);
                            o->oAction = 2;
                        } else {
                            o->header.gfx.unk38.animFrame = 0;
                            o->oBobombBuddyCannonStatus++;
                        }
                    }
                    break;
            }
            break;
        case 6:
            // dash into piano
            o->oAnimState = approach_s16_symmetric(o->oAnimState, 80, 10);
            o->oIntangibleTimer = -1;
            switch (o->oSubAction) {
                case 0:
                    o->oVelY = 0;
                    cur_obj_init_animation(5);
                    if (!o->oTimer) {
                        o->oForwardVel = -50.f;
                        o->oAngleVelPitch = 0x1370;
                        o->oAngleVelYaw = -0x10C0;
                    }
                    o->oFaceAngleYaw += o->oAngleVelYaw;
                    o->oFaceAnglePitch += o->oAngleVelPitch;
                    o->oAngleVelPitch = approach_s16_symmetric(o->oAngleVelPitch, 0, 0x137 / 2);
                    o->oAngleVelYaw = approach_s16_symmetric(o->oAngleVelYaw, 0, 0x10C / 2);
                    o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 0.f, 1.f);
                    if (o->oTimer > 32) {
                        o->oSubAction++;
                        o->oAngleVelYaw = 0;
                        o->oAngleVelPitch = 0;
                        o->oHealth++;
                        if (o->oHealth > 2) {
                            o->oAction = 8;
                        }
                    }
                    o->oPosY = approach_f32_symmetric(o->oPosY, gMarioState->pos[1] + 100.f, 3.f);
                    break;
                case 1:
                    o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 0.f, 1.f);
                    o->oFaceAngleYaw =
                        approach_s16_symmetric(o->oFaceAngleYaw, o->oAngleToMario, 0x800);
                    o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, 0, 0x800);
                    if (o->oForwardVel == 0.f) {
                        o->oSubAction++;
                        o->oFaceAngleYaw = o->oAngleToMario;
                        o->oFaceAnglePitch = o->oFaceAnglePitch;
                    }
                    break;
                case 2:
                    o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 0.f, 1.f);
                    o->oMoveAngleYaw = approach_s16_symmetric(
                        o->oMoveAngleYaw, obj_angle_to_object(o, o->oHiddenBlueCoinSwitch), 0x800);
                    if (o->oFaceAngleYaw == o->oMoveAngleYaw) {
                        o->oSubAction++;
                        cur_obj_init_animation(6);
                    }
                    o->oFaceAngleYaw = o->oMoveAngleYaw;
                    break;
                case 3:
                    o->oMoveAngleYaw = obj_angle_to_object(o, o->oHiddenBlueCoinSwitch);
                    if (o->header.gfx.unk38.animFrame > 19)
                        o->oForwardVel = approach_f32_symmetric(
                            o->oForwardVel,
                            lateral_dist_between_objects(o, o->oHiddenBlueCoinSwitch) / 8.f, 5.f);
                    o->oPosY = approach_f32_asymptotic(o->oPosY,
                                                       o->oHiddenBlueCoinSwitch->oPosY + 350.f, 0.1f);
                    if (lateral_dist_between_objects(o, o->oHiddenBlueCoinSwitch) < 40.f) {
                        o->oSubAction++;
                        o->oForwardVel = 0;
                        o->oTimer = 0;
                    }
                    break;
                case 4:
                    o->oHiddenBlueCoinSwitch->oAction = 1;
                    o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, 0x4000, 0xC00);
                    o->oVelY -= 4.f;
                    cur_obj_scale(1.f - 0.08 * o->oTimer);
                    if (o->oTimer > 11) {
                        o->oAction = 7;
                        cur_obj_set_model(0);
                        o->oHiddenBlueCoinSwitch->oAction = 2;
                    }
                    break;
            }
        cur_obj_compute_vel_xz();
    cur_obj_move_using_vel();
            break;
        case 7:
            o->oIntangibleTimer = -1;
            // angry piano attack mario, chases for 10 + 5*damage seconds
            switch (o->oSubAction) {
                case 0:
                    ObjbParam2(o->oHiddenBlueCoinSwitch) = o->oHealth;
                    if (o->oTimer > o->oHealth * 150 + 300) {
                        cur_obj_set_model(0x4B);
                        o->oHiddenBlueCoinSwitch->oAction = 0;
                        o->oVelY = 14.f;
                        o->oFaceAnglePitch = 0xC000;
                        o->oTimer = 0;
                        cur_obj_init_animation(2);
                        o->oSubAction++;
                        obj_copy_pos_and_angle(o, o->oHiddenBlueCoinSwitch);
                        o->oPosY += 50.f;
                    }
                    break;
                case 1:
                    o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, 0, 0xC00);
                    o->oVelY -= 2.f;
                    o->oPosY += o->oVelY;
                    cur_obj_scale(0.08 * o->oTimer);
                    if (o->oTimer > 11) {
                        o->oAction = 2;
                        cur_obj_scale(1.f);
                    }
                    o->oInteractStatus = 0;
                    break;
            }
            break;
        case 8:
            // die and give mario star
            if (!o->oTimer) {
                cur_obj_set_model(0);
                spawn_mist_particles_variable(20, 0, 46.f);
                spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, 4);
            } else {
                stop_background_music(SEQ_EVENT_SHYGUYBOSS);
                cur_obj_spawn_star_at_y_offset(o->oHomeX, o->oHomeY + 200.f, o->oHomeZ, 0.f);
                mark_obj_for_deletion(o);
            }
            break;
    }
    if (o->oAction < 6) {
        if (o->oInteractStatus & INT_STATUS_INTERACTED) {
            if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
                PlaySFX(SOUND_OBJ_KOOPA_FLYGUY_DEATH);
                o->oAction = 6;
                o->oMoveAngleYaw = o->oAngleToMario;
                if (o->oObjPointer2) {
                    mark_obj_for_deletion(o->oObjPointer2);
                    o->oObjPointer2 = 0;
                    o->oOpacity++;
                }
            }
        }
        o->oInteractStatus = 0;
    }
    if ((gMarioState->pos[1] < 2300.f) && !currentScene && o->oAction > 0) {
        o->oAction = 0;
        o->oPosX = o->oHomeX;
        o->oPosY = o->oHomeY;
        o->oPosZ = o->oHomeZ;
        o->oAngleVelYaw = 0;
        o->oForwardVel = 0.f;
        o->oVelY = 0;
        o->oFaceAngleYaw = 0x8000;
        o->oMoveAngleYaw = 0x8000;
        mark_obj_for_deletion(o->oHiddenBlueCoinSwitch);
        o->oHiddenBlueCoinSwitch = 0;
        stop_background_music(SEQ_EVENT_SHYGUYBOSS);
    }
    o->oFaceAngleYaw += o->oAngleVelYaw;
}
Gfx *Geo_CaptainColor(s32 callContext, struct GraphNode *b, UNUSED Mat4 *mtx) {
    Gfx *gfx = alloc_display_list(sizeof(Gfx) * 2);
    Gfx *dlStart = gfx;
    if (callContext == GEO_CONTEXT_RENDER) {
        struct Object *obj = (struct Object *) gCurGraphNodeObject;
        struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) b;
        gDPSetPrimColor(dlStart++, 0, 0, 0x1d, 0x47, 0x40, obj->oAnimState);
        gSPEndDisplayList(dlStart++);
        asGenerated->fnNode.node.flags = (asGenerated->fnNode.node.flags & 0xFF) | (LAYER_TRANSPARENT << 8);
    }
    return gfx;
}
// spawn dust and sound too
#define INCREMENT 0.0035f
// TODO: implement camRoll via lakitustate
extern f32 camRoll;
extern f32 camRollSpeed;
#define PERCENTAGE 0.001f

#define DUSTSPAWN 40.f
#define /*0x108*/ oMacroUnk108 OBJECT_FIELD_F32(0x20)
extern struct ParticleInfos MistParticle;
extern struct ParticleInfos SmokeParticle;
void movecratecode(void) {
    /*for (; o->oOpacity < 0x400; o->oOpacity++) {
        o->oMacroUnk10C = DUSTSPAWN / 2.f;
        camRoll += camRollSpeed;
        camRollSpeed -= camRoll * PERCENTAGE;
        o->oVelZ += camRoll * INCREMENT * 127.f / bParam2;
        o->oVelZ *= 0.99f;
        o->oPosZ += o->oVelZ;
        if (o->oPosZ > (o->oHomeZ + ((o->oBehParams >> 24) * 100.f))) {
            o->oPosZ = (o->oHomeZ + ((o->oBehParams >> 24) * 100.f));
            o->oVelZ = 0.f;
        }
        if (o->oPosZ < (o->oHomeZ - ((o->oBehParams >> 24) * 100.f))) {
            o->oPosZ = (o->oHomeZ - ((o->oBehParams >> 24) * 100.f));
            o->oVelZ = 0.f;
        }
    }
    o->oVelZ += camRoll * INCREMENT * 127.f / bParam2;*/
    o->oVelZ *= 0.99f;
    o->oPosZ += o->oVelZ;
    if (o->oPosZ > (o->oHomeZ + ((o->oBehParams >> 24) * 100.f))) {
        o->oPosZ = (o->oHomeZ + ((o->oBehParams >> 24) * 100.f));
        o->oVelZ = 0.f;
    }
    if (o->oPosZ < (o->oHomeZ - ((o->oBehParams >> 24) * 100.f))) {
        o->oPosZ = (o->oHomeZ - ((o->oBehParams >> 24) * 100.f));
        o->oVelZ = 0.f;
    }
    if (absf(o->oVelZ) > 10.f) {
        PlaySFX(SOUND_AIR_ROUGH_SLIDE);
    }
    o->oMacroUnk108 += o->oVelZ;
    o->oMacroUnk10C += o->oVelZ;
    if (o->oMacroUnk108 < -DUSTSPAWN) {
        o->oMacroUnk108 += DUSTSPAWN;
        spawn_object_relative(0, 200.f, 200.f, 0, o, 0,bhvMistParticleSpawner);
    }
    if (o->oMacroUnk108 > DUSTSPAWN) {
        o->oMacroUnk108 -= DUSTSPAWN;
        spawn_object_relative(0, 200.f, -200.f, 0, o, 0,bhvMistParticleSpawner);
    }

    if (o->oMacroUnk10C < -DUSTSPAWN) {
        o->oMacroUnk10C += DUSTSPAWN;
        spawn_object_relative(0, -200.f, 200.f, 0, o, 0,bhvMistParticleSpawner);
    }
    if (o->oMacroUnk10C > DUSTSPAWN) {
        o->oMacroUnk10C -= DUSTSPAWN;
        spawn_object_relative(0, -200.f, -200.f, 0, o, 0,bhvMistParticleSpawner);
    }

    Solidify();
}


void ghostplatform(void) {
    switch (o->oAction) {
        case 0:
            if (o->oOpacity) {
                o->oOpacity--;
                if (o->oOpacity & 2) {
                    cur_obj_hide();
                } else {
                    cur_obj_unhide();
                }
            } else {
                o->oAnimState = 0;
            }
            o->oAction = cur_obj_is_mario_on_platform();
            o->oVelY = 0.f;
            Solidify();
            break;
        case 1:
            if (!o->oTimer) {
                PlaySFX(SOUND_GENERAL_BIG_CLOCK);
            }
            o->oAnimState = 1;
            /*if (!cur_obj_is_mario_on_platform()) {
                o->oAction++;
                cur_obj_update_floor_height();
            }*/
            o->oGraphYOffset = (o->oTimer & 1) * -8.f;
            if (o->oTimer > 64) {
                o->oAction++;
                cur_obj_update_floor_height();
                o->oGraphYOffset = 0;
            }

            Solidify();
            break;
        case 2:
            o->oVelY -= 2.f;
            o->oPosY += o->oVelY;
            if (o->oPosY < o->oFloorHeight) {
                o->oAction++;
                cur_obj_set_model(0);
                spawn_mist_particles_variable(20, 0, 46.f);
                spawn_triangle_break_particles(30, MODEL_DIRT_ANIMATION, 3.0f, 4);
                PlaySFX(SOUND_GENERAL_BREAK_BOX);
            }
            Solidify();
            break;
        case 3:
            if (o->oTimer > 240) {
                cur_obj_set_model(0x36);
                o->oPosY = o->oHomeY;
                o->oAction = 0;
                o->oOpacity = 40;
            }
            break;
    }
}

Gfx *geo_GhostPlatform(s32 callContext, struct GraphNode *b, UNUSED Mat4 *mtx) {
    Gfx *gfx = alloc_display_list(sizeof(Gfx) * 2);
    Gfx *dlStart = gfx;
    if (callContext == GEO_CONTEXT_RENDER) {
        struct Object *obj = (struct Object *) gCurGraphNodeObject;
        struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) b;
        if (obj->oAnimState) {
            gDPSetPrimColor(dlStart++, 0, 0, 0, 0, 0, 0);
        } else {
            gDPSetPrimColor(dlStart++, 0, 0, 0, 0xff, 0x90, 0);
        }
        gSPEndDisplayList(dlStart++);
        asGenerated->fnNode.node.flags = (asGenerated->fnNode.node.flags & 0xFF) | (LAYER_OPAQUE << 8);
    }
    return gfx;
}

s32 getHitBox() {
    f32 x, y, z;
    x = o->oPosX - gMarioState->pos[0];
    y = (o->oPosY - 100.f) - gMarioState->pos[1];
    z = o->oPosZ - gMarioState->pos[2];
    return (sqrtf(x * x + y * y + z * z) < 150.f);
}
// hang on until you press A again
// swing back and forth in idle
// hold stick to rotate mario
const u8 LanternRGB[3] = { 0x39, 0xff, 0x14 };
void ghostLantern(void) {
                 s32 UsedAngleVelPitch;
                 s16 UsedFaceAnglePitch;
    f32 speedScale = 1.f;
    if (!o->oOpacity) {
        o->oOpacity = random_u16();
    }
    if (!(o->oBehParams & 0x01000000)) {
        o->oOpacity += 0x100;
        o->oPosY = o->oHomeY + sins(o->oOpacity) * 50.f;
    }
    o->oAngleVelPitch -= o->oFaceAnglePitch / 64;
    o->oAngleVelPitch *= .99f;
    o->oFaceAnglePitch += o->oAngleVelPitch;
    switch (o->oAction) {
        case 0:
            if (o->oOpacity & 0x4000) {
                o->oAngleVelPitch += 0x0020;
            }
            if (o->oTimer > 20) {
                if (getHitBox()) {
                    o->oAction++;
                    gMarioState->action = ACT_HANG_LANTERN;
                    gMarioState->usedObj = o;
                    o->oAngleVelPitch = -gMarioState->forwardVel / 0.01581917687f / 2.f;
                }
            }
            break;
        case 1:
#define OFFSET -155.f
            speedScale += 4.f - absf((o->oAngleVelPitch - (o->oFaceAnglePitch / 64)) / 0x1000);
            gMarioState->faceAngle[1] =
                approach_s16_symmetric(gMarioState->faceAngle[1], o->oMoveAngleYaw, 0xC00);
            gMarioState->action = ACT_HANG_LANTERN;
            gMarioState->usedObj = o;
            gMarioState->pos[0] = o->oPosX + sins(o->oFaceAnglePitch) * sins(o->oMoveAngleYaw) * OFFSET;
            gMarioState->pos[1] = o->oPosY + coss(o->oFaceAnglePitch) * OFFSET;
            gMarioState->pos[2] = o->oPosZ + sins(o->oFaceAnglePitch) * coss(o->oMoveAngleYaw) * OFFSET;
            o->oAngleVelPitch -= coss(gMarioState->intendedYaw - o->oFaceAngleYaw)
                                 * gMarioState->intendedMag * speedScale;
            o->oAngleVelPitch *= .95f;
            if (gMarioState->controller->buttonPressed & A_BUTTON) {
                o->oAction = 0;
                gMarioState->action = ACT_TRIPLE_JUMP;
#define UNITS_PER_ANGLE 0.01581917687f
                // fumbled the numbers a little because
                // some players just dont understand how swings work!
                // they would just flop to the ground...
                 UsedAngleVelPitch =
                    o->oAngleVelPitch + (o->oAngleVelPitch > 0 ? 0x400 : -0x400);
                 UsedFaceAnglePitch = ((f32) o->oFaceAnglePitch) * 0.75f;
                gMarioState->vel[1] =
                    UsedAngleVelPitch * coss(UsedFaceAnglePitch - 0x4000) * UNITS_PER_ANGLE * 1.25f;
                gMarioState->forwardVel =
                    UsedAngleVelPitch * sins(UsedFaceAnglePitch - 0x4000) * UNITS_PER_ANGLE * 1.75f;
                if (gMarioState->vel[1] < 44.f) {
                    gMarioState->vel[1] = 44.f;
                }
            }
            switch (o->oAnimState) {
                case 0:
                    if (absi(o->oAngleVelPitch) > 0x400) {
                        o->oAnimState++;
                        PlaySFX(SOUND_GENERAL_SWISH_AIR);
                    }
                    break;
                case 1:
                    if (absi(o->oAngleVelPitch) < 0x200) {
                        o->oAnimState = 0;
                    }
                    break;
            }
            break;
    }
}

s32 InVision() {
    f32 pitchToMario;
    f32 x, y, z;
    x = gMarioState->pos[0] - o->oPosX;
    z = gMarioState->pos[2] - o->oPosZ;
    y = gMarioState->pos[1] - o->oPosY;
    pitchToMario = -atan2s(sqrtf(x * x + z * z), y);
    if (sqr(o->oDistanceToMario) < sqr(1200.f)) {
        if (abs_angle_diff(o->oMoveAngleYaw, o->oAngleToMario) < 0x1800) {
            if (abs_angle_diff(o->oFaceAnglePitch, pitchToMario) < 0x1400) {
                return 1;
            }
        }
    }
    return 0;
}
s32 IsMarioFarFromHome(f32 max) {
    f32 dx = o->oHomeX - gMarioObject->oPosX;
    f32 dy = o->oHomeY - gMarioObject->oPosY;
    f32 dz = o->oHomeZ - gMarioObject->oPosZ;
    f32 marioDistToHome = sqrtf(dx * dx + dy * dy + dz * dz);

    if (marioDistToHome > max) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void CurObjSpawnYellowCoins(s32 nCoins) {
    for (; nCoins > 0; nCoins--) {
        struct Object *coin = spawn_object(o, MODEL_YELLOW_COIN, bhvMovingYellowCoin);
        coin->oForwardVel = random_float() * 20;
        coin->oVelY = random_float() * 40 + 20;
        coin->oMoveAngleYaw = random_u16();
    }
}

// make their model pulsate white to turkoise
// different idle and attackstart behavior depending on bParam2
// charge at mario once they see him
// 25% chance to do half a looping after missing mario and attack again
// afterwrards, turn into ghosts that slowly walk towards mario, just like boos. go back to idle if
// mario is far away from their home.
void booGuy(void) {
    struct WallCollisionData collisionData;
    u16 targetAngle;
    u16 targetPitch;
    o->oPosY += sins(o->oOpacity += 0x800) * 0.5f;
    if (!o->oAnimState) {
        o->oAnimState = o->oMoveAngleYaw + 1;
    }
    o->oGraphYOffset = 50.f;
    o->oIntangibleTimer = 0;
    switch (o->oAction) {
        case 0:
            switch (bParam2) {
                case 0:
                    if (!o->oHiddenBlueCoinSwitch) {
                        o->oHiddenBlueCoinSwitch =
                            spawn_object(gCurrentObject, MODEL_BUBBLE, bhvYoshiBubble);
                        o->oHiddenBlueCoinSwitch->oObjPointer1 = o;
                        ObjbParam2(o->oHiddenBlueCoinSwitch) = 2;
                    }
                    cur_obj_init_animation(1);
#define SLEEPTIME 59
                    if (o->header.gfx.unk38.animFrame > SLEEPTIME) {
                        o->header.gfx.unk38.animFrame -= SLEEPTIME;
                    }
                    if (sqr(o->oDistanceToMario) < sqr(1500.f)) {
                        if ((gMarioState->action == ACT_GROUND_POUND_LAND)) {
                            o->oAction = 1;
                            o->oHiddenBlueCoinSwitch = 0;
                        }
                        if (sqrtf(sqr(gMarioState->forwardVel) + sqr(gMarioState->vel[1]))
                            > (o->oDistanceToMario) / 15.f) {
                            o->oAction = 1;
                            o->oHiddenBlueCoinSwitch = 0;
                        }
                    }
                    break;
                case 1:
                    // keep watch (looks left and right)
                    cur_obj_init_animation(0);
                    if (InVision()) {
                        o->oAction = 1;
                    }
                    break;
                case 2:
                    // look at something
                    cur_obj_init_animation(2);
                    if (InVision()) {
                        o->oAction = 1;
                    }
                    break;
                case 3:
                    // patrol
                    cur_obj_init_animation(3);
                    switch (o->oSubAction) {
                        case 0:
                            o->oForwardVel = 10.f;
                            if (o->oTimer > (o->oBehParams & 0xFF) + 30) {
                                o->oSubAction = 1;
                                o->oTimer = 0;
                            }
                            break;
                        case 1:
                            o->oForwardVel = 0.f;
                            o->oMoveAngleYaw += 0x400;
                            if (o->oTimer > 0x1F) {
                                o->oSubAction = 0;
                                o->oTimer = 0;
                            }
                            break;
                    }
                    if (InVision()) {
                        o->oAction = 1;
                    }
                    break;
                case 4:

                    break;
            }
            break;
        case 1:
            // charge anim
            cur_obj_init_animation(4);
#define CHARGETIME 19
            if (o->header.gfx.unk38.animFrame > CHARGETIME) {
                o->header.gfx.unk38.animFrame -= CHARGETIME;
            }
            targetAngle = atan2s(gMarioState->pos[2] - o->oPosZ, gMarioState->pos[0] - o->oPosX);
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, targetAngle, 0x100);
            targetPitch =
                -atan2s(sqrtf((gMarioState->pos[2] - o->oPosZ) * (gMarioState->pos[2] - o->oPosZ)
                              + (gMarioState->pos[0] - o->oPosX) * (gMarioState->pos[0] - o->oPosX)),
                        gMarioState->pos[1] - o->oPosY);
            o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, targetPitch, 0x100);
#define FLYSPEEDMUL4 8.f
            if (o->oTimer < 10) {
                o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, targetPitch, 0x400);
                o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, targetAngle, 0x400);
            }
            o->oForwardVel =
                approach_f32_symmetric(o->oForwardVel,
                                       FLYSPEEDMUL4 * (coss(targetAngle - o->oMoveAngleYaw) + 1.0f)
                                           * (coss(targetPitch - o->oFaceAnglePitch) + 1.0f),
                                       1.f);
            if ((o->oTimer > 60) || gMarioState->action == ACT_CRAWLING) {
                o->oAction = 3;
            }
            break;
        case 2:
            // looping while charge
            cur_obj_init_animation(4);
            if (o->header.gfx.unk38.animFrame > CHARGETIME) {
                o->header.gfx.unk38.animFrame -= CHARGETIME;
            }
            break;
        case 3:
            // slowly fly at mario
            // if (cur_obj_check_if_at_animation_end()) {
            cur_obj_init_animation(3);
            // }
            targetAngle = atan2s(gMarioState->pos[2] - o->oPosZ, gMarioState->pos[0] - o->oPosX);
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, targetAngle, 0x400);
            targetPitch =
                -atan2s(sqrtf((gMarioState->pos[2] - o->oPosZ) * (gMarioState->pos[2] - o->oPosZ)
                              + (gMarioState->pos[0] - o->oPosX) * (gMarioState->pos[0] - o->oPosX)),
                        gMarioState->pos[1] - o->oPosY);
            o->oFaceAnglePitch = approach_s16_symmetric(o->oFaceAnglePitch, targetPitch, 0x400);
#undef FLYSPEEDMUL4
#define FLYSPEEDMUL4 (8.f / 6.25f)
            o->oForwardVel =
                approach_f32_symmetric(o->oForwardVel,
                                       FLYSPEEDMUL4 * (coss(targetAngle - o->oMoveAngleYaw) + 1.5f)
                                           * (coss(targetPitch - o->oFaceAnglePitch) + 1.5f),
                                       2.f);
            if (IsMarioFarFromHome(4000.f) || o->oTimer > 300 || gMarioState->action == ACT_CRAWLING) {
                o->oAction = 5;
            }
            if ((((gCurrentObject->oRoom) & 0xFF) != CurrentRoom)
                && ((gCurrentObject->oRoom & 0xFF00) != (CurrentRoom << 8))) {
                o->oAction = 5;
            }
            break;
        case 4:
            // die
            // make him shrink too
            o->oIntangibleTimer = -1;
            o->oFaceAnglePitch += 0x800;
            o->oFaceAngleRoll += 0xC00;
            collisionData.offsetY = 0.f;
            collisionData.radius = 50.f;
            collisionData.x = (s16) o->oPosX;
            collisionData.y = (s16) o->oPosY;
            collisionData.z = (s16) o->oPosZ;
            if ((o->oTimer > 23) || (find_wall_collisions(&collisionData))) {
                mark_obj_for_deletion(o);
                spawn_mist_particles_variable(20, 0, 46.f);
                CurObjSpawnYellowCoins(2);
            }
            break;
        case 5:
            // go home
            o->oVelY -= 2.f;
            o->oVelX = approach_f32_symmetric(o->oVelX, 0, 2.f);
            o->oVelZ = approach_f32_symmetric(o->oVelZ, 0, 2.f);
            if (o->oTimer > 100) {
                o->oAction = 0;
                o->oFaceAnglePitch = 0;
                o->oMoveAngleYaw = o->oAnimState;
                o->oHiddenBlueCoinSwitch = 0;
                o->oPosX = o->oHomeX;
                o->oPosY = o->oHomeY;
                o->oPosZ = o->oHomeZ;
                o->oVelX = 0.f;
                o->oVelY = 0.f;
                o->oVelZ = 0.f;
                o->oForwardVel = 0;
            }
            break;
    }
    if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
        o->oAction = 4;
        o->oMoveAngleYaw = gMarioState->faceAngle[1] + 0x8000;
        o->oForwardVel = -35.f;
        o->oVelY = 10.f;
        o->oIntangibleTimer = 0 - 1;
    }
    if ((o->oAction != 5) && (o->oAction != 4)) {
        o->oVelY = sins(-o->oFaceAnglePitch) * o->oForwardVel;
        o->oVelX = coss(-o->oFaceAnglePitch) * sins(o->oMoveAngleYaw) * o->oForwardVel;
        o->oVelZ = coss(-o->oFaceAnglePitch) * coss(o->oMoveAngleYaw) * o->oForwardVel;
    } else {
        cur_obj_compute_vel_xz();
    }
    cur_obj_update_floor_height();
    cur_obj_move_using_vel();
    o->oInteractStatus = 0;
    // can go through walls, but not above ceilings or OOB
    // kill by GP or dive, drops 2 coins
}

// left, up, forward, framescale
// left/right may be swapped right now!
ALIGNED16 f32 BubbleParameters[][5] = {
    { 1.f, -78.f, 62.f, 100.f, 1.25f }, // wario or yoshi?
    { 1.f, -3.f, 106.f, -10.f, 1.25f }, // wario or yoshi?
    { 1.f, -20.f, 20.f, 65.f, 1.f },    // bbh
    { 1.f, -50.f, 125.f, 80.f, 1.f },   // treetops
    { 1.f, -82.f, 125.f, 80.f, 1.25f }, // sleeping goomba
    { 2.5f, 0.f, 425.f, 265.f, 1.f }    // amayzee dayzee
};

void OffsetChildByTransform_SIMPLE(struct Object *child, struct Object *parent, float yOffset,
                                   float horizOffset, f32 lateral) {
    child->oPosY = parent->oPosY + yOffset;
    child->oPosX = parent->oPosX + horizOffset * sins(parent->oMoveAngleYaw)
                   + lateral * sins(parent->oMoveAngleYaw + 0x4000);
    child->oPosZ = parent->oPosZ + horizOffset * coss(parent->oMoveAngleYaw)
                   + lateral * coss(parent->oMoveAngleYaw + 0x4000);
}
void SleepBubbleInit(void) {
    OffsetChildByTransform_SIMPLE(o, o->oObjPointer1, BubbleParameters[bParam2][2],
                                  BubbleParameters[bParam2][3], -BubbleParameters[bParam2][1]);
   // o->header.gfx.CullingRadius *= BubbleParameters[bParam2][0];
}

void SleepBubble(void) {
    s32 LastFrame = o->oObjPointer1->header.gfx.unk38.curAnim->unk08;
    s32 i;
    if (!o->oObjPointer1->oAction) {
        // some sleep anims have sleep fadeouts .scale up!
        f32 Frame = (o->oObjPointer1->header.gfx.unk38.animFrame) * BubbleParameters[bParam2][4];
#define IDLETIME 8.f
        f32 AnimationCurveTime = LastFrame / 2.f - IDLETIME / 2.f;
        f32 scale = 1.f;
        if (Frame < AnimationCurveTime) {
            scale = coss((Frame / AnimationCurveTime) * 0x8000) * 1.0f + 2.f;
        } else if (Frame > IDLETIME + AnimationCurveTime) {
            scale =
                coss(MIN(1.f, ((Frame - AnimationCurveTime - IDLETIME) / AnimationCurveTime)) * 0x8000)
                    * -1.0f
                + 2.f;
        }
        cur_obj_scale(scale * BubbleParameters[bParam2][0]);
    } else {
        for (i = 0; i < 13; i++) {
            struct Object *Obj = spawn_object(o, MODEL_BUBBLE, bhvPiranhaPlantWakingBubbles);
            Obj->oPosY += 5.f * o->header.gfx.scale[1];
        }
        obj_mark_for_deletion(o);
    }
}
Gfx *geo_set_primOpa(s32 callContext, struct GraphNode *b, UNUSED Mat4 *mtx) {
    struct Object *obj = (struct Object *) gCurGraphNodeObject;
    struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) b;
    if (callContext == GEO_CONTEXT_RENDER) {
        Gfx *gfx = alloc_display_list(sizeof(Gfx) * 2);
        Gfx *dlStart = gfx;
        gDPSetPrimColor(dlStart++, 0, 0, 0, (ObjbParam2(obj) - 16) * 20, (ObjbParam2(obj) - 16) * 20,
                        obj->oOpacity);
        gSPEndDisplayList(dlStart++);
        asGenerated->fnNode.node.flags = (asGenerated->fnNode.node.flags & 0xFF) | (asGenerated->parameter << 8);
        return gfx;
    }
    return 0;
}


#include "levels/thi/header.h"

Gfx *BGList[] = {
   0,
    0,
0,
    0,
    0,
    0,
    0,
    &MoonlitBG_AAAAAAABackGround_001_mesh[0],
    &MoonlitBG2_AAAAAAABackGroundTransparent_mesh[0]
};

f32 farawaynesses[] = {
    0.99f, 0.99f, 0.99f, 0.99f,    0.99f,  0.75675f, 0.99f, 0.75675f, 0.99f, // 8
    0.99f, 1.f,   0.99f, 0.75675f, 0.975f, 0.99f,    0.99f, 0.99f,    0.99f, // 17
    0.99f, 0.99f, 0.99f, 0.99f,    0.99f,  1.00f,    0.99f, 0.99f,    0.99f, // 26
    0.99f, 0.99f, 0.99f,
};
Gfx *geo_render_INFBG(s32 callContext, struct GraphNode *node, UNUSED Mat4 b) {
    f32 pos[3];
    s32 i;
    struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) node;
    if (callContext == GEO_CONTEXT_RENDER) {
        Mtx *mtx = alloc_display_list(sizeof(*mtx));
        Gfx *dlist = alloc_display_list(4 * sizeof(Gfx));
        Gfx *Start = dlist;
        for (i = 0; i < 3; i++) {
            pos[i] = newcam_pos[i] * farawaynesses[asGenerated->parameter];
        }
        guTranslate(mtx, pos[0], pos[1], pos[2]);
        gSPMatrix(dlist++, (mtx),
                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
        gSPDisplayList(dlist++, CaptainBG_CaptainBG_mesh);
        gSPEndDisplayList(dlist++);
        asGenerated->fnNode.node.flags = (asGenerated->fnNode.node.flags & 0xFF) | (0 << 8);
        return Start;
    }
    return 0;
}

Gfx *FindFirstMatching(Gfx *DLStart, u32 Word1Flag, u32 Word2Flag, u32 DesiredWord1,
                            u32 DesiredWord2) {
    s32 DebugCounter = 0;
    do {
        if (!0) {
            DebugCounter++;
            // crash on purpose
            if (!(DebugCounter < (0x300000 / 8)))
                return 0;
        }
        if ((DLStart[0].words.w0 & Word1Flag) != (DesiredWord1 & Word1Flag))
            continue;
        if ((DLStart[0].words.w1 & Word2Flag) != (DesiredWord2 & Word2Flag))
            continue;
        return DLStart;
    } while (DLStart++);
    return 0;
}


u8 water_texI4[64 * 32];

u32 water_get_srcI4() {
    return water_texI4;
}
Gfx envColor[] = {
    sDPRGBColor(G_SETENVCOLOR, 64, 64, 64, 64),
    gsSPEndDisplayList(),
};
// Gfx pointers that may be backed up by various geo nodes or texture animations
Gfx *GfxPointerStorage[10];
#define LIGHTINGTIMER (envColor[0].words.w1 & 0x000000FF)
u8 bolted = 0;
static const Gfx FindFoamyWater = gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, thi_dl_tiki1_i4);
static const Gfx FindGFX2 = gsDPSetTileSize(1, 0, 0, 252, 252);
Gfx *geo_cause_env_lightning(s32 callContext, struct GraphNode *b, UNUSED Mat4 *mtx) {
    Gfx *gfx = NULL;
    s32 old;
    u8 brightness;
    struct GraphNodeGenerated *asGenerated = (struct GraphNodeGenerated *) b;
    if (callContext == GEO_CONTEXT_RENDER) {
        gfx = &envColor[0];
        if (!asGenerated->parameter) {
            brightness = (envColor[0].words.w1 & 0x000000FF);
            if ((brightness > 30) && ((random_u16() % 175) == 0)) {
                brightness = 0;
                bolted = 1;
            } else {
                brightness = approach_s16_symmetric(brightness, 64, 1);
            }
            envColor[0].words.w1 =
                brightness + brightness * 256 + brightness * 256 * 256 + brightness * 256 * 256 * 256;
            // ALSO: scroll water. because it fits here i guess
#define SCROLLBITFLAG _SHIFTL(0xFFF, 12, 12)
#define SCROLLBITFLAG2 _SHIFTL(0xFFF, 0, 12)
            old = (GfxPointerStorage[1]->words.w0 & SCROLLBITFLAG) >> 12;
            GfxPointerStorage[1]->words.w0 =
                ((GfxPointerStorage[1]->words.w0 & (~SCROLLBITFLAG)) | _SHIFTL(old + 5, 12, 12));
            old = (GfxPointerStorage[1]->words.w0 & SCROLLBITFLAG2) >> 0;
            GfxPointerStorage[1]->words.w0 =
                ((GfxPointerStorage[1]->words.w0 & (~SCROLLBITFLAG2)) | _SHIFTL(old - 6, 0, 12));
        }
        asGenerated->fnNode.node.flags = (asGenerated->fnNode.node.flags & 0xFF) | (asGenerated->parameter << 8);
    } else if (callContext == GEO_CONTEXT_CREATE) {
        if (!asGenerated->parameter) {
            Gfx *Found =
                FindFirstMatching(SegmentedToVirtual(thi_dl_OCEAN_mesh_layer_1), 0xFFFFFFFF,
                                  0xFFFFFFFF, FindFoamyWater.words.w0, FindFoamyWater.words.w1);
            Found->words.w1 = water_get_srcI4() & 0x00FFFFFF;
            GfxPointerStorage[1] =
                FindFirstMatching(SegmentedToVirtual(thi_dl_OCEAN_mesh_layer_1), 0xFF000000,
                                  0xFFFFFFFF, FindGFX2.words.w0, FindGFX2.words.w1);
        }
    }
    return gfx;
}
s32 CurObjBlinkAfterTimeUntil(s32 TimeUntilBlink, s32 TimeBlinking) {
    s32 TimeSpent = o->oTimer - TimeUntilBlink;
    if (o->oTimer >= TimeUntilBlink) {
        if (!(TimeSpent & 1)) {
            o->header.gfx.node.flags ^= GRAPH_RENDER_INVISIBLE;
        }
    }

    return TimeSpent > TimeBlinking;
}
extern const Collision fallplatform1_collision[];
extern const Collision fallplatform2_collision[];
void fallplatform(void) {
    u32 *collisionData;
    if (bParam2) {
        collisionData = SegmentedToVirtual(fallplatform2_collision);
    } else {
        collisionData = SegmentedToVirtual(fallplatform1_collision);
    }
    o->collisionData = collisionData;
    switch (o->oAction) {
        case 0:
            if (cur_obj_is_mario_on_platform()) {
                o->oAction++;
                PlaySFX(SOUND_OBJ_UNKNOWN2);
                // CurObjApplyCameraShakeWithFalloff(&SmallDefaultShake, 5500.f, 2000.f);
            }
            Solidify();
            break;
        case 1:
            o->oGraphYOffset = (o->oTimer & 1) * -8.f;
            if (o->oTimer > 32) {
                o->oAction++;
                o->oGraphYOffset = 0;
            }
            Solidify();
            break;
        case 2:
            o->oVelY -= 1.f;
            if (o->oVelY < -75.f) {
                o->oVelY = -75.f;
            }
            if (o->oPosY < -1500.f) {
                o->oAction++;
            }
            Solidify();
            break;
        case 3:
            if (CurObjBlinkAfterTimeUntil(0, 20)) {
                o->oAction = 0;
                o->oPosX = o->oHomeX;
                o->oPosY = o->oHomeY;
                o->oPosZ = o->oHomeZ;
                o->oVelY = 0;
                o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
            }
            Solidify();
            break;
    }
    o->oPosY += o->oVelY;
}