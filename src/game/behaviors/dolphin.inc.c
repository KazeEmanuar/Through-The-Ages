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
            if (gMarioState->controller->buttonPressed & A_BUTTON) {
                magnitude = -40.0f;
                play_sound(SOUND_MOVING_TERRAIN_SLIDE, gDefaultSoundArgs);
            } else {
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
            o->oVelX += sins(gMarioState->intendedYaw) * gMarioState->intendedMag / 64.f;
            o->oVelZ += coss(gMarioState->intendedYaw) * gMarioState->intendedMag / 64.f;
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
            o->oForwardVel *= 0.998f;
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
    { 5, "Unlock Haunter" },
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

void renderAllItems(u8 a) {
    int i, j;
    u8 ranktext[7] = { 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0x9e, 0xff };
    for (i = 0; i < itemListlength; i++) {
        ranktext[0] = 0XFA;
        print_generic_string2(menuX + a, menuY - menuoffset - textheight * i - a, itemList[i].name);
        convertNumberToSm64String(itemList[i].price, ranktext + 1); // normalize number
        print_generic_string(menuX + a + 100, menuY - menuoffset - textheight * i - a, ranktext);
        ranktext[1] = 0x9e;
        ranktext[2] = 0x9e;
        ranktext[3] = 0x9e;
        ranktext[4] = 0x9e;
        ranktext[5] = 0x9e;
    }
}
u16 pokedialog;
u32 getPokeID(u16 selection) {
    switch (selection) {
        case 2:
            pokedialog = 159;
            return 1 << 0;
            break;
        case 3:
            pokedialog = 162;
            return 1 << 3;

            break;
        case 4:
            pokedialog = 164;
            return 1 << 5;

            break;
        case 5:
            pokedialog = 165;
            return 1 << 6;

            break;
        case 6:
            pokedialog = 170;
            return 1 << 7;

            break;
        case 7:
            pokedialog = 171;
            return 1 << 8;

            break;
        case 8:
            pokedialog = 168;
            return 1 << 9;

            break;
        case 9:
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
                        cutscene = cutscene_object(CUTSCENE_PREPARE_CANNON, cannonClosed);
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
                    } else {
                        gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[0] |=
                            getPokeID(blackmarketselection);
                        rendershop = 0;
                        gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[1] += 5;
                        play_sound(SOUND_MENU_STAR_SOUND, gDefaultSoundArgs);
                    }
                    break;
                case 10:
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
    if (yoshiselected > (10)) {
        yoshiselected = 0;
    } else if (yoshiselected == -1) {
        yoshiselected = 10;
    }

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
    Gfx *a = segmented_to_virtual(ccm_dl_wata_mesh);
    a[0].words.w0 = 0xdf000000;
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
    int i = 0xFFFFFF00 + t;
    Gfx *a = segmented_to_virtual(mat_mirage_floorSide_001_v2_v2);
    a[0x13].words.w1 = i;
    a = segmented_to_virtual(mat_mirage_ground_001_v2_v2);
    a[0x12].words.w1 = i;
    a = segmented_to_virtual(mat_mirage_stone_001_v2_v2);
    a[0x13].words.w1 = i;
    a = segmented_to_virtual(mat_mirage_triangularStone_001_v2_v2);
    a[0x12].words.w1 = i;
    // a = segmented_to_virtual(mat_mirage_roofOrnament_002_v2_v2);
    // a[0x13].words.w1 = i;
    a = segmented_to_virtual(mat_mirage_sm64_material_007);
    a[0x12].words.w1 = i;
    a = segmented_to_virtual(mat_mirage_sm64_material_005);
    a[0x12].words.w1 = i;
    a = segmented_to_virtual(mat_mirage_sm64_material_014_v2_v2);
    a[0x13].words.w1 = i;
    a = segmented_to_virtual(mat_mirage_sm64_material_002);
    a[0x12].words.w1 = i;
    a = segmented_to_virtual(mat_mirage_sm64_material_003);
    a[0x12].words.w1 = i;
    a = segmented_to_virtual(mat_mirage_sm64_material_004);
    a[0x12].words.w1 = i;
    a = segmented_to_virtual(mat_mirage_roofOrnament_003_v2_v2);
    a[0x12].words.w1 = i;
    a = segmented_to_virtual(mat_mirage_sm64_material_006);
    a[0x12].words.w1 = i;
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
                cur_obj_play_sound_2(SOUND_OBJ_KING_WHOMP_DEATH);
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
        }
    }
}



