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
void krakendmg() {
    if (o->oTimer > 50) {
        gMarioState->faceAngle[1] = obj_angle_to_object(gMarioState->marioObj, o);
        o->oTimer = 0;
        m->hurtCounter += 4 * 3;
        play_sound(SOUND_MARIO_ATTACKED, m->marioObj->header.gfx.cameraToObject);
        update_mario_sound_and_camera(m);
        drop_and_set_mario_action(m, ACT_BACKWARD_WATER_KB, 3);
        gMarioState->forwardVel = -40.f;
    }
}
void krakenCode(void) {
    if (o->oDistanceToMario < 3500.f) {
        o->header.gfx.unk38.animFrame++;
    }
    if (o->oDistanceToMario < 5500.f) {
        if (cur_obj_check_if_near_animation_end()) {
            cur_obj_init_animation(0);
        }
    } else {
        cur_obj_init_animation(1);
        if (o->header.gfx.unk38.animFrame > 79) {
            o->header.gfx.unk38.animFrame = 0;
        }
    }
    if (gMarioState->wall) {
        if (gMarioState->wall->object == o) {
            krakendmg();
        }
    }
    if (gMarioState->ceil) {
        if (gMarioState->ceil->object == o) {
            krakendmg();
        }
    }
    if (gMarioState->floor) {
        if (gMarioState->floor->object == o) {
            krakendmg();
        }
    }
    load_object_collision_model();
}

extern struct Surface *resolve_and_return_wall_collisions(Vec3f pos, f32 offset, f32 radius);
;
void screwcode(void) {
    f32 scale;
    scale = (o->oBehParams2ndByte * 2 + 100.f) / 50.f;
    cur_obj_scale(scale);
    if (cur_obj_is_mario_on_platform()) {
        if (coss(atan2s(gMarioObject->oPosX - o->oPosX, gMarioObject->oPosZ - o->oPosZ)
                 + o->oFaceAngleYaw)
            > 0) {
            o->oAngleVelRoll -= 0x0020 / scale;
        } else {
            o->oAngleVelRoll += 0x0020 / scale;
        }
        if (o->oAngleVelRoll > 0x400 / scale) {
            o->oAngleVelRoll = 0x400 / scale;
        }
        if ((s16) o->oAngleVelRoll < -0x400 / scale) {
            o->oAngleVelRoll = -0x400 / scale;
        }
    }
    o->oAngleVelRoll = approach_s16_symmetric(o->oAngleVelRoll, 0, 0x08 / scale);
    o->oFaceAngleRoll += o->oAngleVelRoll;
    o->oForwardVel = o->oAngleVelRoll * 0.007f * scale;
    cur_obj_move_xz_using_fvel_and_yaw();
    resolve_and_return_wall_collisions(&o->oPosX, 0.0f, 300.0f * scale * scale * scale);
    load_object_collision_model();
}

extern const Trajectory ssl_area_1_spline_eelpath[];
void deepseaeel(void) {
    f32 x, z, y;
    x = ((s16 *) segmented_to_virtual(ssl_area_1_spline_eelpath))[1 + o->oOpacity];
    z = ((s16 *) segmented_to_virtual(ssl_area_1_spline_eelpath))[3 + o->oOpacity];
    y = ((s16 *) segmented_to_virtual(ssl_area_1_spline_eelpath))[2 + o->oOpacity];
    o->oForwardVel = 40.f;
    o->oDrawingDistance = 150000.f;
    o->oMoveAngleYaw =
        approach_s16_symmetric(o->oMoveAngleYaw, atan2s(z - o->oPosZ, x - o->oPosX), 0x0040);
    if (sqrtf((x - o->oPosX) * (x - o->oPosX) + (z - o->oPosZ) * (z - o->oPosZ)) < 350.f) {
        o->oOpacity += 4;
        if (o->oOpacity == 40) {
            o->oOpacity = 0;
        }
    }
    if (absf(o->oPosY - y) > 10.f) {
        o->oVelY += (y - o->oPosY) / absf(o->oPosY - y) * 0.5f;
    } else {
        o->oVelY *= 0.95f;
    }
    if (o->oVelY > 30.f) {
        o->oVelY = 30.f;
    }
    if (o->oVelY < -30.f) {
        o->oVelY = -30.f;
    }
    cur_obj_move_xz_using_fvel_and_yaw();
    o->oPosY += o->oVelY;
}

