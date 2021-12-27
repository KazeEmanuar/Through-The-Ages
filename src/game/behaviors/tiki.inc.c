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

void tikiflying(void) {
    switch (o->oBehParams2ndByte) {
        case 0:
            if (lateral_dist_between_objects(o, gMarioState->marioObj) > 500.f) {
                if (lateral_dist_between_objects(o, gMarioState->marioObj) < 5000.f) {
                    rotateTowardsMario(0x200);
                }
            }
            break;
        case 1:
            if (!o->oTimer) {
                o->oOpacity = o->oHomeY;
            }
            o->oHomeY = o->oOpacity + sins(o->oTimer * 0x100) * 350.f;
            break;
        case 2:
            switch (o->oAction) {
                case 0:
                    o->oAngleVelYaw = 0;
                    if (o->oTimer < 10) {
                        o->oForwardVel += 2.f;
                    }
                    if (o->oTimer > ((o->oBehParams & 0xff) + 40)) {
                        o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 0.f, 2.f);
                        if (o->oForwardVel < 0.1f) {
                            o->oAction++;
                        }
                    }
                    break;
                case 1:
                    o->oMoveAngleYaw += 0x400;
                    o->oAngleVelYaw = 0x400;
                    if (o->oTimer == 0x1F) {
                        o->oAction = 0;
                    }
                    break;
            }
            break;
        case 3:
            o->oMoveAngleYaw += ((o->oBehParams & 0xff) + 0x0080);
            o->oAngleVelYaw = ((o->oBehParams & 0xff) + 0x0080);
            o->oForwardVel = 10.f;
            break;
    }
    o->oVelY = approach_f32_asymptotic(o->oVelY, (o->oHomeY - o->oPosY) / 8.f, 0.1f);
    if (cur_obj_is_mario_on_platform()) {
        o->oVelY -= 1.5f;
        o->header.gfx.unk38.animFrame++;
    }
    if (cur_obj_is_mario_ground_pounding_platform()) {
        o->oVelY -= 8.f;
    }
    cur_obj_move_xz_using_fvel_and_yaw();
    o->oPosY += o->oVelY;
    load_object_collision_model();
}

extern struct GoombaProperties sGoombaProperties[];
void tikigoomba(void) { // anim 0 is walk
    switch (o->oOpacity) {
        case 0:
            // wait idly
            o->oDrawingDistance = 65000.f;
            if (!o->oBooParentBigBoo) {
                o->oBooParentBigBoo = spawn_object(o, 0x37, bhvSpear);
            }
            cur_obj_scale(1.5f);
            rotateTowardsMario(0x400);
            if (o->oDistanceToMario < 1850.f) {
                o->oOpacity++;
                o->oTimer = 0;
                cur_obj_init_animation(1);
            }
            break;
        case 1:
            // throw spear
            rotateTowardsMario(0x400);
            if (o->oTimer == 28) {
                o->oBooParentBigBoo->oAction = 1;
                o->oBooParentBigBoo->oVelY = 45.f;
                o->oBooParentBigBoo->oForwardVel =
                    lateral_dist_between_objects(gMarioState->marioObj, o) / 50.f;
            }
            if (o->oTimer > 38) {
                o->oOpacity++;
                o->oGoombaScale = sGoombaProperties[0].scale;
                o->oDeathSound = sGoombaProperties[0].deathSound;
                obj_set_hitbox(o, &sGoombaHitbox);
                o->oDamageOrCoinValue = sGoombaProperties[0].damage;
                o->oGravity = -8.0f / 3.0f * o->oGoombaScale;
            }
            break;
        case 2:
            // act like normal goomba
            bhv_goomba_update();
            break;
    }
}