// 6x96 I4 sheet of animframes
u8 animFrames[6 * 3 * 32] = {
	0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 0x01, 0x11, 
	0x11, 0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 0x00, 
	0x00, 0x00, 0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 
	0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 0x01, 0x11, 
	0x11, 0x00, 0x00, 0x00, 0x02, 0x22, 0x22, 0x02, 
	0x22, 0x22, 0x02, 0x22, 0x22, 0x02, 0x22, 0x22, 
	0x02, 0x22, 0x22, 0x00, 0x00, 0x00, 0x03, 0x33, 
	0x33, 0x03, 0x33, 0x33, 0x03, 0x33, 0x33, 0x03, 
	0x33, 0x33, 0x03, 0x33, 0x33, 0x00, 0x00, 0x00, 
	0x04, 0x44, 0x44, 0x04, 0x44, 0x44, 0x04, 0x44, 
	0x44, 0x04, 0x44, 0x44, 0x04, 0x44, 0x44, 0x00, 
	0x00, 0x00, 0x05, 0x55, 0x55, 0x05, 0x55, 0x55, 
	0x05, 0x55, 0x55, 0x05, 0x55, 0x55, 0x05, 0x55, 
	0x55, 0x00, 0x00, 0x00, 0x06, 0x66, 0x66, 0x06, 
	0x66, 0x66, 0x06, 0x66, 0x66, 0x06, 0x66, 0x66, 
	0x06, 0x66, 0x66, 0x00, 0x00, 0x00, 0x07, 0x77, 
	0x77, 0x07, 0x77, 0x77, 0x07, 0x77, 0x77, 0x07, 
	0x77, 0x77, 0x07, 0x77, 0x77, 0x00, 0x00, 0x00, 
	0x08, 0x88, 0x88, 0x08, 0x88, 0x88, 0x08, 0x88, 
	0x88, 0x08, 0x88, 0x88, 0x08, 0x88, 0x88, 0x00, 
	0x00, 0x00, 0x09, 0x99, 0x99, 0x09, 0x99, 0x99, 
	0x09, 0x99, 0x99, 0x09, 0x99, 0x99, 0x09, 0x99, 
	0x99, 0x00, 0x00, 0x00, 0x0b, 0xbb, 0xbb, 0x0b, 
	0xbb, 0xbb, 0x0b, 0xbb, 0xbb, 0x0b, 0xbb, 0xbb, 
	0x0b, 0xbb, 0xbb, 0x00, 0x00, 0x00, 0x0c, 0xcc, 
	0xcc, 0x0c, 0xcc, 0xcc, 0x0c, 0xcc, 0xcc, 0x0c, 
	0xcc, 0xcc, 0x0c, 0xcc, 0xcc, 0x00, 0x00, 0x00, 
	0x0d, 0xdd, 0xdd, 0x0d, 0xdd, 0xdd, 0x0d, 0xdd, 
	0xdd, 0x0d, 0xdd, 0xdd, 0x0d, 0xdd, 0xdd, 0x00, 
	0x00, 0x00, 0x0e, 0xee, 0xee, 0x0e, 0xee, 0xee, 
	0x0e, 0xee, 0xee, 0x0e, 0xee, 0xee, 0x0e, 0xee, 
	0xee, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x0f, 
	0xff, 0xff, 0x0f, 0xff, 0xff, 0x0f, 0xff, 0xff, 
	0x0f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x0f, 0xff, 
	0xff, 0x0f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x0f, 
	0xff, 0xff, 0x0f, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x0f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x0f, 0xff, 
	0xff, 0x0f, 0xff, 0xff, 0x0f, 0xff, 0xff, 0x00, 
	0x00, 0x00, 0x0e, 0xee, 0xee, 0x0e, 0xee, 0xee, 
	0x0e, 0xee, 0xee, 0x0e, 0xee, 0xee, 0x0e, 0xee, 
	0xee, 0x00, 0x00, 0x00, 0x0d, 0xdd, 0xdd, 0x0d, 
	0xdd, 0xdd, 0x0d, 0xdd, 0xdd, 0x0d, 0xdd, 0xdd, 
	0x0d, 0xdd, 0xdd, 0x00, 0x00, 0x00, 0x0c, 0xcc, 
	0xcc, 0x0c, 0xcc, 0xcc, 0x0c, 0xcc, 0xcc, 0x0c, 
	0xcc, 0xcc, 0x0c, 0xcc, 0xcc, 0x00, 0x00, 0x00, 
	0x0b, 0xbb, 0xbb, 0x0b, 0xbb, 0xbb, 0x0b, 0xbb, 
	0xbb, 0x0b, 0xbb, 0xbb, 0x0b, 0xbb, 0xbb, 0x00, 
	0x00, 0x00, 0x09, 0x99, 0x99, 0x09, 0x99, 0x99, 
	0x09, 0x99, 0x99, 0x09, 0x99, 0x99, 0x09, 0x99, 
	0x99, 0x00, 0x00, 0x00, 0x08, 0x88, 0x88, 0x08, 
	0x88, 0x88, 0x08, 0x88, 0x88, 0x08, 0x88, 0x88, 
	0x08, 0x88, 0x88, 0x00, 0x00, 0x00, 0x07, 0x77, 
	0x77, 0x07, 0x77, 0x77, 0x07, 0x77, 0x77, 0x07, 
	0x77, 0x77, 0x07, 0x77, 0x77, 0x00, 0x00, 0x00, 
	0x06, 0x66, 0x66, 0x06, 0x66, 0x66, 0x06, 0x66, 
	0x66, 0x06, 0x66, 0x66, 0x06, 0x66, 0x66, 0x00, 
	0x00, 0x00, 0x05, 0x55, 0x55, 0x05, 0x55, 0x55, 
	0x05, 0x55, 0x55, 0x05, 0x55, 0x55, 0x05, 0x55, 
	0x55, 0x00, 0x00, 0x00, 0x04, 0x44, 0x44, 0x04, 
	0x44, 0x44, 0x04, 0x44, 0x44, 0x04, 0x44, 0x44, 
	0x04, 0x44, 0x44, 0x00, 0x00, 0x00, 0x03, 0x33, 
	0x33, 0x03, 0x33, 0x33, 0x03, 0x33, 0x33, 0x03, 
	0x33, 0x33, 0x03, 0x33, 0x33, 0x00, 0x00, 0x00, 
	0x02, 0x22, 0x22, 0x02, 0x22, 0x22, 0x02, 0x22, 
	0x22, 0x02, 0x22, 0x22, 0x02, 0x22, 0x22, 0x00, 
	0x00, 0x00, 0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 
	0x01, 0x11, 0x11, 0x01, 0x11, 0x11, 0x01, 0x11, 
	0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	

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
            generateNightSky(nightSky);
            break;
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
}

void toadlawyer(void) {
    s32 i;
    if (save_file_get_total_star_count(gCurrSaveFileNum - 1, 0, 0x18) < 45) {
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
                    level_trigger_warp(m, WARP_OP_CREDITS_END);
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
                    gSaveBuffer.files[gCurrSaveFileNum - 1]->capPos[0] = 0xff; //debug
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