void snappyeel(void) {
    if (!o->oOpacity) {
        o->oOpacity = o->oMoveAngleYaw;
    }
    switch (o->oAction) {
        case 0:
            o->header.gfx.unk38.animFrame = 0;
            if (!o->oTimer) {
                o->oPosX = o->oHomeX + sins(o->oMoveAngleYaw) * -1150.f;
                o->oPosZ = o->oHomeZ + coss(o->oMoveAngleYaw) * -1150.f;
            }
            if (o->oDistanceToMario < 3000.f) {
                if (absf(gMarioState->pos[1] - o->oPosY) < 1000.f) {
                    if (o->oTimer > 80) {
                        o->oAction = 1;
                        o->oForwardVel = 80.f;
                        o->oMoveAngleYaw = o->oAngleToMario;
                        cur_obj_play_sound_2(SOUND_OBJ_EEL_2);
                    }
                }
            }
            break;
        case 1:
            if (o->oVelY > 20.f) {
                o->oVelY = 20.f;
            }
            if (o->oTimer > 25) {
                o->oForwardVel = approach_f32_asymptotic(o->oForwardVel, 0.f, 0.93f);
                o->oVelY -= 0.2f;
            } else {
                o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x0080);
                o->oVelY = (gMarioState->pos[1] - o->oPosY)
                           / (lateral_dist_between_objects(gMarioState->marioObj, o) / o->oForwardVel);
            }
            if (o->oTimer > 40) {
                o->oForwardVel -= 8.f;
            }
            if (o->oTimer > 55) {
                o->oAction++;
            }
            cur_obj_move_xz_using_fvel_and_yaw();
            o->oPosY += o->oVelY;
            break;
        case 2:
            o->oForwardVel = -30.f;
            o->oVelY = (o->oPosY - o->oHomeY) / (cur_obj_lateral_dist_to_home() / o->oForwardVel);
            o->oMoveAngleYaw =
                approach_s16_symmetric(o->oMoveAngleYaw, cur_obj_angle_to_home() - 0x8000, 0x300);
            if ((cur_obj_lateral_dist_to_home() < 100.f) || (o->oTimer > 100)) {
                o->oAction = 0;
                o->oForwardVel = 0.f;
                o->oVelY = 0.f;
            }
            cur_obj_move_xz_using_fvel_and_yaw();
            o->oPosY += o->oVelY;
            break;
    }
}

void angler(void) {
    if (!o->oOpacity) {
        o->oOpacity = o->oMoveAngleYaw;
    }
    switch (o->oAction) {
        case 0:
            o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oOpacity, 0x0080);
            o->header.gfx.unk38.animFrame = 0;
            if (!o->oTimer) {
                o->oPosX = o->oHomeX + sins(o->oOpacity) * -1200.f;
                o->oPosZ = o->oHomeZ + coss(o->oOpacity) * -1200.f;
            }
            if (o->oDistanceToMario < 4000.f) {
                if (o->oTimer > 360) {
                    o->oAction = 1;
                    o->oForwardVel = 80.f;
                    o->oMoveAngleYaw =
                        approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x0100);
                    cur_obj_play_sound_2(SOUND_OBJ_EEL_2);
                };
            }
            break;
        case 1:
            if (o->oVelY > 20.f) {
                o->oVelY = 20.f;
            }
            if (o->oTimer > 25) {
                o->oForwardVel = approach_f32_asymptotic(o->oForwardVel, 0.f, 0.93f);
                o->oVelY -= 0.2f;
            } else {
                o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, o->oAngleToMario, 0x0100);
                o->oVelY = approach_f32_symmetric(
                    o->oVelY,
                    (gMarioState->pos[1] - o->oPosY)
                        / (lateral_dist_between_objects(gMarioState->marioObj, o) / o->oForwardVel),
                    5.f);
            }
            if (o->oTimer > 40) {
                o->oForwardVel -= 8.f;
            }
            if (o->oTimer > 55) {
                o->oAction++;
            }
            cur_obj_move_xz_using_fvel_and_yaw();
            o->oPosY += o->oVelY;
            break;
        case 2:
            o->oForwardVel = -20.f;
            o->oVelY = (o->oPosY - o->oHomeY) / (cur_obj_lateral_dist_to_home() / o->oForwardVel);
            o->oMoveAngleYaw =
                approach_s16_symmetric(o->oMoveAngleYaw, cur_obj_angle_to_home() - 0x8000, 0x300);
            if ((cur_obj_lateral_dist_to_home() < 100.f) || (o->oTimer > 150)) {
                o->oAction = 0;
                o->oForwardVel = 0.f;
                o->oVelY = 0.f;
            }
            cur_obj_move_xz_using_fvel_and_yaw();
            o->oPosY += o->oVelY;
            break;
    }
}