void tikispear(void) {
    struct Object *parent = o->parentObj;
    struct Surface *floor;
    o->oFaceAnglePitch = atan2s(o->oVelY, o->oForwardVel);
    if (o->oAction) {
        if (o->oTimer < 2) {
            rotateTowardsMario(0x400);
        }
        o->oFloorHeight = find_floor(o->oPosX, o->oPosY + 100.f, o->oPosZ, &floor);
        o->oVelY -= 3.f;
        if (o->oPosY < o->oFloorHeight) {
            mark_obj_for_deletion(o);
            spawn_mist_particles();
        }
        cur_obj_compute_vel_xz();
        cur_obj_move_using_vel();
    } else {
        cur_obj_set_pos_relative(parent, -55.0f, 100.f, 12.0f);
    }
}

void sclaetiki(void) {
    cur_obj_scale(1.0f + (o->oBehParams & 0xFF) / 100.f);
    o->hitboxRadius *= o->header.gfx.scale[0];
    o->hitboxHeight *= o->header.gfx.scale[0];
}

u8 heads;
void easterhead(void) {
    if (!o->oOpacity) {
        o->oHealth = 0;
        o->oOpacity = 1;
        heads = 0;
    }
    if (!o->oSubAction) {
        if (o->oDistanceToMario < 500.f) {
            if (talkToMarioNoRotation(o->oBehParams & 0xFF)) {
                o->oSubAction = 1;
                o->oTimer = 0;
            }
        }
    } else {
        if (o->oTimer > 900) {
            o->oSubAction = 0;
        }
    }
    switch (o->oBehParams2ndByte) {
        case 0:
            if (o->oOpacity == 1) {
                if (heads == 31) {
                    o->oOpacity = 2;
                    spawn_default_star(gMarioState->pos[0], gMarioState->pos[1] + 200.f,
                                       gMarioState->pos[2]);
                }
            }
            // gp me
            if (o->oHealth >= 200) {
                if (!(heads & 1)) {
                    play_puzzle_jingle();
                }
                heads |= 1;
                o->oSubAction = 1;
                o->oTimer = 0;
            } else {
                if (cur_obj_is_mario_ground_pounding_platform()) {
                    o->oHealth += 10;
                    o->oPosY -= 10.f;
                }
            }
            break;
        case 1:
            // break thing
            if (!o->oHiddenBlueCoinSwitch) {
                o->oHiddenBlueCoinSwitch = cur_obj_nearest_object_with_behavior(bhvBreakableBox);
            }
            if ((!o->oHiddenBlueCoinSwitch->activeFlags)
                || (o->oHiddenBlueCoinSwitch->behavior != segmented_to_virtual(bhvBreakableBox))) {
                if (!(heads & 2)) {
                    play_puzzle_jingle();
                }
                heads |= 2;
                o->oSubAction = 1;
                o->oTimer = 0;
            }
            break;
        case 2:
            // scratch nose
            if (!o->oHiddenBlueCoinSwitch) {
                o->oHiddenBlueCoinSwitch = cur_obj_nearest_object_with_behavior(bhvYellowCoin);
            }
            if ((!o->oHiddenBlueCoinSwitch->activeFlags)
                || (o->oHiddenBlueCoinSwitch->behavior != segmented_to_virtual(bhvYellowCoin))) {
                if (!(heads & 4)) {
                    play_puzzle_jingle();
                }
                heads |= 4;
                o->oSubAction = 1;
                o->oTimer = 0;
            }
            break;
        case 3:
            // run 3 circles
            o->oWoodenPostTotalMarioAngle += (s16)(o->oAngleToMario - o->oWoodenPostPrevAngleToMario);
            if (absi(o->oWoodenPostTotalMarioAngle) > 0x30000) {
                if (!(heads & 8)) {
                    play_puzzle_jingle();
                }
                heads |= 8;
                o->oSubAction = 1;
                o->oTimer = 0;
            }
            o->oWoodenPostPrevAngleToMario = o->oAngleToMario;
            break;
        case 4:
            // kill the guy
            o->oCollisionDistance = 10000.f;
            if (!o->oHiddenBlueCoinSwitch) {
                o->oHiddenBlueCoinSwitch = cur_obj_nearest_object_with_behavior(bhvTikiGoomba);
            }
            if (o->oHiddenBlueCoinSwitch->oAction > 50) {
                if (!(heads & 16)) {
                    play_puzzle_jingle();
                }
                heads |= 16;
                o->oSubAction = 1;
                o->oTimer = 0;
            }
            break;
    }

    load_object_collision_model();
}

#define /*0x0FC*/ oObjPointer1 OBJECT_FIELD_OBJ(0x1D)
#define /*0x100*/ oObjPointer2 OBJECT_FIELD_OBJ(0x1E)
#define /*0x104*/ oObjPointer3 OBJECT_FIELD_OBJ(0x1F)
void inittotemBoss(void) {
    o->oHiddenBlueCoinSwitch = spawn_object(o, 0x3a, bhvTotemPole);
    o->oHiddenBlueCoinSwitch->oPosY -= 1800.f;
    o->oHiddenBlueCoinSwitch->header.gfx.scale[0] = 0.67f;
    o->oHiddenBlueCoinSwitch->header.gfx.scale[2] = 0.67f;
    o->oHiddenBlueCoinSwitch->oOpacity = 99;

    o->oObjPointer1 = spawn_object(o, 0x3B, bhvTotemBossPart);
    o->oObjPointer1->oPosY += 300.f;
    o->oObjPointer1->oBehParams2ndByte = 0;

    o->oObjPointer2 = spawn_object(o, 0x3C, bhvTotemBossPart);
    o->oObjPointer2->oPosY += 700.f;
    o->oObjPointer2->oBehParams2ndByte = 1;

    o->oObjPointer3 = spawn_object(o, 0x3D, bhvTotemBossPart);
    o->oObjPointer3->oPosY += 1100.f;
    o->oObjPointer3->oBehParams2ndByte = 2;
    o->oHealth = 0; // dies at 4 health. set to 1 when fight starts
    o->oPosY += 1000.f;
}

struct Object *find_totem(int num) {
    uintptr_t *behaviorAddr = segmented_to_virtual(bhvTotemPole);
    struct Object *obj;
    struct ObjectNode *listHead;

    listHead = &gObjectLists[get_object_list_from_behavior(behaviorAddr)];
    obj = (struct Object *) listHead->next;

    while (obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr) {
            if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && obj != o) {
                if (obj->oBehParams == num) {
                    return obj;
                }
            }
        }
        obj = (struct Object *) obj->header.next;
    }
}