#define SPAWNTIME 20
#define RANGE 150.f
void bhv_air_rocks(void) {
    struct Object *a;
    if (o->oTimer >= (SPAWNTIME + (random_u16() & 7))) {
        a = spawn_object_relative(0, random_f32_around_zero(RANGE), -80, random_f32_around_zero(RANGE),
                                  o, MODEL_BUBBLE, bhvWaterAirBubble);
        a->oBehParams = o->oBehParams;
        o->oTimer = 0;
    }
}
extern void obj_set_pos_relative(struct Object *obj, struct Object *other, f32 dleft, f32 dy,
                                 f32 dforward);
void boneMom(void) {
    s16 targetAngle;
    if (!o->oHiddenBlueCoinSwitch) {
        o->oHiddenBlueCoinSwitch = spawn_object(o, 0, bhvHitbox);
        o->oHiddenBlueCoinSwitch->hitboxRadius = 350;
        o->oHiddenBlueCoinSwitch->hitboxDownOffset = 200;
        o->oHiddenBlueCoinSwitch->hitboxHeight = 450;
        o->rawData.asObject[0x1D] = spawn_object(o, 0, bhvHitbox);
        o->rawData.asObject[0x1D]->hitboxRadius = 350;
        o->rawData.asObject[0x1D]->hitboxDownOffset = 200;
        o->rawData.asObject[0x1D]->hitboxHeight = 450;
        o->rawData.asObject[0x1E] = spawn_object(o, 0, bhvHitbox);
        o->rawData.asObject[0x1E]->hitboxRadius = 350;
        o->rawData.asObject[0x1E]->hitboxDownOffset = 200;
        o->rawData.asObject[0x1E]->hitboxHeight = 450;
        o->rawData.asObject[0x1F] = spawn_object(o, MODEL_STAR, bhvStar);
        o->rawData.asObject[0x1F]->oBehParams = 0x05000000;
    }
    obj_set_pos_relative(o->oHiddenBlueCoinSwitch, o, 0, 0, 175.f);
    obj_set_pos_relative(o->rawData.asObject[0x1D], o, 0, 0, -35.f);
    obj_set_pos_relative(o->rawData.asObject[0x1E], o, 0, 0, -250.f);
    obj_set_pos_relative(o->rawData.asObject[0x1F], o,
                         sins(o->header.gfx.unk38.animFrame * 0x10000 / 90 + 0xC000) * 200.f, 0,
                         -500.f);
    o->oHiddenBlueCoinSwitch->oInteractType = INTERACT_DAMAGE;
    o->rawData.asObject[0x1D]->oInteractType = INTERACT_DAMAGE;
    o->rawData.asObject[0x1E]->oInteractType = INTERACT_DAMAGE;
    o->oHiddenBlueCoinSwitch->oDamageOrCoinValue = 2;
    o->rawData.asObject[0x1D]->oDamageOrCoinValue = 2;
    o->rawData.asObject[0x1E]->oDamageOrCoinValue = 2;

    if (o->oTimer < 2) {
        o->oTimer = 2;
        o->oOpacity = random_u16() % 150 + 150;
        o->oBobombBuddyPosXCopy = o->oHomeX + random_f32_around_zero(7000.f);
        o->oBobombBuddyPosZCopy = o->oHomeZ + random_f32_around_zero(7000.f);
        if (!(random_u16() % 9)) {
            o->oAction = 1;
            o->oOpacity = 0;
        }
    }
    if (o->oOpacity) {
        o->oOpacity--;
    } else {
        o->oTimer = 0;
    }
    targetAngle = atan2s(o->oBobombBuddyPosZCopy - o->oPosZ, o->oBobombBuddyPosXCopy - o->oPosX);
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, targetAngle, 0x100);
    o->oForwardVel = approach_f32(o->oForwardVel,
                                  12.f * (coss(targetAngle - o->oMoveAngleYaw) + 1.0f)
                                      * (coss(targetAngle - o->oMoveAngleYaw) + 1.0f),
                                  1.f, 1.f);
    cur_obj_move_xz_using_fvel_and_yaw();
}

void spidercrab(void) {
    o->oDrawingDistance = 150000.f;
}