u32 totemAttackTimer = 0;
void totemBoss(void) {
    o->oHiddenBlueCoinSwitch->oOpacity = o->oHealth * 600.f;
    totemAttackTimer++;
    if (o->oHealth < 3) {
        o->oObjPointer3->oMoveAngleYaw = o->oMoveAngleYaw;
        o->oObjPointer3->oPosY = 2100.f + o->oHiddenBlueCoinSwitch->oPosY;
    } else {
        o->oObjPointer3->oOpacity = 1;
    }
    if (o->oHealth < 2) {
        o->oObjPointer2->oMoveAngleYaw = o->oMoveAngleYaw;
        o->oObjPointer2->oPosY = 2500.f + o->oHiddenBlueCoinSwitch->oPosY;
    } else {
        o->oObjPointer2->oOpacity = 1;
    }
    if (o->oHealth < 1) {
        o->oObjPointer1->oMoveAngleYaw = o->oMoveAngleYaw;
        o->oObjPointer1->oPosY = 2900.f + o->oHiddenBlueCoinSwitch->oPosY;
    } else {
        o->oObjPointer1->oOpacity = 1;
    }
    switch (o->oHealth) {
        case 1:
            if (gMarioObject->platform == o->oObjPointer2) {
                if (gMarioStates[0].action == ACT_GROUND_POUND_LAND) {
                    o->oHealth++;
                    gMarioState->action = ACT_STEEP_JUMP;
                    gMarioState->vel[1] = 55.f;
                    gMarioState->forwardVel = -40.f;
                    spawn_object(o, 0, bhvTenCoinsSpawn);
                }
            }
            break;
        case 2:
            if (gMarioObject->platform == o->oObjPointer3) {
                if (gMarioStates[0].action == ACT_GROUND_POUND_LAND) {
                    o->oHealth++;
                    gMarioState->action = ACT_STEEP_JUMP;
                    gMarioState->vel[1] = 55.f;
                    gMarioState->forwardVel = -40.f;
                    o->oObjPointer1 = spawn_object(o, MODEL_STAR, bhvStar);
                    o->oObjPointer1->oPosY += 1300.f;
                    o->oObjPointer1->oBehParams = 0x00030000;
                    spawn_object(o, 0, bhvTenCoinsSpawn);
                }
            }
            break;
        case 3:

            break;
    }
    rotateTowardsMario(0x200);

    switch (o->oAction) {
        case 0:
            if (o->oDistanceToMario < 1750.f) {
                o->oAction++;
            }
            break;
        case 1:
            if (talkToMario(77)) {
                o->oAction++;
                o->oHealth++;
                totemAttackTimer = 80;
                play_music(SEQ_PLAYER_LEVEL, SEQUENCE_ARGS(4, SEQ_EVENT_BOSS), 0);
            }
            break;
        case 2:
            // wait for hit
            if (o->oTimer == 65) {
                o->oOpacity = random_u16() % 25;
                find_totem(o->oOpacity)->oOpacity = 900.f;
                find_totem((o->oOpacity + 1) % 25)->oOpacity = 1200.f;
                find_totem((o->oOpacity + 2) % 25)->oOpacity = 1500.f;
                find_totem((o->oOpacity + 3) % 25)->oOpacity = 1800.f;
                find_totem((o->oOpacity + 4) % 25)->oOpacity = 2150.f;
            }
            if (o->oTimer > 700 - (o->oHealth * 100)) {
                find_totem(o->oOpacity)->oOpacity = 0.f;
                find_totem((o->oOpacity + 1) % 25)->oOpacity = 0.f;
                find_totem((o->oOpacity + 2) % 25)->oOpacity = 0.f;
                find_totem((o->oOpacity + 3) % 25)->oOpacity = 0.f;
                find_totem((o->oOpacity + 4) % 25)->oOpacity = 0.f;
                o->oTimer = 0;
            }
            break;
        case 3:
            // spawn star
            break;
    }
}

void totemBosshead(void) {
    struct Object *flame;
    s16 goalAngle;
    switch (o->oAction) {
        case 0:
            // do nothing
            if (o->oOpacity) {
                o->oAction++;
            }
            break;
        case 1:
// fly to position
#define floatDist 1500.f
            goalAngle = atan2s(gMarioState->pos[2], gMarioState->pos[0]) + o->oBehParams2ndByte * 0x200;
            o->oHomeX = sins(goalAngle) * floatDist;
            o->oHomeZ = coss(goalAngle) * floatDist;
            o->oHomeY = gMarioState->pos[1] + 250.f;
            if (o->oHomeY < -1650.f) {
                o->oHomeY = -1650.f;
            }
            o->oHomeY += sins(o->oTimer * 0x200) * 50.f;
            o->oPosX = approach_f32_symmetric(o->oPosX, o->oHomeX, 20.f);
            o->oPosZ = approach_f32_symmetric(o->oPosZ, o->oHomeZ, 20.f);
            o->oPosY = approach_f32_symmetric(o->oPosY, o->oHomeY, 20.f);
            rotateTowardsMario(0x800);
            if ((totemAttackTimer % 400) == (o->oBehParams2ndByte * 133)) {
                o->oAction++;
            }
            break;
        case 2:
            // attack pattern
            switch (o->oBehParams2ndByte) {
                case 0:
                    // dash
                    if (!o->oTimer) {
                        o->oHomeX = gMarioState->pos[0];
                        o->oHomeY = gMarioState->pos[1];
                        o->oHomeZ = gMarioState->pos[2];
                        o->oMoveAngleYaw = atan2s(o->oHomeZ - o->oPosZ, o->oHomeX - o->oPosX);
                    }
                    if (o->oTimer < 80) {
                        o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 40.f, 2.f);
                        o->oPosY = approach_f32_symmetric(o->oPosY, o->oHomeY, 7.f);
                    } else {
                        if (o->oTimer < 120) {
                            o->oVelY += 0.5f;
                        } else {
                            o->oVelY -= 0.5f;
                        }
                        o->oForwardVel = approach_f32_symmetric(o->oForwardVel, 0.f, 2.f);
                        o->oMoveAngleYaw += 0x200;
                        if (o->oTimer > 140) {
                            o->oAction = 1;
                            o->oForwardVel = 0;
                            o->oVelY = 0;
                        }
                    }
                    cur_obj_update_floor_and_walls();
                    cur_obj_move_standard(-78);
                    break;
                case 1:
                    // spit fire
                    goalAngle = atan2s(gMarioState->pos[2], gMarioState->pos[0]);
                    o->oHomeX = sins(goalAngle) * floatDist;
                    o->oHomeZ = coss(goalAngle) * floatDist;
                    o->oHomeY = gMarioState->pos[1];
                    o->oHomeY += sins(o->oTimer * 0x800) * 10.f;
                    o->oPosX = approach_f32_symmetric(o->oPosX, o->oHomeX, 30.f);
                    o->oPosZ = approach_f32_symmetric(o->oPosZ, o->oHomeZ, 30.f);
                    o->oPosY = approach_f32_symmetric(o->oPosY, o->oHomeY, 30.f);
                    rotateTowardsMario(0x800);
                    if (!(o->oTimer & 3)) {

                        o->oFlameThowerUnk110 = 32;
                        flame = spawn_object_relative(2, 0, 110.f, 125.f, o, MODEL_RED_FLAME,
                                                      bhvFlamethrowerFlame);
                        flame->oForwardVel = 25.f;
                        flame->oVelY = 0.f;
                        cur_obj_play_sound_1(SOUND_AIR_BLOW_FIRE);
                    }
                    if (o->oTimer > 50) {
                        o->oAction = 1;
                    }
                    break;
                case 2:
                    // stomp on mario
                    if (o->oTimer < 80) {
                        o->oHomeX = gMarioState->pos[0];
                        o->oHomeY = gMarioState->pos[1] + 800.f;
                        o->oHomeZ = gMarioState->pos[2];
                        o->oPosX = approach_f32_asymptotic(o->oPosX, o->oHomeX, 0.1f);
                        o->oPosZ = approach_f32_asymptotic(o->oPosZ, o->oHomeZ, 0.1f);
                        o->oPosY = approach_f32_asymptotic(o->oPosY, o->oHomeY, 0.1f);
                    } else {
                        if (o->oTimer == 80) {
                            cur_obj_play_sound_2(SOUND_OBJ_THWOMP);
                        }
                        o->oVelY -= 8.f;
                        if (o->oMoveFlags & OBJ_MOVE_LANDED) {
                            o->oAction = 1;
                            cur_obj_shake_screen(SHAKE_POS_SMALL);
                        }
                    }
                    cur_obj_update_floor_and_walls();
                    cur_obj_move_standard(-78);
                    break;
            }
            break;
    }
    load_object_collision_model();
}

void totemPoleCOde(void) {
    o->oPosY = approach_f32_symmetric(o->oPosY, o->oHomeY + o->oOpacity, 10.f);
    load_object_collision_model();
}